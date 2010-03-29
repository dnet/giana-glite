#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXVAL 65535

double midi2freq(int midi) {
	return 440 * powf(1.05946309436, (midi - 69));
}

double osc_note = 0, osc_base = 0;

void play(int base, int midi, int len) {
	int val, i, samples = (int)floor(len / 1000.0 * SRATE);
	double t_note, t_base, s_note, s_base, foo, sample, dither;
	double f_note = midi2freq(midi), f_base = midi2freq(base);

	t_note = midi ? SRATE / f_note : 1;
	t_base = base ? SRATE / f_base : 1;

	for (i = 0; i < samples; i++) {
		s_note = modf(i / t_note + osc_note, &foo); /* 0 <= s < 1 */
		s_base = modf(i / t_base + osc_base, &foo);
		dither = rand() / (double)RAND_MAX;
		sample = (fabs(0.5 - s_note) * 0.55 + fabs(0.5 - s_base) * 0.45) * MAXVAL;
		val = (int)round(sample - dither);
		putchar((val & 0x00FF) >> 0);
		putchar((val & 0xFF00) >> 8);
	}

	osc_note = s_note;
	osc_base = s_base;
}

int wave(char *seq) {
	int note = 0, len = 0, base = 0, *input = &note;
	do {
		if (isdigit(seq[0])) {
			*input = 10 * (*input) + seq[0] - '0';
		} else {
			if (input == &len) {
				if (len == 0) {
					base = note;
				} else {
					play(base, note, len);
				}
				input = &note;
			} else {
				input = &len;
			}
			*input = 0;
		}
	} while (*(++seq));
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <sequence>\n", argv[0]);
		return 1;
	}

	return wave(argv[1]);
}
