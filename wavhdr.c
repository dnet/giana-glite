#include <stdio.h>
#include <stdlib.h>

void ple(int val) {
	putchar((val & 0x000000FF) >> 0);
	putchar((val & 0x0000FF00) >> 8);
	putchar((val & 0x00FF0000) >> 16);
	putchar((val & 0xFF000000) >> 24);
}

void header(int datalen) {
	/*
	 * src: http://www.lightlink.com/tjweber/StripWav/Canon.html
	 *      https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
	 */
	/* RIFF header */
	printf("RIFF");
	ple(datalen + 36); /* file length - 8 */
	printf("WAVE");
	/* fmt */
	printf("fmt ");
	ple(16); /* fmt length */
	putchar(0x01); /* wave = 0x0001 */
	putchar(0x00);
	putchar(0x01); /* mono = 0x0001 */
	putchar(0x00);
	ple(SRATE); /* sample rate */
	ple(SRATE * 2); /* bitrate (16 bit mono) */
	putchar(0x02); /* block align = 0x0002 (16 bits) */
	putchar(0x00);
	putchar(0x10); /* bits per sample = 0x0010 (16 bits) */
	putchar(0x00);
	/* data */
	printf("data");
	ple(datalen);
}

int main(int argc, char **argv) {
	int datalen;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <data-length>\n", argv[0]);
		return 1;
	}

	if (!(datalen = atoi(argv[1]))) {
		fprintf(stderr, "Incorrect data length (must be nonzero number)\n");
		return 1;
	}

	header(datalen);
	return 0;
}

