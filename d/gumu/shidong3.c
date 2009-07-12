// ALi by NewX

inherit ROOM;

void create ()
{
    set ("short", "石洞");
    set ("long", @LONG

一条长长的石洞，看不到尽头。东面有一个小室，隐约传来一些奇怪的
声音。
LONG);

    set("exits", ([ /* sizeof() == 3 */
        "north" : __DIR__"shidong4.c",
        "south" : __DIR__"shidong2.c",
        "east" : __DIR__"testroom1.c",
    ]));

  setup();
}

