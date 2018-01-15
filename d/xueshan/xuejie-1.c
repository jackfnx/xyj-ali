// ALi by NewX

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "雪阶下");
    set("long", @LONG

这里是一片小平台，雪山弟子平日起居的处所基本都在这里，西边
就是休息室，东边则是厨房。地上积了厚厚的雪，往来的雪山弟子
却从不感到严寒。
LONG);

    set("exits", ([ //sizeof() == 4
        "north" : __DIR__"xuejie-2",
        "sorth" : __DIR__"xuelu",
        "west" : __DIR__"restroom",
        "east" : __DIR__"chufang",
    ]));
    
    set("objects", ([
        __DIR__"obj/rack" : 1,
    ]));

    set("outdoors", "xueshan");

    create_door("east", "厨房门", "west", DOOR_CLOSED);
    set("no_clean_up", 0);

    setup();
}



