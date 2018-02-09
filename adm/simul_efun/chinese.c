// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

string chinese_number(int i)
{
    return CHINESE_D->chinese_number(i);
}

int is_chinese(string str)
{
    int *codes = CONVERT_D->decode_utf8(str);
    for (int i = 0; i < sizeof(codes); i++) {
        if (codes[i] <= 0x4E00 || codes[i] >= 0x9FFF) // hanzi qujian
            return 0;
    }
    return 1;
}
