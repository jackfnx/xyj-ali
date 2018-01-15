// room

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "宝光殿");
    set("long", @LONG
    
LONG);

    set("exits", ([ /* sizeof() == 3 */
        "east"      : __DIR__"tongmingdian",
        "west"      : __DIR__"yunluw1",
    ]));
    setup();
}
