
inherit ROOM;

void create()
{
    set("short", "演武场");
    set("long", @LONG

傲来国演武场，文官武将，各穿锦衣；帐下偏裨将校，都披银铠。
分两行。左右军士，皆全装惯带，持戈执戟而立。中间一行行兵
士威风凛凛的穿行于其中。
LONG);

    set("exits", ([
        "north"   : __DIR__"drillent",
        "south"   : __DIR__"arsenal",
    ]));

    set("objects", ([
        __DIR__"npc/wushi" : 4,
    ]));

    set("outdoors", __DIR__);

    setup();
}
