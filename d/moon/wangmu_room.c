// ALi by NewX

#include <ansi.h>
inherit ROOM;

void create()
{
    set ("short", "卧云轩");
    set ("long", @LONG

此间本是王母居处，收拾的与别处不同，竟分不出间隔来的。四面皆是雕
空玲珑木板，或「流云百蝠」，或「岁寒三友」，或山水人物，或翎毛花
卉，或集锦，或博古，或万万福寿，各种花样，皆名手雕镂，五彩销金嵌
宝的。一隔一隔，或有贮书处，或设鼎处，或安置笔砚处，或供花设瓶安
放盆景处，其格各式各样，或天圆地方，或葵花蕉叶，或连环半壁，真是
花团锦簇，剔透玲珑。
LONG);

    set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/xiwangmudummy.c" : 1,
        ]));

    set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"huilang1.c",
                ]));

    setup();
}

void init()
{
    add_action("do_search", "search");
}

int do_search(string arg)
{
    object me = this_player();

    if (!arg || arg != "yunwu")
        return notify_fail("你想找什么？");

    message_vision("$N趴在地上乱摸了一通，忽然在地上发现了一颗铜钱。\n", me);
    message_vision("财迷的$N欢天喜地的想把铜钱捡起来，谁知铜钱刚刚离地，地面上便显出了一个洞口，将$N的身影吞没了。\n\n\n", me);
    tell_object(me, HIY "你掉进了一条长长地隧道，你不停的下坠，吓得半死，可是偏偏停不下来。。。\n\n\n" NOR);
    me->move("/d/gumu/tianjing");
    tell_object(me, CYN "\n\n你吧唧一声摔在地上，终于停了下来，却也摔了个半死。。。\n\n" NOR);

    return 1;
}
