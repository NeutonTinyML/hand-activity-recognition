#ifndef _NEUTON_NN_INFERENCE_ENGINE_H_
#define _NEUTON_NN_INFERENCE_ENGINE_H_

#include "../../../neuton_generated/neuton_user_types.h"

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Make inference based on the internal Neuton model, 
 *        to get results use @ref nn_engine_get_inference_results
 * 
 * @param[in] p_input_features          Input(LAG) features, can be NULL if not used by model
 * @param[in] p_extracted_features      Extracted DSP features, can be NULL if not used by model
 */
void nn_engine_make_inference(const neuton_input_t* p_input_features,
                                    const neuton_feature_t* p_extracted_features);

/**
 * @brief Get Neuton model inference results
 * 
 * @param[out] p_index        Index of predicted target(class) with highest probability, can be NULL. 
 * @param[out] pp_outputs     Pointer to set pointer to the internal buffer with all predicted outputs,
 *                            contains predicted target variable (for regression task) or probabilities 
 *                            of each class (binary/multi classification), can be NULL.

 * 
 * @return neuton_i16_t Number of the predicted outputs
 */
neuton_i16_t nn_engine_get_inference_results(neuton_u16_t* p_index, 
                                                   const neuton_output_t** pp_outputs);

/**
 * @brief Quantized sigmoid activation function
 * @warning Only for internal use
 * 
 * @param[in] acc           Neuron accumulator
 * 
 * @return neuton_coeff_t   Activated coefficient 
 */
neuton_coeff_t nn_activation_sigmoid_q(neuton_accum_t acc);

/**
 * @brief Get Neuton model size in bytes
 */
neuton_u32_t nn_engine_model_size(void);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_NN_INFERENCE_ENGINE_H_ */