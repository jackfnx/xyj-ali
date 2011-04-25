// ALi by NewX
 
inherit ROOM;

void create ()
{
    set("short", "古墓入口");
    set("long", @LONG

坟堆下面居然真的别有洞天，洞口一块石头，上面写着『轩辕古墓』
四个字。难道这是轩辕黄帝之墓？不会吧，黄帝陵不应该在这里啊？
LONG);

    set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"shidong1",
        "up": "/d/changan/fendui",
    ]));

    setup();
}

