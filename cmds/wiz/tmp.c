// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
int main(object me, string arg)
{
	int *codes;
	string buf;
	seteuid(getuid());

	printf("arg=%s\n", arg);

	if (!arg || !stringp(arg) || sizeof(arg) < 2)
		return 1;

	printf("%d, %d\n", arg[0], strlen(arg));
	printf("%x, %x\n", arg[0], arg[1]);

	codes = decode_utf8(arg);
	printf("%O\n", codes);
	buf = encode_gb2312(codes);
	printf("converted: %s\n", buf);
	printf("%x,%x,%x,%x\n", buf[0],buf[1],buf[2],buf[3]);
	log_file("gb2312", buf);

    return 1;
}


