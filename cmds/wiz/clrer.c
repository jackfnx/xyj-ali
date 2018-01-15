// clear error

inherit F_CLEAN_UP;

int main(object me)
{
    me->delete_temp("error");
    write("Ok.\n");
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : clrer

等价于call me->delete("error")
HELP
    );
    return 1;
}
