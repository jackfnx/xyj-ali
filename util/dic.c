#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

const uint16_t DEFAULT_GBK = 0xA996;
const uint16_t DEFAULT_UCS2 = 0x3007;

iconv_t U2G;
iconv_t G2U;

void WideCodeToTwoBytes(uint16_t code, uint8_t *bytes)
{
    bytes[0] = code >> 8;
    bytes[1] = code & 0xFF;
}

int GBKtoUCS2(uint8_t *in, uint8_t *out)
{
    char *inbuf = (char *)in;
    char *outbuf = (char *)out;

    size_t inleft = 2;
    size_t outleft = 2;

    size_t n = iconv(G2U, &inbuf, &inleft, &outbuf, &outleft);

    if (n == -1)
    {
        out[0] = DEFAULT_UCS2 >> 8;
        out[1] = DEFAULT_UCS2 & 0xFF;
        return -1;
    }
    else
    {
        int len = 2 - (int)outleft;
        if (len != 2)
        {
            out[0] = DEFAULT_UCS2 >> 8;
            out[1] = DEFAULT_UCS2 & 0xFF;
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

int UCS2toGBK(uint16_t ucs2, uint8_t *gbk)
{
    uint8_t inbytes[2];
    uint8_t outbytes[8];
    
    WideCodeToTwoBytes(ucs2, inbytes);
    
    char *inbuf = (char *)&inbytes;
    char *outbuf = (char *)outbytes;

    size_t inleft = sizeof(inbytes);
    size_t outleft = sizeof(outbytes);

    size_t n = iconv(U2G, (char **)&inbuf, &inleft, (char **)&outbuf, &outleft);

    if (n == -1)
    {
        gbk[0] = DEFAULT_GBK >> 8;
        gbk[1] = DEFAULT_GBK & 0xFF;
        return -1;
    }
    else
    {
        int len = sizeof(outbytes) - (int)outleft;
        if (len != 2)
        {
            gbk[0] = DEFAULT_GBK >> 8;
            gbk[1] = DEFAULT_GBK & 0xFF;
            return -1;
        }
        else
        {
            gbk[0] = outbytes[0];
            gbk[1] = outbytes[1];
            return 0;
        }
    }
}

int generate_G2U(const char *fname, uint8_t from, uint8_t to)
{
    int cnt = 0;
    FILE *fp = fopen(fname, "w");
    uint8_t gbk[2];
    for (gbk[0] = from; gbk[0] <= to; gbk[0]++)
    {
        for (gbk[1] = 0x40; gbk[1] <= 0xFE; gbk[1]++)
        {
            uint8_t ucs2[2];
            cnt -= GBKtoUCS2(gbk, ucs2);
            fprintf(fp, "%02x%02x\n", ucs2[0], ucs2[1]);
        }
    }
    fclose(fp);
    return cnt;
}

int generate_U2G(const char *fname, uint16_t from, uint16_t to)
{
    int cnt = 0;
    FILE *fp = fopen(fname, "w");
    for (uint16_t ucs2 = from; ucs2 <= to; ucs2++)
    {
        uint8_t gbk[2];
        cnt -= UCS2toGBK(ucs2, gbk);
        fwrite(gbk, sizeof(gbk), 1, fp);
    }
    fclose(fp);
    return cnt;
}

int main(int argc, char **argv)
{
    U2G = iconv_open("GBK", "UTF-16BE");
    G2U = iconv_open("UTF-16LE", "GBK");
    if (U2G == (iconv_t)-1 || G2U == (iconv_t)-1)
    {
        perror("iconv_open()");
        exit(1);
    }

    int cnt;

    const int UCS2_AREA_0_LBOUND = 0x3000;
    const int UCS2_AREA_0_UBOUND = 0x4DFF;
    cnt = generate_U2G("U2G_0.dic", UCS2_AREA_0_LBOUND, UCS2_AREA_0_UBOUND);
    printf("<U2G_0.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           UCS2_AREA_0_UBOUND - UCS2_AREA_0_LBOUND + 1,
           UCS2_AREA_0_UBOUND - UCS2_AREA_0_LBOUND - cnt + 1,
           cnt);

    const int UCS2_AREA_1_LBOUND = 0x4E00;
    const int UCS2_AREA_1_UBOUND = 0x6DFF;
    cnt = generate_U2G("U2G_1.dic", UCS2_AREA_1_LBOUND, UCS2_AREA_1_UBOUND);
    printf("<U2G_1.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           UCS2_AREA_1_UBOUND - UCS2_AREA_1_LBOUND + 1,
           UCS2_AREA_1_UBOUND - UCS2_AREA_1_LBOUND - cnt + 1,
           cnt);

    const int UCS2_AREA_2_LBOUND = 0x6E00;
    const int UCS2_AREA_2_UBOUND = 0x8DFF;
    cnt = generate_U2G("U2G_2.dic", UCS2_AREA_2_LBOUND, UCS2_AREA_2_UBOUND);
    printf("<U2G_2.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           UCS2_AREA_2_UBOUND - UCS2_AREA_2_LBOUND + 1,
           UCS2_AREA_2_UBOUND - UCS2_AREA_2_LBOUND - cnt + 1,
           cnt);

    const int UCS2_AREA_3_LBOUND = 0x8E00;
    const int UCS2_AREA_3_UBOUND = 0x9DFF;
    cnt = generate_U2G("U2G_3.dic", UCS2_AREA_3_LBOUND, UCS2_AREA_3_UBOUND);
    printf("<U2G_3.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           UCS2_AREA_3_UBOUND - UCS2_AREA_3_LBOUND + 1,
           UCS2_AREA_3_UBOUND - UCS2_AREA_3_LBOUND - cnt + 1,
           cnt);

    const int GBK_AREA_0_LBOUND = 0x81;
    const int GBK_AREA_0_UBOUND = 0x8F;
    cnt = generate_G2U("G2U_0.dic", GBK_AREA_0_LBOUND, GBK_AREA_0_UBOUND);
    printf("<G2U_0.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_0_UBOUND - GBK_AREA_0_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_0_UBOUND - GBK_AREA_0_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);

    const int GBK_AREA_1_LBOUND = 0x90;
    const int GBK_AREA_1_UBOUND = 0x9F;
    cnt = generate_G2U("G2U_1.dic", GBK_AREA_1_LBOUND, GBK_AREA_1_UBOUND);
    printf("<G2U_1.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_1_UBOUND - GBK_AREA_1_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_1_UBOUND - GBK_AREA_1_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);

    const int GBK_AREA_2_LBOUND = 0xA0;
    const int GBK_AREA_2_UBOUND = 0xAF;
    cnt = generate_G2U("G2U_2.dic", GBK_AREA_2_LBOUND, GBK_AREA_2_UBOUND);
    printf("<G2U_2.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_2_UBOUND - GBK_AREA_2_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_2_UBOUND - GBK_AREA_2_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);

    const int GBK_AREA_3_LBOUND = 0xB0;
    const int GBK_AREA_3_UBOUND = 0xBF;
    cnt = generate_G2U("G2U_3.dic", GBK_AREA_3_LBOUND, GBK_AREA_3_UBOUND);
    printf("<G2U_3.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_3_UBOUND - GBK_AREA_3_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_3_UBOUND - GBK_AREA_3_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);
    
    const int GBK_AREA_4_LBOUND = 0xC0;
    const int GBK_AREA_4_UBOUND = 0xCF;
    cnt = generate_G2U("G2U_4.dic", GBK_AREA_4_LBOUND, GBK_AREA_4_UBOUND);
    printf("<G2U_4.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_4_UBOUND - GBK_AREA_4_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_4_UBOUND - GBK_AREA_4_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);
    
    const int GBK_AREA_5_LBOUND = 0xD0;
    const int GBK_AREA_5_UBOUND = 0xDF;
    cnt = generate_G2U("G2U_5.dic", GBK_AREA_5_LBOUND, GBK_AREA_5_UBOUND);
    printf("<G2U_5.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_5_UBOUND - GBK_AREA_5_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_5_UBOUND - GBK_AREA_5_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);
    
    const int GBK_AREA_6_LBOUND = 0xE0;
    const int GBK_AREA_6_UBOUND = 0xEF;
    cnt = generate_G2U("G2U_6.dic", GBK_AREA_6_LBOUND, GBK_AREA_6_UBOUND);
    printf("<G2U_6.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_6_UBOUND - GBK_AREA_6_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_6_UBOUND - GBK_AREA_6_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);
    
    const int GBK_AREA_7_LBOUND = 0xF0;
    const int GBK_AREA_7_UBOUND = 0xFE;
    cnt = generate_G2U("G2U_7.dic", GBK_AREA_7_LBOUND, GBK_AREA_7_UBOUND);
    printf("<G2U_7.dic> total: [%d], OK: [%d], ERR: [%d]\n",
           (GBK_AREA_7_UBOUND - GBK_AREA_7_LBOUND) * (0xFE - 0x80) + 1,
           (GBK_AREA_7_UBOUND - GBK_AREA_7_LBOUND) * (0xFE - 0x80) - cnt + 1,
           cnt);
    
    iconv_close(U2G);
    iconv_close(G2U);

	return 0;
}
