inherit ROOM;

void create()
{
    set("short", "洞主宝座");
    set("long", @LONG

这里便是花果山水帘洞的内洞，这里的空间十分宽敞，空气也格外的
清新，仿佛飘荡着一股仙灵之气。正中一张虎皮椅子，正是供水帘洞
之主休息的。
LONG );

    set("exits", ([
        "west"   : __DIR__"shifang",
    ]));

    setup();
}
