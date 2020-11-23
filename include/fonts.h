// MIT License

// Copyright (c) 2020 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FONT_BIT(x) 				((char)0x01 << x)
#define FONT_MAX_DATA_LEN 			50

#define FONT_5x7_NUM_BYTE 			(7)        	/*!< Bytes lenght data */
#define FONT_5x7_NUM_MEMBER 		(96)     	/*!< Num char supported */
#define FONT_11x15_NUM_BYTE 		(15 * 2) 	/*!< Bytes lenght data */
#define FONT_11x15_NUM_MEMBER 		(96)   		/*!< Num char supported */

typedef enum {
	FONT_SIZE_5x7 = 0,							/*!< Font 5x7 */
	FONT_SIZE_11x15,							/*!< Font 11x15 */
	FONT_SIZE_MAX
} font_size_t;

typedef struct {
	char 			data[FONT_MAX_DATA_LEN];	/*!< Data */
	int 			data_len;					/*!< Num bytes data */
	uint8_t 		width;						/*!< Max pixel width to display */
	uint8_t 		height;						/*!< Max pixel height to display*/
	char 			ascii;						/*!< Character ASCII format */
} font_t;

/*
 * @brief	Get data from ASCII with font type.
 * @param   c Character ASCII format.
 * @param 	size Font size
 * @param  	font Pointer to font.
 * @return 
 * 		- (-1): Pointer to output font is null.
 * 		- 0: Input character is out of range.
 * 		- Others: Font width.
 */
int get_font(char c, font_size_t size, font_t *font);

extern const char font5x7_ref[FONT_5x7_NUM_MEMBER][FONT_5x7_NUM_BYTE];
extern const char font11x15_ref[FONT_11x15_NUM_MEMBER][FONT_11x15_NUM_BYTE];

#ifdef __cplusplus
}
#endif