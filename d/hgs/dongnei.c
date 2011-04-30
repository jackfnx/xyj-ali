inherit ROOM;

void create()
{
    set("short", "水帘洞内");
    set("long", @LONG
这里便是花果山水帘洞的内堂，四周锅碗瓢盆样样
俱全。正中一张虎皮椅子，正是供水帘洞主休息的。
LONG );

    set("exits", ([
        "west"   : __DIR__"shifang",
    ]));

    set("objects", ([
        "/d/dntg/huaguo/mowang" : 1,
    ]));

    setup();
}

int valid_leave(object me, string dir)
{
    object mowang;
    if (dir == "west"
    &&  objectp(mowang = present("hunshi mowang", environment(me)))
    &&  living(mowang))
        return notify_fail("混世魔王冲着你冷笑到：“想走？没那么容易吧！”\n");
    return ::valid_leave(me,dir);
}

