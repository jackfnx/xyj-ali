//restroom.c

inherit ROOM;

void create ()
{
    set ("short", "雪阶");
    set ("long", @LONG

这是一条满是积雪的阶梯，不过已经到达了尽头，面前只有一道
积雪的石壁(shibi)。
LONG);

    set("exits", ([ //sizeof() == 4
        "south" : __DIR__"xuejie-1",
    ]));

    set("outdoors", "xueshan");

    setup();

}

void init()
{
    add_action("do_climb", "climb");
}

int do_climb(string arg)
{
    object me = this_player();

    if (!arg || arg != "shibi") return notify_fail("你要往哪爬？\n");
    if (me->is_busy()) return notify_fail("你现在正忙着呢。\n");

    message_vision("$N手抠着石缝，向石壁上爬去。\n", me);
    me->start_busy(2);
    call_out("climb_to", 2, me);
    return 1;
}

void climb_to(object me)
{
    if (me->query("kee") < 50) {
        message_vision("谁知，$N一脚蹬空，从石壁上大头冲下载了下来，脑瓜子噗的一声砸在雪地上。\n", me);
        message_vision("幸好是雪地，否则肯定没命了。\n", me);
        me->unconcious();
    } else if ((int)me->query_skill("dodge", 1) < 20) {
        message_vision("谁知，$N一脚蹬空，从石壁上大头冲下载了下来，来了个屁股向后平沙落雁式。\n", me);
        message_vision("虽然是雪地，也把$P摔得不轻。\n", me);
        me->receive_damage("kee", 20);
    } else {
        me->receive_damage("kee", 50);
        tell_room(environment(me), "转眼之间，"+me->name()+"的身影便看不见了。\n", me);
        me->move(__DIR__"no4-enter");
        tell_room(environment(me), "只见"+me->name()+"飞身跃了上来。\n", me);
    }
}
