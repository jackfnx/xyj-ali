inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me, string arg)
{
    object ob;

    if (!arg) {
        ob = me;
    } else if (wizardp(me)) {
        ob = find_player(arg);
        if (!ob) ob = find_living(arg);
        if (!ob) ob = LOGIN_D->find_body(arg);
        if (!ob || !me->visible(ob)) return notify_fail("没有这个人。\n");
    } else
       return 0;

    write(QUEST_D->check_quests_detail(ob, me));

    return 1;
}

int help()
{
    write(@TEXT
指令格式：quests <某人>

显示某人的解谜记录。 

请见：help jiemi
TEXT
    );
    return 1;
}


