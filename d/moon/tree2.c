
inherit ROOM;

void create()
{
    set("short", "桂树叶间");
    set("long", @LONG
四周花香弥漫，枝叶繁茂，却已看不见地。
LONG);

    set("exits", ([ /* sizeof() == 2 */
        "up" : __DIR__"ontop",
        "down" : __DIR__"tree1",
    ]));

    set("objects", ([
        "/d/obj/flower/guihua.c" : 2,
    ]));

    setup();
}






