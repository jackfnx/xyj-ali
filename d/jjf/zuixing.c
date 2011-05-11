// created 6-8-97 pickle
// Room: /d/jjf/zuixing.c

inherit ROOM;

void create()
{
    set("short", "醉星楼");
    set("long", @LONG

这里竟是太子建成和齐王元吉造的那一座奢华的彩楼「醉星楼」，没
想到神仙竟然也把他们挪移到了这里。不知道长安城中那座醉星楼又
是怎么回事。反正，这里比长安那座楼还要冷清，这里也没有百姓，
就连发送时食物钱财的狠招数也没有用了。
LONG);

    set("no_fight", 1);
    set("light_up", 1);
    set("objects", ([ /* sizeof() == 2 */
        __DIR__"npc/qinbing-jian" : 1,
        __DIR__"npc/qinbing-qi" : 1,
]));
    set("exits", ([ /* sizeof() == 2 */
        "northwest" : __DIR__"center",
        "up" : __DIR__"zuixing2",
]));

    setup();
}

int valid_leave(object me, string dir)
{
    if (me->query("env/invisibility")) return ::valid_leave(me, dir);
    if (dir == "up" && objectp(present("qin bing", environment(me)))) {
        if (!me->id("qin bing"))
            return notify_fail("亲兵喝道：闲杂人等不得乱闯！\n");
    }
    return ::valid_leave(me, dir);
}

void init()
{
    add_action("do_kan", "kan3");
    add_action("do_kan", "砍");
    add_action("do_kan", "chop");
}

int do_kan(string arg)
{
    object me = this_player(), ob;
    
    if (!arg || (arg != "柱子" && arg != "zhuzi" && arg!="pillar"))
        return notify_fail("你要从哪里下手？\n");
    if (!(ob = me->query_temp("weapon")) || (string)ob->query("skill_type") != "axe")
        return notify_fail("没顺手的家伙怎么拆得动？\n");
    if (objectp(present("qin bing", environment(me))))
        return notify_fail("看样子要想拆楼，先得把亲兵料理了！\n");
    message_vision("$N用足了劲，一斧抡向彩楼的柱子！\n", me);
    message_vision("只听轰隆一声巨响，支撑房子的柱子从中折断，整座醉星楼塌了下来！\n", me);
    message_vision("一根巨大的房梁从天而降，正正砸在$N的天灵盖上，将$N砸得两眼翻白，当场晕了过去！\n", me);
    me->unconcious();
    message_vision("只听咔啦咔啦一阵响动，碎裂的木头又向上飞去，重新组装成了一座彩楼，仿佛刚才的场景只是幻影。\n", me);
    return 1;
}
