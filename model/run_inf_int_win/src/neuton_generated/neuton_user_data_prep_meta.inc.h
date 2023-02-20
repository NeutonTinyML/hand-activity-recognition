/* 2023-02-13T10:48:08Z */

/* ----------------------------------------------------------------------
Copyright (c) 2022-2023 Neuton.AI, Inc.
*
The source code and its binary form are being made available on the following terms:
Redistribution, use, and modification are permitted provided that the following
conditions are met:
*
1. Redistributions of source code and/or its binary form must retain the above copyright notice,
* this list of conditions (and the disclaimer) either in the body of the source code or in
* the documentation and/or other materials provided with the distribution of the binary form, as
applicable.
*
2. The name of the copyright holder may not be used to endorse or promote products derived from this
* source code or its binary form without specific prior written permission of Neuton.AI, Inc.
*
3. Disclaimer. THIS SOURCE CODE AND ITS BINARY FORM ARE PROVIDED BY THE COPYRIGHT HOLDER "AS IS".
* THE COPYRIGHT HOLDER HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS
* OF THIRD PARTIES; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE OR ITS BINARY FORM, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------- */

/** Defines input(also used for LAG) features MIN scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MIN[] = { 0 };

/** Defines input(also used for LAG) features MAX scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MAX[] = { 0 };

/** Defines which unique input features is used for LAG features processing,
 *  one bit for one unique feature, starting from LSB
 */
static const neuton_u8_t INPUT_FEATURES_USED_FOR_LAGS_MASK[] = { 0x00 };

/** Defines DSP feature calculation masks used as neuton_dsp_features_mask_t,
 *  32 bit for one unique feature, @ref neuton_dsp_features_mask_t to see bitmask
 */
static const neuton_u32_t DSP_FEATURES_CALCULATION_MASK[] = { 939458560 };

/** Defines DSP feature calculation arguments used by DSP pipeline,
 *  32 bit for one feature argument
 */
static const neuton_input_t DSP_FEATURES_CALCULATION_ARGS[] = {
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

/** Defines DSP features MAX scaling factor
 */
static const neuton_feature_t DSP_FEATURES_SCALE_MIN[] = {
	-32768, -4044, 24, -5075, 3, -44402, 4117, 5, 21, 0, 0, 14, 13, -22743,
	-3619, 19, -6647, 2, -51077, 4111, 4, 5, 0, 0, 10, 12, -29597, -3971, 19,
	-4187, 3, -44195, 4134, 4, 38, 0, 0, 11, 13, -30021, -334, 21, -2520, 3,
	-46554, 5165, 4, 4, 0, 0, 11, 12, -19972, -1671, 17, -4667, 2, -51561,
	5362, 3, 4, 0, 0, 8, 11, -28273, -49, 17, -3517, 2, -43504, 5210, 4, 4,
	0, 0, 8, 13 };

/** Defines DSP features MIN scaling factor
 */
static const neuton_feature_t DSP_FEATURES_SCALE_MAX[] = {
	3814, 19657, 51537, 4262, 7077, 49645, 665984, 8337, 8958, 48, 34, 37982,
	40456, 4028, 18574, 32463, 4504, 6071, 49053, 694272, 6767, 7739, 50, 44,
	26202, 24567, 4061, 31815, 44453, 4798, 6849, 49803, 646256, 7900, 8566,
	50, 21, 29872, 40740, 236, 22589, 51929, 1660, 6429, 49191, 634304, 7697,
	7719, 47, 47, 38049, 40324, 233, 15366, 30318, 830, 5799, 51166, 703168,
	6472, 6493, 58, 53, 23653, 24405, 353, 31294, 43655, 1153, 6179, 47786,
	637056, 7362, 7373, 50, 46, 29108, 40515 };

