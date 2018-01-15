
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "石房");
    set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床(bed)、
石凳，各种家当样样俱全。好一座天造地设的安身之所。
LONG
    );

    set("item_desc", ([
        "bed": "一张石床(gosleep,gobed,bed)。\n", 
    ]));

    set("exits", ([
        "west"   : __DIR__"ironbridge",
        "east"  : __DIR__"throne",
    ]));
    set("no_clean_up", 1);

    create_door("west", "石门", "east", DOOR_CLOSED);
    setup();
}

void init()
{
    add_action("do_bed", ({"bed","gobed","gosleep"}));
}

int do_bed()
{
    object me = this_player();
    message_vision("$N往石床上一躺，准备睡觉了。\n\n", me);
    me->move(__DIR__"shichuang");
    message_vision("\n$N钻到了被窝里。\n", me);
    return 1;
}
