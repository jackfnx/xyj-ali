// Room: /d/jjf/zuixing2
inherit ROOM;
 
void create()
{
    set("short", "醉星楼二楼");
    set("long", @LONG

上得楼梯，迎面是一面玉石屏风，上绘嫦娥奔月的故事。转过屏风，
只见两人坐在一张桌上狂饮作乐，旁边舞女在奏乐起舞。一边，几个
青衣小童正在伺候着。有的在上菜，有的在打扇。
LONG);
    set("objects", ([ /* sizeof() == 4 */
        __DIR__"npc/liyuanji.c": 1,
        __DIR__"npc/lijiancheng.c": 1,
]));
    set("exits", ([ /* sizeof() == 1 */
    "down" : __DIR__"zuixing",
]));
    set("light_up", 1);

    setup();
}

void init()
{
    add_action("do_kan", "砍");
    add_action("do_kan", "chop");
    add_action("do_kan", "kan3"); 
}

int do_kan(string arg)
{
    object me = this_player(), ob;
    
    if (!arg || (arg != "柱子" && arg != "zhuzi" && arg!="pillar"))
        return notify_fail("你要从哪里下手？\n");
    if (!(ob = me->query_temp("weapon")) || (string)ob->query("skill_type") != "axe")
        return notify_fail("没有顺手的家伙怎么拆得动？\n");
    if (objectp(present("li jiancheng", environment(me)))
    ||  objectp(present("li yuanji", environment(me))))
        return notify_fail("当朝达贵在此，不怕砸伤了担责任吗？\n");

    message_vision("$N用足了劲，一斧抡向彩楼的柱子！\n", me);
    message_vision("只听轰隆一声巨响，支撑房子的柱子从中折断，整座醉星楼塌了下来！\n", me);
    message_vision("一根巨大的房梁从天而降，正正砸在$N的天灵盖上，将$N砸得两眼翻白，当场晕了过去！\n", me);
    me->unconcious();
    message_vision("只听咔啦咔啦一阵响动，碎裂的木头又向上飞去，重新组装成了一座彩楼，仿佛刚才的场景只是幻影。\n", me);
    return 1;
}
