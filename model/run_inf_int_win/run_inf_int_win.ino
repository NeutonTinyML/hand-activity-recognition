#include <Arduino_BHY2.h>
#include <Nicla_System.h>
#include <LibPrintf.h>

#include "src/neuton/include/neuton/neuton.h"

#define FREQUENCY_HZ    (100)
#define INTERVAL_MS     (1000 / FREQUENCY_HZ)

#define HOP_MS          (200)
#define AVG_TIME_MS     (400)

#define NUM_CLASSES     (5)
//                      RAND   CLAP   TEETH   HANDS   HAIR
#define THRESHOLDS      0.50,  0.91,  0.85,   0.92,   0.85

#define AVG_COUNT       ((AVG_TIME_MS / HOP_MS) + (AVG_TIME_MS % HOP_MS ? 1 : 0))


// #define PRINT_PROBABILITIES
// #define PRINT_INFERENCE_TIME
// #define DISABLE_POSTPROCESSING


static SensorXYZ accel(SENSOR_ID_ACC);
static SensorXYZ linear_accel(SENSOR_ID_LACC);
static SensorXYZ gyro(SENSOR_ID_GYRO);

static bool change_color = true;
static auto color = blue;


class Averaging
{
public:
  Averaging(neuton_u16_t count)
    : _count(count)
  {}

  void begin()
  {
    _sliding_window_buffer = malloc(_count * sizeof(float) * neuton_nn_model_outputs_num());
    if (!_sliding_window_buffer)
    {
      printf("Failed to allocate averaging buffer!\n");  
      while (true);
    }
    
    neuton_sliding_window_init(&_sliding_window, _sliding_window_buffer, _count * neuton_nn_model_outputs_num(), 
      sizeof(float), neuton_nn_model_outputs_num(), onBufferReady, this);
  }

  ~Averaging()
  {
    if (_sliding_window_buffer)
    {
      free(_sliding_window_buffer);
    }
  }

  void newValues(float *values)
  {
    neuton_sliding_window_feed(&_sliding_window, (void*)values, neuton_nn_model_outputs_num());    
  }
  
  inline float max() 
  {
    return _max;
  }
  
  inline neuton_u16_t index() 
  {
    return _index;
  }

protected:
  static void onBufferReady(void* p_window, neuton_u16_t window_size, void* p_user_ctx)
  {
    Averaging* inst = reinterpret_cast<Averaging*>(p_user_ctx);
    uint16_t index = 0;
    float max = 0;

    for (neuton_u16_t i = 0; i < neuton_nn_model_outputs_num(); i++)
    {
      neuton_dsp_stat_ctx_f32_t ctx = {0};
      const float *input = (float*)p_window + i;
      float avg = neuton_dsp_mean_f32_s(input, inst->_count, neuton_nn_model_outputs_num(), &ctx);
      if (avg > max)
      {
        max = avg;
        index = i;
      }
    }

    inst->_index = index;
    inst->_max = max;
  }

private:
  neuton_sliding_window_ctx_t _sliding_window = {0};
  void *_sliding_window_buffer = nullptr;
  neuton_u16_t _count;
  neuton_u16_t _index = UINT16_MAX;
  float _max = 0;
};

class Inference
{
public:
  Inference(SensorXYZ *a, SensorXYZ *la, SensorXYZ *g)
    : _accelerometer(a), _linear_accelerometer(la), _gyroscope(g), _avg(AVG_COUNT)
  {}

  void begin()
  {
    printf("\nInit NN\n");
    neuton_nn_setup();
       
#if !defined(DISABLE_POSTPROCESSING)
    printf("Init postproccessing\n");
    _avg.begin();
#endif

    printf("\nStart...\n\n");
  }

  void read(unsigned long ts)
  {
    _timestamp = ts;
    readData(_d_accelerometer, _accelerometer);
    readData(_d_linear_accelerometer, _linear_accelerometer);
    readData(_d_gyroscope, _gyroscope);

    neuton_input_t sample[neuton_nn_uniq_inputs_num()];
    neuton_u16_t i = 0;
    
    sample[i++] = _d_accelerometer.x;
    sample[i++] = _d_accelerometer.y;
    sample[i++] = _d_accelerometer.z;
    // sample[i++] = _d_linear_accelerometer.x;
    // sample[i++] = _d_linear_accelerometer.y;
    // sample[i++] = _d_linear_accelerometer.z;
    sample[i++] = _d_gyroscope.x;
    sample[i++] = _d_gyroscope.y;
    sample[i++] = _d_gyroscope.z;

    unsigned long _start = micros();
    neuton_inference_input_t* input = neuton_nn_feed_inputs(sample, neuton_nn_uniq_inputs_num());
    if (input)
    {
      {
        change_color = true;
        if (color == off)
        {
          color = blue;
        }
        else
        {
          color = off;
        }
      }

      const neuton_u16_t outputs_num = neuton_nn_model_outputs_num();
      neuton_u16_t predicted_class;
      const neuton_output_t* probabilities;
      
      if (neuton_nn_run_inference(input, &predicted_class, &probabilities) == outputs_num)
      {
        unsigned long _stop = micros();

#if defined(PRINT_PROBABILITIES)
        for(neuton_u16_t i = 0; i < outputs_num; i++)
        {
          printf("%.6f ", probabilities[i]);
        }
        printf("\n");
#endif

#if defined(PRINT_INFERENCE_TIME)
        printf("\tinference time: %lu us\n", _stop - _start);
#endif

#if !defined(DISABLE_POSTPROCESSING)
        _avg.newValues((float*)probabilities);
        handleOutput(_avg.index(), _avg.max());
#else
        handleOutput(predicted_class, probabilities[predicted_class]);
#endif

      }
    }
  }

protected:
  void readData(DataXYZ &d, SensorXYZ *sensor)
  {
    d.x = sensor->x();
    d.y = sensor->y();
    d.z = sensor->z();
  }

  static const char* getClassName(neuton_u16_t classNum)
  {
    switch (classNum)
    {
      case 0:  return "Random        ";
      case 1:  return "Clapping      ";
      case 2:  return "Brushing Teeth";
      case 3:  return "Washing Hands ";
      case 4:  return "Brushing Hair ";
      default: return "Unknown       ";
    }
  }
  
  void handleOutput(neuton_u16_t newClass, float probability)
  {
    if (probability < (1.0 / (float)neuton_nn_model_outputs_num()))
    {
      newClass = 0;
      probability = 1.0;
    }

#if !defined(DISABLE_POSTPROCESSING)
    // if (probability < _thresholds[newClass])
    // {
    //   newClass = 0;
    // }
    if (probability >= _thresholds[newClass])
#endif
    {
      printf("%lu -> %s (%3u%%)\n", _timestamp, getClassName(newClass), (uint32_t)(probability * 100.0));
    }
  }

private:
  SensorXYZ *_accelerometer;
  SensorXYZ *_linear_accelerometer;
  SensorXYZ *_gyroscope;

  unsigned long _timestamp;
  DataXYZ _d_accelerometer;
  DataXYZ _d_linear_accelerometer;
  DataXYZ _d_gyroscope;
  
  Averaging _avg;

  float _thresholds[NUM_CLASSES] = { THRESHOLDS };
};

static Inference inference(&accel, &linear_accel, &gyro);

void indication()
{
  if (change_color)
  {
    change_color = false;
    nicla::leds.setColor(color);
  }
}

void setup() 
{
  Serial.begin(115200);

  nicla::begin();
  nicla::leds.begin();

  if (!BHY2.begin(NICLA_I2C))
  {
    printf("Failed to initialize BHY2!\n");
    while (true);
  }

  bool init_success = accel.begin(FREQUENCY_HZ);
  init_success &= linear_accel.begin(FREQUENCY_HZ);
  init_success &= gyro.begin(FREQUENCY_HZ);

  if (!init_success)
  {
    printf("Failed to initialize sensors!\n");
    while (true);
  }

  inference.begin();
}

void loop() {

  BHY2.update();

  unsigned long curr_time = millis();
  static unsigned long print_time = curr_time;

  if ((curr_time - print_time) >= INTERVAL_MS)
  {
    print_time = curr_time;
    inference.read(print_time);
  }

  indication();
}
