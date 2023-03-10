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


static const neuton_weight_t MODEL_WEIGHTS[] = {
	-45, 7, 19, -128, -128, -112, 100, -86, -49, 125, -117, -106, 26, 95, -17,
	50, 67, 120, -128, -6, 124, 35, 91, -27, -8, -5, -86, -83, 70, 93, 125,
	12, 41, -68, -15, -39, -66, 30, -3, 59, -128, 115, -11, -66, -76, 122,
	-76, -52, 125, -3, -60, -119, -9, -32, -96, 125, 0, 79, 23, 92, 74, 115,
	-86, -125, -98, 125, 36, 68, -78, -3, -83, 51, 63, -91, 82, -107, 0, -20,
	-42, 68, 89, 123, -7, -122, -69, 25, 18, -57, -19, 22, 117, -67, -127,
	-5, -31, -97, -128, -40, -17, -8, -4, -120, -52, 85, 19, -124, 15, -80,
	93, 93, -128, -68, -3, -128, -78, 43, -25, -88, 9, 18, 123, -87, -38, -128,
	-8, 65, -79, 61, -29, -72, -122, 4, 29, -81, -70, 29, -128, -35, -63, -128,
	-97, -125, 39, 38, 61, -67, -128, 41, -128, -119, 9, -15, -128, 116, 20,
	-50, -78, 11, -20, -126, 21, -115, -48, -34, 31, 122, -56, 29, 98, -84,
	-76, 1, -61, -125, 69, 108, -55, -67, 32, -71, -128, -128, -36, 31, -5,
	73, -128, -36, -31, 62, -50, -26, 58, 121, -103, -117, -14, 16, 48, -29,
	-65, -128, 64, -68, -128, -128, -87, -47, -74, 0, -89, -111, -128, -128,
	71, -128, 0, 82, -126, 121, -52, 68, -91, -124, -61, -33, -19, 38, -51,
	0, 32, 20, -56, 26, 123, -101, 33, -84, 119, -37, 29, 126, -120, 55, 2,
	-128, 28, -114, -64, 124, -110, 77, 24, -44, -121, 83, -54, -21, 14, -67,
	120, -29, -46, 78, -104, 0, -83, -98, -3, 115, -43, 72, -106, 124, -36,
	-128, -128, -2, -65, 61, -2, -128, 125, -111, -81, -114, 18, 0, -66, -62,
	29, -128, -34, -56, -35, -47, -99, -33, -128, -55, -120, 4, -8, -128, -128,
	-83, -122, -4, 14, -2, -30, -49, 124, -26, -16, 126, -100, -38, 105, 9,
	-128, 122, -69, 4, -97, -6, 57, -128, -122, -40, 114, -128, -128, 0, -128,
	120, -22, -124, -84, -59, -87, 0, 97, 4, -75, 107, -52, -78, -128, -17,
	-116, -128, 92, -20, 0, -43, -74, -28, 0, -128, 115, -40, -98, 125, -56,
	-74, 125, -66, -126, -56, 47, -128, 47, -17, -13, -60, -128, -53, 27, -70,
	41, -91, 121, 77, -128, 93, -35, 0, 13, -108, -128, 100, -128, -52, 3,
	115, -89, -62, -113, -53, 29, 29, -8, 25, 112, -105, -79, 69, -128, 93,
	-128, -72, 125, -128, -35, -3, 124, -128, -35, -108, 55, -46, 110, -52,
	-44, -14, 59, 124, 28, 32, -128, 98, -128, -128, -124, -128, 0, 47, 125,
	-49, -68, -47, -5, -48, -128, -128, -128, 54, 16, -58, 1, 125, 118, 125,
	33, -39, -122, -5, -77, 93, 116, -73, -72, -128, -77, 122, -25, -43, -46,
	-56, 0, -15, 125, 81, 113, -35, -128, 27, 17, -128, -128, -128, -92, 93,
	10, 9, 64, 83, -128, -102, 22, 15, -24, 40, 95, 124, 4, -113, 123, -49,
	-26, 109, 70, -116, 87, -113, -22, -127, 15, 21, 93, 117, -123, -2, -20,
	-82, -1, -65, 0, -101, -2, -128, -128, -128, -112, 38, -65, 0, 121, -97,
	-118, 39, 0, -89, 68, -128, -65, 58, 122, 84, 68, -128, -81, 52, -17, -26,
	124, 78, 35, -87, 30, -47, 122, -125, -126, -96, -22, -81, -3, -34, 29,
	-98, -68, -68, -3, -128, -128, 56, -77, -50, -56, 112, -38, -111, 26, -108,
	-32, -62, 28, -128, 100, -82, -75, 63, 33, -75, -128, -90, 78, -117, 36,
	1, -113, 38, -45, 116, -124, -128, -84, -4, -84, -128, -3, 74, -48, -4,
	30, 51, -105, -128, -52, -128, 0, 42, -72, -125, -59, -46, 111, 1, -11,
	-92, 117, 62, -67, -8, -128, -114, 83, 124, 37, -53, 14, 6, 0, -84, 103,
	-16, -77, 108, 79, -125, -58, -74, 4, -125, -84, 20, 122, -128, 34, 31,
	-125, -128, 64, -116, -4, -128, 82, -25, -26, -128, -82, 25, 8, -128, -128,
	-113, -34, 3, -128, -5, 47, -128, 120, -128, 61, 111, 0, -128, -28, 78,
	36, -121, -4, 118, -120, -128, -128, -102, 80, 0, -62, -128, 105, -32,
	49, -117, 0, 95, -128, 122, -83, -11, -37, -49, 62, -128, 71, 12, -73,
	-33, -122, 37, -52, -45, -2, -128, -84, 37, -128, 104, 18, -59, 8, -32,
	57, -26, 121, 30, -67, -128, 44, -94, -78, -128, -5, -104, 125, -125, -4,
	-128, -4, 79, -128, 16, -24, -51, -120, 0, -71, 20, 40, 10, -121, -44,
	-75, -71, 67, -11, -9, 20, 18, -114, 79, -87, -66, 51, -128, -99, -41,
	-128, -128, 116, -128, 47, -33, 106, 70, 46, -126, -95, -121, -128, 105,
	-128, -128, 35, -14, 44, -84, -111, 44, -128, 120, -128, 125, 32, 112,
	-128, -128, 123, 125, -128, 72, -128, 30, -85, 47, -128, -25, -30, -120,
	48, -126, 100, 83, 79, 63, 124, -27, -82, -87, 0, -28, 125, -128, -7, -91,
	109, 28, -72, -2, -83, 49, -128, -115, -128, -124, -126, -122, 0, 104,
	-128, -75, -125, -61, -103, 0, -40, 56, 124, 71, -125, -18, 49, 20, -88,
	86, -36, -41, 28, 8, -3, 124, -128, 50, -55, -42, -125, -2, -25, -80, -20,
	-128, -74, -128, -5, 76, -128, 116, -128, -47, -41, 33, -101, -128, -93,
	21, 1, -128, -3, 42, 122, -99, -119, -3, 5, 124, 125, -46, 78, -125, -16,
	120, -127, 61, 124, 21, -93, 9, 23, 110, -128, 106, -128, -67, 31, -60,
	124, -110, 32, -85, 99, -51, -6, 124, -90, -128, 38, 0, 69, 58, 5, -70,
	-47, 33, -102, 52, -66, -128, -122, 93, -128, -39, -6, -45, -128, -112,
	60, -30, -116, -128, -4, -57, -42, -128, -89, -127, -108, 4, -128, -14,
	-128, 66, -97, -60, -5, 71, -128, -128, -128, -88, -120, -5, -128, -128,
	-86, -27, -94, -36, 0, -128, 2, 117, -42, -127, 79, 37, -4, -128, 123,
	-115, -62, -93, -92, 0, -116, -110, 70, -104, -128, -128, -4, -23, 125,
	124, -127, 77, -104, -53, -4, -128, 62, 85, -59, -46, -18, 103, -81, 43,
	-128, 72, -98, -122, -23, -36, -128, -113, 28, -53, -128, -3, -128, -128,
	20, 28, -59, -34, -82, -34, 125, -128, 0, 125, -98, -21, 31, -128, 69,
	-110, -39, -125, -111, 0, 62, -78, 105, -17, 19, -96, -13, -87, 84, -109,
	125, 16, -128, 125, -14, -128, 103, 118, 109, 123, -128, -33, -128, 125,
	121, 125, 125, -30, -128, 125, -21, -23, -128, 87, -128, 125, -25, 125,
	-25, -128, 125, -128, -114, 125, 125, -128, 125, -2, 125, 125, -128, -5,
	-128, 125, -128, 125, -33, 125, 33, -128, -28, 125, 125, -57, 125, -17,
	-109, 31, -50, 125, -128, 125, -53, -125, 125, -128, 125, -128, 127, -108,
	-128, -128, 125, 112, -128, 13, -128, 110, -56, 13, 5, -128, -115, -119,
	16, 60, 8, -12, 22, 9, -64, -128, 33, -128, -128, -60, 125, 20, -119, -87,
	0, -91, -96, -128, -77, -128, -92, 0, 38, 120, -83, 49, 75, -103, 29, -44,
	-128, -128, -128, -128, -84, 76, -128, 0, -128, 69, 114, 29, -109, -115,
	-34, -2, -44, -45, -79, -128, -54, -128, -30, 126, -128, -51, 50, -70,
	46 };

static const neuton_sources_num_t MODEL_LINKS[] = {
	14, 39, 48, 51, 55, 66, 78, 38, 46, 50, 51, 66, 78, 0, 14, 30, 37, 38,
	69, 78, 0, 21, 32, 61, 74, 78, 1, 16, 34, 60, 62, 66, 78, 0, 17, 45, 71,
	77, 78, 5, 11, 12, 29, 43, 57, 68, 78, 1, 6, 78, 2, 7, 17, 23, 45, 46,
	78, 6, 18, 34, 47, 70, 76, 78, 5, 8, 1, 30, 59, 78, 6, 2, 8, 42, 69, 75,
	78, 2, 4, 9, 56, 77, 78, 8, 8, 17, 29, 35, 78, 3, 13, 25, 26, 29, 78, 5,
	13, 4, 27, 62, 78, 8, 18, 28, 36, 43, 78, 0, 11, 58, 64, 66, 78, 17, 24,
	30, 35, 63, 78, 10, 3, 16, 41, 42, 78, 15, 21, 34, 44, 61, 74, 78, 14,
	16, 12, 29, 58, 78, 15, 19, 7, 55, 57, 75, 78, 3, 22, 29, 32, 35, 78, 4,
	1, 11, 21, 29, 36, 78, 16, 21, 12, 24, 39, 48, 78, 0, 1, 9, 16, 27, 37,
	78, 3, 9, 40, 49, 58, 78, 5, 14, 21, 4, 16, 22, 78, 7, 43, 46, 55, 65,
	78, 12, 18, 34, 55, 71, 78, 14, 37, 47, 62, 68, 78, 6, 15, 22, 31, 14,
	77, 78, 4, 18, 22, 6, 10, 19, 78, 24, 4, 42, 65, 68, 78, 14, 4, 18, 22,
	45, 60, 78, 10, 14, 15, 53, 61, 78, 21, 14, 24, 37, 41, 55, 78, 1, 18,
	21, 30, 69, 78, 32, 14, 23, 29, 62, 68, 78, 32, 34, 52, 65, 68, 70, 78,
	40, 27, 49, 66, 75, 78, 0, 1, 1, 23, 66, 78, 35, 38, 26, 42, 49, 78, 33,
	16, 26, 29, 34, 49, 78, 21, 34, 16, 36, 46, 74, 78, 2, 22, 23, 33, 1, 6,
	78, 10, 18, 24, 28, 27, 78, 1, 30, 14, 29, 76, 78, 1, 17, 42, 43, 71, 78,
	45, 20, 24, 42, 75, 78, 34, 40, 42, 5, 59, 69, 76, 78, 8, 13, 3, 23, 34,
	43, 56, 78, 44, 14, 28, 55, 68, 78, 15, 1, 3, 7, 30, 74, 78, 1, 13, 14,
	50, 61, 65, 78, 2, 31, 33, 50, 66, 78, 39, 3, 7, 27, 44, 78, 4, 6, 17,
	68, 72, 75, 78, 3, 16, 18, 22, 10, 28, 78, 5, 10, 18, 22, 53, 16, 78, 45,
	38, 44, 53, 75, 78, 4, 10, 4, 40, 50, 78, 12, 14, 21, 6, 9, 60, 67, 73,
	78, 44, 53, 44, 46, 55, 78, 0, 1, 2, 3, 23, 36, 61, 78, 24, 29, 44, 57,
	40, 69, 78, 9, 19, 49, 66, 75, 78, 10, 20, 25, 26, 39, 59, 65, 78, 31,
	41, 57, 10, 48, 56, 78, 65, 0, 16, 26, 69, 78, 18, 22, 50, 70, 22, 72,
	78, 3, 22, 30, 44, 13, 21, 78, 8, 22, 37, 72, 14, 32, 34, 78, 5, 42, 53,
	57, 66, 75, 78, 8, 13, 52, 17, 42, 68, 78, 10, 13, 3, 31, 61, 63, 78, 13,
	19, 33, 20, 44, 68, 78, 3, 12, 43, 10, 35, 69, 78, 8, 15, 39, 1, 27, 75,
	78, 0, 48, 0, 2, 8, 49, 78, 80, 16, 29, 43, 46, 54, 68, 76, 78, 3, 4, 55,
	4, 30, 57, 78, 16, 27, 63, 71, 73, 48, 58, 78, 4, 71, 10, 34, 51, 78, 23,
	77, 1, 26, 34, 35, 68, 78, 19, 69, 9, 29, 70, 78, 10, 45, 16, 23, 60, 78,
	6, 84, 1, 5, 44, 70, 78, 2, 16, 18, 21, 25, 86, 77, 78, 12, 11, 49, 51,
	74, 78, 15, 28, 52, 85, 3, 73, 78, 20, 34, 55, 69, 70, 78, 16, 1, 12, 58,
	70, 78, 17, 91, 0, 9, 73, 78, 5, 63, 81, 49, 51, 66, 78, 39, 91, 11, 35,
	48, 74, 78, 0, 8, 16, 21, 59, 78, 6, 87, 89, 10, 48, 78, 28, 1, 28, 47,
	64, 68, 78, 23, 47, 49, 68, 79, 96, 34, 78, 34, 37, 62, 5, 67, 77, 78,
	95, 3, 16, 29, 68, 78, 29, 93, 97, 28, 49, 64, 78, 3, 33, 54, 3, 38, 71,
	78, 52, 67, 78, 20, 22, 78, 10, 2, 60, 68, 76, 78, 58, 65, 71, 21, 74,
	78, 9, 10, 12, 13, 24, 33, 16, 78, 50, 61, 31, 34, 62, 78, 2, 20, 22, 35,
	69, 78, 17, 22, 65, 29, 43, 78, 6, 19, 10, 16, 40, 69, 78, 10, 63, 29,
	45, 54, 78, 3, 9, 14, 17, 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
	78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
	96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
	111, 112, 113, 78, 0, 1, 3, 13, 14, 31, 59, 78, 11, 48, 70, 73, 22, 61,
	78, 2, 8, 116, 78, 9, 45, 66, 84, 0, 55, 78, 31, 43, 72, 75, 45, 53, 78,
	24, 57, 66, 34, 46, 51, 78, 26, 70, 79, 14, 42, 44, 48, 78, 34, 78, 5,
	8, 23, 53, 78, 14, 44, 50, 34, 61, 76, 78, 3, 9, 52, 85, 96, 6, 78, 20,
	58, 3, 48, 55, 78, 46, 8, 21, 27, 74, 78, 40, 87, 96, 102, 14, 58, 78,
	52, 102, 106, 0, 21, 64, 78, 34, 74, 75, 111, 115, 16, 78, 1, 6, 16, 37,
	59, 75, 78, 3, 19, 67, 81, 96, 103, 11, 78, 37, 3, 42, 58, 71, 74, 78,
	63, 86, 115, 116, 0, 78, 39, 62, 83, 11, 21, 48, 78, 39, 42, 75, 7, 31,
	33, 45, 78, 2, 5, 53, 70, 80, 56, 78, 60, 75, 92, 113, 74, 75, 78, 14,
	15, 67, 113, 1, 6, 78, 32, 57, 86, 3, 53, 62, 78, 0, 42, 78, 5, 49, 58,
	73, 78, 40, 55, 78, 103, 49, 76, 78, 39, 92, 29, 62, 64, 70, 78, 6, 31,
	126, 53, 63, 71, 72, 78, 13, 110, 18, 26, 48, 78, 19, 112, 113, 141, 13,
	28, 42, 78, 3, 60, 78, 85, 128, 23, 78, 39, 141, 2, 55, 68, 78, 3, 4, 40,
	108, 7, 39, 78, 2, 13, 22, 32, 75, 1, 73, 77, 78, 0, 5, 11, 12, 13, 15,
	18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
	54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 118, 119, 120, 121, 122, 123,
	124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138,
	139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 78, 0, 1, 2, 3,
	89, 116, 51, 78, 0, 1, 2, 3, 23, 82, 35, 68, 78, 55, 67, 75, 119, 4, 53,
	56, 78, 6, 24, 76, 99, 145, 24, 78, 5, 100, 109, 9, 48, 52, 78, 2, 43,
	130, 149, 154, 3, 21, 45, 78, 13, 22, 52, 123, 146, 153, 14, 78, 4, 10,
	16, 66, 115, 151, 152, 153, 154, 155, 156, 157, 78 };

static const neuton_weights_num_t MODEL_INTERNAL_LINKS_BOUNDARIES[] = {
	0, 7, 14, 21, 26, 34, 40, 49, 51, 58, 66, 71, 79, 84, 89, 97, 102, 109,
	114, 120, 125, 134, 140, 145, 152, 160, 169, 174, 181, 185, 192, 197, 207,
	213, 218, 224, 231, 237, 245, 250, 256, 264, 271, 277, 282, 290, 299, 306,
	310, 315, 321, 329, 336, 343, 349, 355, 363, 369, 377, 385, 393, 396, 403,
	410, 418, 428, 434, 439, 450, 454, 459, 468, 475, 482, 487, 496, 502, 510,
	517, 524, 530, 536, 547, 556, 561, 567, 575, 581, 587, 598, 601, 610, 615,
	620, 627, 634, 640, 645, 654, 658, 670, 675, 680, 688, 695, 702, 706, 714,
	723, 727, 731, 740, 745, 752, 808, 814, 821, 827, 832, 839, 845, 852, 859,
	867, 876, 880, 885, 894, 900, 909, 913, 924, 927, 937, 942, 949, 959, 965,
	972, 978, 985, 994, 999, 1007, 1014, 1022, 1031, 1035, 1043, 1051, 1140,
	1147, 1155, 1162, 1171, 1176, 1185, 1195, 1209 };

static const neuton_weights_num_t MODEL_EXTERNAL_LINKS_BOUNDARIES[] = {
	7, 13, 20, 26, 33, 39, 47, 50, 57, 64, 70, 77, 83, 89, 95, 101, 107, 113,
	119, 125, 132, 138, 145, 151, 158, 165, 172, 178, 185, 191, 197, 203, 210,
	217, 223, 230, 236, 243, 249, 256, 263, 269, 275, 281, 288, 295, 302, 308,
	314, 320, 326, 334, 342, 348, 355, 362, 368, 374, 381, 388, 395, 401, 407,
	416, 422, 430, 437, 443, 451, 458, 464, 471, 478, 486, 493, 500, 507, 514,
	521, 528, 535, 544, 551, 559, 565, 573, 579, 585, 592, 600, 606, 613, 619,
	625, 631, 638, 645, 651, 657, 664, 672, 679, 685, 692, 699, 705, 711, 717,
	725, 731, 737, 743, 750, 756, 809, 817, 824, 828, 835, 842, 849, 857, 864,
	871, 878, 884, 890, 897, 904, 911, 918, 926, 933, 939, 946, 954, 961, 968,
	975, 982, 990, 997, 1004, 1012, 1018, 1026, 1033, 1039, 1046, 1055, 1141,
	1149, 1158, 1166, 1173, 1180, 1189, 1197, 1210 };

static const neuton_coeff_t MODEL_ACTIVATION_COEFFS[] = {
	160, 160, 160, 157, 68, 152, 60, 81, 160, 75, 154, 105, 82, 88, 158, 143,
	144, 157, 147, 157, 144, 149, 123, 122, 160, 89, 157, 57, 111, 157, 125,
	96, 158, 155, 150, 114, 122, 157, 157, 160, 133, 112, 157, 155, 160, 146,
	157, 158, 159, 157, 157, 158, 146, 123, 126, 157, 159, 156, 146, 157, 92,
	147, 74, 157, 160, 52, 160, 156, 129, 147, 144, 155, 157, 148, 156, 153,
	131, 160, 115, 157, 160, 160, 134, 122, 157, 158, 158, 110, 158, 134, 106,
	147, 153, 71, 157, 160, 100, 154, 157, 153, 117, 160, 160, 151, 154, 86,
	158, 115, 131, 154, 157, 157, 157, 122, 110, 134, 160, 158, 132, 158, 151,
	157, 136, 160, 149, 144, 157, 148, 159, 113, 157, 155, 158, 157, 157, 157,
	140, 158, 156, 109, 89, 157, 160, 157, 104, 104, 145, 66, 144, 160, 160,
	160, 146, 160, 160, 147, 157, 140, 113 };

static const neuton_neurons_num_t MODEL_OUTPUT_NEURONS[] = {
	150, 7, 117, 114, 158 };

