
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "石房");
    set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床、
石凳，各种家当。好一座天造地设的安身之所。正中间插着
一杆大旗(flag)，后面还有一张石床(bed)。
LONG
    );

    set("item_desc", ([
        "flag":"一面迎风招展的三色大旗，在空旷之处迎风挥舞(wave)起来一定煞是好看，但似乎很难拔(ba)动。\n",
        "bed": "一张石床(gosleep,gobed,bed)。 \n", 
    ]));

    set("exits", ([
        "west"   : __DIR__"ironbridge",
        "east"  : __DIR__"dongnei",
    ]));

    create_door("west", "石门", "east", DOOR_CLOSED);
    setup();
}

void init()
{
    object me = this_player();
    object houzi;
    object where = this_object();

    if (me->query("dntg/huaguo")=="allow") {
        message_vision("一群猴子跟着$N蹦蹦跳跳的跑了过来。\n", me);
        if (!present("hou zi 3", where)) {
            houzi = new(__DIR__"npc/hou-ok");
            houzi->move(where);
        }
    }
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
