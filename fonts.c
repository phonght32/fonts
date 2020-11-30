#include "fonts.h"
#include "stdbool.h"

#define FONT_BIT(x) 			((char)0x01 << x)
#define FONT_ASCII_OFFSET 		0x20

extern const char font5x7_ref[FONT_5x7_NUM_MEMBER * FONT_5x7_NUM_BYTE];
extern const char font11x15_ref[FONT_11x15_NUM_MEMBER * FONT_11x15_NUM_BYTE];

int get_font(char c, font_size_t size, font_t *font)
{
	int idx, byte_per_row, num_row, max_width;

	if (font == NULL) {
		return -1;
	}

	switch (size) {
	case FONT_SIZE_5x7:
		byte_per_row = 1;
		num_row = 7;
		idx = c - FONT_ASCII_OFFSET;
		if (idx < 0 || idx > FONT_5x7_NUM_MEMBER) {
			return 0;
		}
		font->data_len = num_row * byte_per_row;
		font->height = num_row;
		font->ascii = c;
		memcpy(font->data, (char*)&font5x7_ref[idx * FONT_5x7_NUM_BYTE], font->data_len);

		if (font->ascii == 0x20) {
			font->width = 3;
			break;
		}

		max_width = 0;
		for (int row = 0; row < (int)font->height; row++) {
			int _width = 8 * byte_per_row;
			for (int bit = 7; bit > -1; bit--) {
				if ((font->data[row] & FONT_BIT(bit)) == FONT_BIT(bit)) {
					break;
				} else {
					_width--;
				}
			}
			max_width = (max_width < _width) ? _width : max_width;
		}
		font->width = max_width;
		break;

	case FONT_SIZE_11x15:
		byte_per_row = 2;
		num_row = 15;
		idx = c - FONT_ASCII_OFFSET;
		if (idx < 0 || idx > FONT_11x15_NUM_MEMBER) {
			return 0;
		}
		font->data_len = num_row * byte_per_row;
		font->height = num_row;
		font->ascii = c;
		memcpy(font->data, (char*)&font11x15_ref[idx * FONT_11x15_NUM_BYTE], font->data_len);

		if (font->ascii == 0x20) {
			font->width = 6;
			break;
		}

		max_width = 0;
		for (int row = 0; row < (int)font->height; row++) {
			int _width = 8 * byte_per_row;
			bool out = false;
			for (int byte = 0; byte < byte_per_row; byte++) {
				for (int bit = 7; bit > -1; bit--) {
					if ((font->data[byte + row * 2] & FONT_BIT(bit)) == FONT_BIT(bit)) {
						out = true;
						break;
					} else {
						_width--;
					}
				}
				if (out)
					break;
			}
			max_width = (max_width < _width) ? _width : max_width;
		}
		font->width = max_width;
		break;
	default:
		break;
	}
	return font->width;
}