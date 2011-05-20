
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "石房");
    set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床(bed)、
石凳，各种家当样样俱全。好一座天造地设的安身之所。正中间插着
一杆大旗(flag)。
LONG
    );

    set("item_desc", ([
        "flag": "一面迎风招展的三色大旗，在空旷之处迎风挥舞(wave)起来一定煞是好看，但似乎很难拔(ba)动。\n",
        "bed": "一张石床(gosleep,gobed,bed)。\n", 
    ]));

    set("exits", ([
        "west"   : __DIR__"ironbridge",
        "east"  : __DIR__"throne",
    ]));
    set("no_clean_up", 1);
    set("have_flag", 1);

    create_door("west", "石门", "east", DOOR_CLOSED);
    setup();
}

void init()
{
    add_action("do_bed", ({"bed","gobed","gosleep"}));
    add_action("do_ba", "ba");
}

int do_bed()
{
    object me = this_player();
    message_vision("$N往石床上一躺，准备睡觉了。\n\n", me);
    me->move(__DIR__"shichuang");
    message_vision("\n$N钻到了被窝里。\n", me);
    return 1;
}

int do_ba(string arg)
{
    if (query("have_flag")) {
        if (!arg || arg != "flag")
            return notify_fail("你要拔什么？\n");

        return notify_fail("你使尽吃奶的力气也没将大旗拔出来。\n", me);
    }
    return 0;
}

void reset_flag_desc(int have_flag)
{
    if (!have_flag) {
        set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床(bed)、
石凳，各种家当样样俱全。好一座天造地设的安身之所。
LONG);
        delete("item_desc/flag");
        set("have_flag", 0);
    } else {
        set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床(bed)、
石凳，各种家当样样俱全。好一座天造地设的安身之所。正中间插着
一杆大旗(flag)。
LONG);
        set("item_desc/flag",
            "一面迎风招展的三色大旗，在空旷之处迎风挥舞(wave)起来一定煞是好看，但似乎很难拔(ba)动。\n");
        set("have_flag", 1);
    }
}

void start_call_out(string func, int time, string arg)
{
    call_out(func, time, arg);
}
