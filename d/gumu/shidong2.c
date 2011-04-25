// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "石洞");
    set("long", @LONG

一条长长的石洞，看不到尽头。
LONG);

    set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"shidong3",
        "south" : __DIR__"shidong1",
    ]));

  setup();
}

