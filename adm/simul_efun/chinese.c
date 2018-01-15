// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

string chinese_number(int i)
{
    return CHINESE_D->chinese_number(i);
}

int is_chinese(string str)
{
    if (strlen(str)>=2 && str[0] > 160 && str[0] < 255) return 1;
    else return 0;
}
