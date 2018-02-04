// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "石洞");
    set("long", @LONG

一条长长的石洞，看不到尽头。东面有一个小室，隐约传来一些奇怪的
声音。
LONG);

    set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"shidong3",
        "south" : __DIR__"shidong1",
        "east" : __DIR__"practiceroom",
    ]));

  setup();
}

