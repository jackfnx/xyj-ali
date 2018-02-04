// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "石洞");
    set("long", @LONG

一条长长的石洞，看不到尽头。东面黑洞洞的，隐约传来一些奇怪的
声音。西面影绰绰的，隐约飘来一阵阵香气。
LONG);

    set("exits", ([ /* sizeof() == 3 */
        "north" : __DIR__"shidong4",
        "south" : __DIR__"shidong2",
        "east" : __DIR__"tiaojiaoroom",
        "west" : __DIR__"enjoyroom",
    ]));

  setup();
}

