#include "fonts.h"
#include "stdbool.h"

#define FONT_BIT(x) 			((char)0x01 << x)
#define FONT_ASCII_OFFSET 		0x20

extern const char font5x8_ref[FONT_5x8_NUM_MEMBER * FONT_5x8_NUM_BYTE];
extern const char font12x16_ref[FONT_12x16_NUM_MEMBER * FONT_12x16_NUM_BYTE];
extern const char font16x32_ref[FONT_16x32_NUM_MEMBER * FONT_16x32_NUM_BYTE];
extern const char font25x57_ref[FONT_25x57_NUM_MEMBER * FONT_25x57_NUM_BYTE];

int get_font(char c, font_size_t size, font_t *font)
{
	int idx, byte_per_row, num_row, max_width;

	if (font == NULL) {
		return -1;
	}

	switch (size) {
	case FONT_SIZE_5x8:
		byte_per_row = 1;
		num_row = 8;
		idx = c - FONT_ASCII_OFFSET;
		if (idx < 0 || idx > FONT_5x8_NUM_MEMBER) {
			return 0;
		}
		font->data_len = num_row * byte_per_row;
		font->height = num_row;
		font->ascii = c;
		memcpy(font->data, (char*)&font5x8_ref[idx * FONT_5x8_NUM_BYTE], font->data_len);

		if (font->ascii == 0x20) {
			font->width = 3;
			break;
		}

		max_width = 0;
		for (int row = 0; row < (int)font->height; row++) {
			int _width = 8 * byte_per_row;
			for (int bit = 0; bit < 8; bit++) {
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

	case FONT_SIZE_12x16:
		byte_per_row = 2;
		num_row = 16;
		idx = c - FONT_ASCII_OFFSET;
		if (idx < 0 || idx > FONT_12x16_NUM_MEMBER) {
			return 0;
		}
		font->data_len = num_row * byte_per_row;
		font->height = num_row;
		font->ascii = c;
		memcpy(font->data, (char*)&font12x16_ref[idx * FONT_12x16_NUM_BYTE], font->data_len);

		if (font->ascii == 0x20) {
			font->width = 6;
			break;
		}

		max_width = 0;
		for (int row = 0; row < (int)font->height; row++) {
			int _width = 8 * byte_per_row;
			bool out = false;
			for (int byte = 1; byte > -1; byte--) {
				for (int bit = 0; bit < 8; bit++) {
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
	case FONT_SIZE_16x32:
		byte_per_row = 2;
		num_row = 32;
		idx = c - FONT_ASCII_OFFSET;
		if (idx < 0 || idx > FONT_16x32_NUM_MEMBER) {
			return 0;
		}
		font->data_len = num_row * byte_per_row;
		font->height = num_row;
		font->ascii = c;
		memcpy(font->data, (char*)&font16x32_ref[idx * FONT_16x32_NUM_BYTE], font->data_len);

		if (font->ascii == 0x20) {
			font->width = 6;
			break;
		}

		max_width = 0;
		for (int row = 0; row < (int)font->height; row++) {
			int _width = 8 * byte_per_row;
			bool out = false;
			for (int byte = 1; byte > -1; byte--) {
				for (int bit = 0; bit < 8; bit++) {
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
	case FONT_SIZE_25x57:
		byte_per_row = 4;
		num_row = 57;
		idx = c - FONT_ASCII_OFFSET;
		if (idx < 0 || idx > FONT_25x57_NUM_MEMBER) {
			return 0;
		}
		font->data_len = num_row * byte_per_row;
		font->height = num_row;
		font->ascii = c;
		memcpy(font->data, (char*)&font25x57_ref[idx * FONT_25x57_NUM_BYTE], font->data_len);

		if (font->ascii == 0x20) {
			font->width = 6;
			break;
		}

		max_width = 0;
		for (int row = 0; row < (int)font->height; row++) {
			int _width = 8 * byte_per_row;
			bool out = false;
			for (int byte = 1; byte > -1; byte--) {
				for (int bit = 0; bit < 8; bit++) {
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