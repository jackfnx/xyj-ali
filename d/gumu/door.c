// ALi by NewX
 
inherit ROOM;

void create ()
{
    set ("short", "古墓入口");
    set ("long", @LONG

始皇陵的地下居然真的别有洞天，洞口有块石头，上面写着『轩辕古墓』
四个字。奇怪？不是始皇陵吗？怎么又变成轩辕古墓了？你也有点搞不懂
是怎么回事了。

LONG);

    set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"shidong1.c",
        "up": "/d/eastway/bingma.c",
    ]));

    setup();
}

