// ALi by NewX

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    CHINESE_D->dump_translate();
    write("DUMP: /CHINESE_DUMP\n");
    return 1;
}

int help()
{
    write ( @HELP
dump the chinese translate to /CHINESE_DUMP.
HELP
    );
    return 1 ;
}
