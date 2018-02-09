#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

void UCS2toGBK()
{
	vector<uint16_t> dic;
	FILE *fp = fopen("UCS2toGBK.dic", "r");
	for (uint16_t code = 0; fscanf(fp, "%hx", &code) == 1; ) {
		dic.push_back(code);
	}
	fclose(fp);
	
	while (1) {
		uint16_t ch;
		fread(&ch, sizeof(ch), 1, stdin);
		if (feof(stdin)) {
			break;
		}
		if (ch >= 0x4E00 && ch <= 0x9FBF) {
			uint16_t gbk = dic[ch - 0x4E00];
			printf("%c%c", gbk / 0x100, gbk % 0x100);
		} else if (ch <= 0x00FF) {
			printf("%c", ch);
		} else {
			printf("#");
		}
	}
}

void GBKtoUCS2()
{
	vector<uint16_t> dic;
	FILE *fp = fopen("GBKtoUCS2.dic", "r");
	for (uint16_t code = 0; fscanf(fp, "%hx", &code) == 1; ) {
		dic.push_back(code);
	}
	fclose(fp);
	
	uint16_t ch = 0;
	while (1) {
		uint8_t byte;
		fread(&byte, sizeof(byte), 1, stdin);
		if (feof(stdin)) {
			break;
		}
		if (ch != 0) {
			ch <<= 8;
			ch |= byte;
		} else {
			if (byte & 0x80) {
				ch = byte;
				continue;
			} else {
				ch = byte;
			}
		}
		if (ch >= 0x8140 && ch <= 0xFEFE) {
			uint16_t ucs2 = dic[ch - 0x8140];
			printf("%c%c", ucs2 / 0x100, ucs2 % 0x100);
		} else if (ch < 0x80) {
			printf("%c%c", 0, ch);
		} else {
			printf("%c%c", 0x23, 0x12);
		}
		ch = 0;
	}

}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "USAGE: %s [u2g|g2u]\n", argv[0]);
		return -1;
	}

	if (!strcasecmp(argv[1], "u2g")) {
		UCS2toGBK();
	} else if (!strcasecmp(argv[1], "g2u")) {
		GBKtoUCS2();
	} else {
		fprintf(stderr, "USAGE: %s [u2g|g2u]\n", argv[0]);
		return -1;
	}
	return 0;
}
