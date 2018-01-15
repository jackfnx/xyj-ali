// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "枯井");
    set("long", @LONG

这里似乎是一个枯井。抬头望去，可以看到一小片天空。
LONG);

    set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"dajiroom",
        "south" : __DIR__"shidong4",
    ]));

    set("outdoors", __DIR__);
    set("valid_startroom", 1);
    setup();
}

