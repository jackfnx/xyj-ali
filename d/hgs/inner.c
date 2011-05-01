// Room: /d/hgs/inner.c
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "黑暗中");
    set("long", @LONG

这里是山腹中的一处密洞，洞内一片黑暗，石缝(gap)内依稀可以看见
什么东西黑乎乎的。
LONG
    );
    set("item_desc", ([
        "gap" : "石缝似乎可以扩大(expand)，那样或许能取出那件东西。\n",
    ]));
    set("exits", ([]));

    setup();
}

void init()
{
    add_action("do_expand", "expand");
}

int do_expand(string arg)
{
    object me = this_player();
    object ob; 

    if (!arg || (arg != "gap" && arg != "石缝"))
        return notify_fail("你要扒开什么？\n");
    if (!(ob = me->query_temp("weapon")))
        return notify_fail("没有工具怎么干活？\n");
    if (me->query_str() < 50)
        return notify_fail("你的力量不够大！\n");

    if (me->query("kee") < 200) {
        message_vision(HIR "\n只听得轰的一声，一大块石壁塌了下来，将$N砸晕了过去。\n\n" NOR, me);
        me->unconcious();
    } else {
        me->receive_damage("kee", 200);
        message("vission", HIR "\n只听得轰的一声，一大块石壁塌了下来。\n\n" NOR, environment(me));
    }

    if ("/d/dntg/master"->in_mud()) {
        message("vission", HIR "你看见石块之中空空如也。\n" NOR, me);
        return 1;
    }

    ob = new("/d/dntg/master");
    ob->move(environment(me));
    message("vission", HIR "你看见石块之中露出一把金箍棒。\n" NOR, me);
    return 1;
}
