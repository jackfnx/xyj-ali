//sgzl
inherit ROOM;

void create()
{
    set("short", "雪岭");
    set("long", @LONG

天空中飘舞的雪花遮住了你的视线，只能隐隐看见前面挂着一张
小小的蜘蛛网(net)。
LONG);

    set("item_desc", ([
        "net" : "一张蜘蛛网。\n", 
    ]));

    set("exits", ([ //sizeof() == 2
        "south" : __DIR__"no4-w1",
        "west" : __DIR__"no4-wn2",
    ]));

    set("outdoors", "xueshan");

    setup();
}

void init()
{
    remove_call_out("check_hudie");
    call_out("check_hudie", 5);
}

void check_hudie()
{
    object where = this_object();
    object hudie;

    if (hudie = present("hu die", where)) {
        remove_call_out("catch_hudie");
        call_out("catch_hudie",3);
    }
    remove_call_out("check_hudie");
    call_out("check_hudie", 5);
}

void catch_hudie()
{
    object where = this_object();
    object hudie;

    if (hudie = present("hu die", where)) {
        message_vision("$N被一股巨大的力量卷进了蜘蛛网。\n", hudie);
        hudie->move(__DIR__"zhuwang");
        message_vision("$N被卷了进来。\n", hudie);
    }
}
