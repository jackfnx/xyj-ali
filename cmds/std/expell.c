
// expell.c

#include <skill.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    object ob;
    string *skname;
    mapping skills;
    int i;

    if (!arg || !ob = present(arg, environment(me)))
        return notify_fail("你要将谁逐出师门？\n");
    if (!ob->is_character())
        return notify_fail("你要开革「谁」？\n");
    if (!userp(ob))
        return notify_fail("你只能开革玩家所扮演的人物。\n");

    if (!me->expell_apprentice(ob)) return 0;

    ob->save();
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : expell <某人>

这个指令可以让你开除不成才的弟子，被开除的弟子虽离开你的门下，但仍
属于这个门派，可以随便传投本派其他师父。

HELP
    );
    return 1;
}
