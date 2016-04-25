#include "JPEGdefs.h"
#include "Htables.h"

int BitSize(int value) {
	fprintf(stdout, "in BitSize()\n");
	int bitsize = 0;

	if (value < 0) {
		value *= -1;
	}

	while (value > 0) {
		bitsize++;
		value >>= 1;
	}

	printf("bitsize = %d\n", bitsize);
	return bitsize;
}

void VLI_encode(int bitsz, int value, char *block_code) {
	fprintf(stdout, "in VLI_encode()\n");
	int i;
	char VLI[13] = { 0 };

	if (value < 0) {
		value--;
	}

	for (i = bitsz - 1; i >= 0; i--) {
		VLI[i] = (value & 1) ? '1' : '0';
		value >>= 1;
	}

	strcat(block_code, VLI);
}

void ZigZag(int ** img, int y, int x, int *zigline) {
	fprintf(stdout, "in ZigZag()\n");
	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			zigline[Zig[i][j]] = img[y+i][x+j];
		}
	}
}

void DC_encode(int dc_value, int prev_value, char *block_code) {
	fprintf(stdout, "in DC_encode()\n");
	int diff, size;

	diff = dc_value - prev_value;
	printf("diff = %d\n", diff);
	size = BitSize(diff);

	strcat(block_code, dcHuffman.code[size]);
	VLI_encode(size, diff, block_code);
}

void AC_encode(int *zigzag, char *block_code) {
	fprintf(stdout, "in AC_encode()\n");
	int idx = 1;
	int zerocnt = 0;
	int bitsize;

	while (idx < 64) {
		if (zigzag[idx] == 0) {
			zerocnt++;
		} else {
			for (; zerocnt > 15; zerocnt -= 16) {
				strcat(block_code, acHuffman.code[15][0]);
			}

			bitsize = BitSize(zigzag[idx]);
			strcat(block_code, acHuffman.code[zerocnt][bitsize]);
			VLI_encode(bitsize, zigzag[idx], block_code);

			zerocnt = 0;
		}

		idx++;
	}

	if (zerocnt) {
		strcat(block_code, acHuffman.code[0][0]);
	}
}

void Block_encode(int prev_value, int *zigzag, char *block_code) {
	fprintf(stdout, "in Block_encode()\n");
	DC_encode(zigzag[0], prev_value, block_code);
	AC_encode(zigzag, block_code);
}

int Convert_encode(char *block_code, unsigned char *byte_code) {
	fprintf(stdout, "in Convert_encode()\n");
	int len = strlen(block_code);
	int bytes = len / 8;
	int idx;
	int i, j;

	idx = 0;
	for (i = 0; i < bytes; i++) {
		for (j = 0; j < 8; j++) {
			byte_code[idx] <<= 1;

			if (block_code[i*8 + j] == '1') {
				byte_code[idx]++;
			}
		}

		if (byte_code[idx] == 0xff) {
			byte_code[++idx] == 0x00;
			bytes++;
		}

		idx++;
	}

	strcpy(block_code, block_code + len / 8 * 8);

	return bytes;
}

unsigned char Zero_pad(char *block_code) {
	fprintf(stdout, "Zero_pad()\n");
	unsigned char val;
	int len;
	int i;

	len = strlen(block_code);
	for (i = 0; i < len; i++) {
		val <<= 1;

		if (block_code[i] == '1') {
			val++;
		}
	}

	val <<= (8 - len);

	return val;
}
