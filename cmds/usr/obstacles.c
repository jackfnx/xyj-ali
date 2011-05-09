inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me, string arg)
{
    object ob;
    string opt;

    if (!arg || arg == "-qujing") {
        ob = me;
        opt = "qujing";
    } else if (arg == "-dntg") {
        ob = me;
        opt = "dntg";
    } else if (wizardp(me)) {
        if (sscanf(arg, "-dntg %s", arg))
            opt = "dntg";
        else if (sscanf(arg, "-qujing %s", arg))
            opt = "qujing";
        else
            opt = "qujing";
        ob = find_player(arg);
        if (!ob) ob = find_living(arg);
        if (!ob) ob = LOGIN_D->find_body(arg);
        if (!ob || !me->visible(ob)) return notify_fail("没有这个人。\n");
    } else
        return 0;

    write(OBSTACLES_D->check_obstacles_long(ob, 0, ob != me, opt));

    return 1;
}

int help()
{
    write(@TEXT
指令格式：obstacles [-dntg] <某人>

显示某人的过关记录。
默认显示西行求取真经的记录，加[-dntg]参数则显示大闹天宫的记录。

请见：help qujing
TEXT
    );
    return 1;
}

