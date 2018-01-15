// ALi by NewX

// Room: /d/city/zuixing.c
 
inherit ROOM;
 
void create ()
{
    set ("short", "醉星楼");
    set ("long", @LONG

太子李建成和齐王李元吉对高祖御旨起麒麟阁十分不满，认为这是对
秦王的偏爱。于是二人穷二府之资，在与麒麟阁正相对的位置修造了
一座极其华丽宏伟的彩楼，名「醉星楼」。为了吸引百姓前来观看，
二人甚至不惜发送食物钱财，当时却也是盛况空前。可是，两人亡故
之后，这里便荒废了，只剩下这空空的彩楼，诉说着当年两位主人的
荒唐。
LONG);

    set("no_fight", 1);
    set("light_up", 1);
    set("exits", ([ /* sizeof() == 2 */
        "west" : __DIR__"xuanwu-n1",
        "up" : __DIR__"zuixing2",
    ]));
    set("objects", ([
        "/d/obj/misc/chairs" : 4,
        "/d/obj/misc/tables" : 1,
    ]));

    setup();
}

void init()
{
    add_action("do_kan", "kan3");
    add_action("do_kan", "砍");
    add_action("do_kan", "chop");
}

int do_kan(string arg)
{
    object me=this_player(), here=this_object(), ob, zhuzi;
    int kar=me->query_kar();
    
    if ((!arg || arg != "柱子") && (arg != "zhuzi" && arg!="pillar"))
        return notify_fail("你要从哪里下手？\n");
    if (!(ob = me->query_temp("weapon")) || (string)ob->query("skill_type") != "axe")
        return notify_fail("没顺手的家伙怎么拆得动？\n");
    //if (objectp(present("qin bing", environment(me))))
    //    return notify_fail("看样子要想拆楼，先得把亲兵料理了！\n");
    if (!me->query_temp("mark/zuixing2_broken"))
        return notify_fail("还没砸二楼呢，就来打一楼的主意？\n");
    here->add("pending/breakdown", 1);
    if (here->query("broken"))
        return notify_fail("柱子都塌了，还砍什么砍？要命的快出去吧！\n");
    message_vision("$N用足了劲，一斧抡向彩楼的柱子！只见几片木片四散飞开。\n", me);
    if (here->query("pending/breakdown") >= (int)(40 - kar)/5) {
        message_vision("只听一声巨响，支撑房子的柱子从中折断，整座醉星楼塌了下来！\n", me);
        message_vision("$N虽然搞得灰头土脸，但居然没有受伤！命大不死，还是赶紧出去吧！\n", me);
        here->set("long", @LONG

这里曾经是一座豪华气派的彩楼，但不知为何被人拆掉了，只剩一片
废墟。几块烂木头下面到处都是酒杯碗筷的碎片。半截被砍断的柱子
倒在门边。
LONG);
        me->delete_temp("mark/zuixing2_broken");
        here->set("broken", 1);
        here->set("outdoors", 1);
        zhuzi=new(__DIR__"obj/zhuzi");
        zhuzi->move(here);
        here->set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"qinglong-e4",
        ]));
    }
    me->receive_damage("kee", (int)me->query("max_kee")/4);
    return 1;
}
