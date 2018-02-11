// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

int main(object me, string arg)
{
	string str;
    int *codes;
	seteuid(getuid());

    arg = "/adm/etc/motd";
    str = read_file(arg);//"★";//
    printf("utf8\n%s\n", str);
    codes = CONVERT_D->decode_utf8(str);
    printf("%O\n", codes);
	str = CONVERT_D->UTF8toGB2312(str);
	printf("gb:\n%02x%02x\n", str[0], str[1]);
	log_file("gb2312", str);

    return 1;
}
