inherit ROOM;

void create()
{
    set("short", "山路");
    set("long", @LONG

一条不甚宽广的山路，四处芳草鲜美，落英缤纷。周围的树丛
中偶尔撺出几只猴子，在这里跳来跳去，路边的小草(grass)
随风飘舞。
LONG
    );

    set("item_desc",([
        "grass":"一些绿油油的小草，拔(ba)出来看看？\n"
    ]));

    set("exits", ([
        "northup"   : __DIR__"shanlu2",
        "eastdown"   : __DIR__"entrance",
    ]));
    set("outdoors", __DIR__);
    set("grass_number", 5);
    setup();
}

void init()
{
    add_action("do_ba", "ba");
}

void reset()
{
    ::reset();
    set("grass_number", 5);
}

int do_ba(string arg)
{
    object me = this_player();
    object cao;

    if (!arg || arg != "grass")
        return notify_fail("你要拔什么？\n");
    else if (query("grass_number") == 0)
        return notify_fail("草已经被拔光了，别费劲了。\n");
    else if (me->query("kee") < 10)
        me->unconcious();
    else {
        me->receive_damage("kee", 10);
        cao = new (__DIR__"obj/grass");
        cao->move(me);
        message_vision("$N拔了一颗小草。\n", me);
        add("grass_number", -1);
    }
    return 1;
}

