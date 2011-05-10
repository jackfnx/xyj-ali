
inherit ROOM;

void create()
{
    set("short", "演武场");
#if 1
    set("long", @LONG

这里是傲来国演武场，好大一片空地，一个人也没有。你不禁产生
一种遛遛马的冲动，不过想到这里毕竟是人家国家的演武场，所以
你还是忍住了。
LONG);
#else
    set("long", @LONG

傲来国演武场，文官武将，各穿锦衣；帐下偏裨将校，都披银铠。
分两行。左右军士，皆全装惯带，持戈执戟而立。中间一行行兵
士威风凛凛的穿行于其中。
LONG);
#endif

    set("exits", ([
        "north"   : __DIR__"drillent",
        "south"   : __DIR__"arsenal",
    ]));

    set("outdoors", __DIR__);

    setup();
}
