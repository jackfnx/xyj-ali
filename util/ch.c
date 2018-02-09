#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

const char* USAGE = "%s: [U|G] [LINE_LENGTH] [FROM:TO]\n";

char mode = 'U';
int length = 0;
int from = -1;
int to = -1;

void parse_args(int argc, char *argv[])
{
	char m = 'U';
	int l = 0;
	int f = 0;
	int t = 0;
	char *p = NULL;

	if (argc < 2) {
		fprintf(stderr, USAGE, argv[0]);
		exit(EXIT_FAILURE);
	} else {
		m = toupper(argv[1][0]);
		if (m != 'U' && m != 'G') {
			fprintf(stderr, USAGE, argv[0]);
			exit(EXIT_FAILURE);
		}
		mode = m;
	}

	if (argc >= 4) {
		if (sscanf(argv[2], "%x:%x", &f, &t) == 2 && ((l = strtol(argv[3], &p, 0)), argv[3] != p)) {
			length = l;
			from = f;
			to = t;
		} else if (sscanf(argv[3], "%x:%x", &f, &t) == 2 && ((l = strtol(argv[2], &p, 0)), argv[2] != p)) {
			length = l;
			from = f;
			to = t;
		} else {
			fprintf(stderr, USAGE, argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (argc >= 3) {
		if (sscanf(argv[2], "%x:%x", &f, &t) == 2) {
			from = f;
			to = t;
		} else if ((l = strtol(argv[2], &p, 0)), argv[2] != p) {
			length = l;
		} else {
			fprintf(stderr, USAGE, argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}

void UCS2()
{
	if (from < 0 || to < 0) {
		from = 0x4e00;
		to = 0x9dff;
	}
	for (uint16_t i = from; i <= to; i++)
	{
		if (length > 0 && (i - from) % length == 0) {
			char ansi[80] = {0};
			if (length > 1)
				sprintf(ansi, "\n%04x - %04x: ", i, i + length - 1);
			else
				ansi[0] = '\n';
			int len = strlen(ansi);
			char u16[80] = {0};
			for (int j = 0; j < len; j++) {
				u16[j * 2] = ansi[j];
				u16[j * 2+ 1] = 0;
			}
			fwrite(u16, sizeof(char), len * 2, stdout);
		}
		fwrite(&i, sizeof(i), 1, stdout);
	}
	if (length > 0) {
		fwrite("\x0A\x00", sizeof(char), 2, stdout);
	}
}

void GBK()
{
	uint8_t b[2];
	for (b[0] = 0x81; b[0] <= 0xFE; b[0]++) {
		for (b[1] = 0x40; b[1] <= 0xFE; b[1]++) {
			if (length > 0 && ((b[1] - 0x40) % length == 0)) {
				char offset[80] = {0};
				uint16_t f = b[0] * 0x100 + b[1];
				uint16_t t = f + length - 1;
				if (length > 1)
					sprintf(offset, "\n%04x - %04x: ", f, t);
				else
					offset[0] = '\n';
				int len = strlen(offset);
				fwrite(offset, sizeof(char), len, stdout);
			}
			fwrite(&b, sizeof(b), 1, stdout);
		}
	}
	fwrite("\n", sizeof(char), 1, stdout);
}

int main(int argc, char *argv[])
{
	parse_args(argc, argv);

	if (mode == 'U')
	 	UCS2();
	else if (mode == 'G')
	 	GBK();

	return 0;
}
