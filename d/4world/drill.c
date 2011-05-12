
inherit ROOM;

void create()
{
    set("short", "演武场");
    set("long", @LONG

这里是傲来国演武场，好大一片空地，一个人也没有。你不禁产生
一种遛遛马的冲动，不过想到这里毕竟是人家国家的演武场，所以
你还是忍住了。
LONG);

    set("exits", ([
        "north"   : __DIR__"drillent",
        "south"   : __DIR__"arsenal",
    ]));

    set("outdoors", __DIR__);

    setup();
    replace_program(ROOM);
}
