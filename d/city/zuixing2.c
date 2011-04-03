// ALi by NewX
 
// Room: /d/city/zuixing2

inherit ROOM;
 
void create ()
{
    set ("short", "醉星楼二楼");
    set ("long", @LONG

上得楼梯，迎面是一面玉石屏风，上绘建成元吉的英雄事迹。一副是
建成走马取关，一幅是元吉斧劈隋将，一副是建成单鞭夺槊，一副是
元吉枪扫群雄。可惜这些画怎么看怎么觉得怪异，怎么看怎么觉得滑
稽，甚至你还觉得有点似曾相识，但又一时想不起来。
LONG);
    set("exits", ([ /* sizeof() == 1 */
        "down" : __DIR__"zuixing",
    ]));
    set("objects", ([
        "/d/obj/misc/chairs" : 4,
        "/d/obj/misc/tables" : 1,
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
    object me=this_player(), here=this_object(), ob;
    int kar=me->query_kar();

    if ((!arg || arg != "柱子") && (arg != "zhuzi" && arg!="pillar"))
        return notify_fail("你要从哪里下手？\n");
    if (!(ob = me->query_temp("weapon")) || (string)ob->query("skill_type") != "axe" )
        return notify_fail("没有顺手的家伙怎么拆得动？\n");
    
    //if (objectp(present("li jiancheng", environment(me)))
    //    || objectp(present("li yuanji", environment(me))))
    //    return notify_fail("当朝达贵在此，不怕砸伤了担责任吗？\n");

    here->add("pending/breakdown", 1);
    if (here->query("already_breakdown"))
        return notify_fail("柱子都塌了，还砍什么砍？要命的快下楼去吧！\n");
    message_vision("$N用足了劲，一斧抡向彩楼的柱子！只见几片木片四散飞开。\n", me);
    if (here->query("pending/breakdown") > (int)(40 - kar)/5) {
        message_vision("只听一声巨响，柱子从中折断，" + here->query("short") + "塌了下来！\n", me);
        message_vision("$N虽然搞得灰头土脸，但居然没有受伤！大命不死，还是赶紧下楼去吧！\n", me);
        here->set("long", @LONG

这里曾经是一间华丽无比的房间，但现在只剩一片废墟。几块烂木头
下面到处都是酒杯碗筷的碎片。原来在这里服侍的舞女、小童也早就
不知去向了。
LONG);
        here->set("already_breakdown", 1);
        here->set("outdoors", 1);
        me->add_temp("mark/zuixing2_broken", 1);
    }
    me->receive_damage("kee", (int)me->query("max_kee")/4);
    return 1;
}
