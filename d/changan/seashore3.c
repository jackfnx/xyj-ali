// ALi by NewX

#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "东海之滨");
    set("long", @LONG

面前便是东海，茫茫大海望不到边际。海面上波涛汹涌，几丈
高的浪头此起彼伏，象是要吞灭一切敢于到海上的东西。你只
能沿着海边行走，希望能找出一条大路来。
LONG);

    set("outdoors", 1);
    set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"seashore2",
        "south" : __DIR__"eastseashore",
    ]));

    setup();
}
