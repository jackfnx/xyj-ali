inherit ROOM;

void create()
{
    set("short", "瀑布前");
    set("long", @LONG

只见那股涧水奔流，真个似滚瓜涌溅。顺涧爬山，直至源流之处，
乃是一股瀑布飞泉。但见那：

　　一派白虹起，千寻雪浪飞；海风吹不断，江月照还依。
　　冷气分青嶂，馀流润翠微；潺湲名瀑布，真似挂帘帷。
LONG);

    set("exits", ([
        "west"   : __DIR__"shanya",
    ]));
    set("outdoors", __DIR__);

    setup();
}

void init()
{
    add_action("do_jump", "jump");

    call_out("appearing", 1);
}

void appearing()
{
    object where = this_object();
    object houzi;

    if (!present("hou zi 4", where)) {
        houzi = new(__DIR__"npc/hou");
        houzi->move(where);
        message_vision("树丛中蹿出一只$N。\n", houzi);
    }
}

int do_jump(string arg)
{
    object me;

    me = this_player();
    if (!arg || (arg != "fall" && arg != "pubu"))
        return notify_fail("你往哪儿跳？\n");

    if (random(30) + me->query("kar") < 30) {
        message_vision("$N向下一纵，不小心撞在了一块石头上。\n", me);
        me->unconcious();
    } else {
        message_vision("$N大喝一声：“我去瞧瞧！＂说罢飞身跃入瀑布。\n", me);
        me->move(__DIR__"ironbridge");
    }

    return 1;
}
