// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "天狐宫");
    set("long", @LONG

这里就是妲己的寝宫，房间布置得非常雅致，色调是粉红色的，让人
心中一暖。尤其是这里的香气，浓郁异常，深吸一口气，仿佛就会让
人昏昏欲醉。
LONG);

    set("exits", ([ /* sizeof() == 2 */
        "south" : __DIR__"tianjing",
        "down" : __DIR__"jailroom",
    ]));

    set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/foxqueen.c" : 1,
    ]));

    setup();
}

int valid_leave(object me, string dir)
{
    object daji;
    if (!wizardp(me) && dir == "down"
    &&  objectp(daji = present("daji", this_object()))
    &&  living(daji))
        return notify_fail("妲己冷冷的瞥了你一眼，你急忙止步。\n");
    return ::valid_leave(me, dir);;
}