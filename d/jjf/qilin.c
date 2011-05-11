// Room: /d/jjf/qilin.c

inherit ROOM;

void create()
{
    set("short", "麒麟阁");
    set("long", @LONG

这里竟是高祖特旨为功臣们修建的彩楼，著名的「麒麟阁」。没想到
这彩楼竟也被神仙挪移到了这里，不知道长安城中那座麒麟阁又是怎
么回事。不过这里可比长安的麒麟阁热闹多了，想来这一帮功臣已经
习惯了在旁边的营房操练完毕后来这里推杯换盏。
LONG
    );
    set("no_fight", 1);
    set("item_desc", ([ /* sizeof() == 1 */
        "up" : "楼上人声喧哗，想是传杯送盏，酒兴正至半酣。",
]));
    set("no_clean_up", 0);
    set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/qinbing" : 2,
]));
    set("light_up", 1);
    set("exits", ([ /* sizeof() == 2 */
        "up" : __DIR__"qilin2",
        "southeast" : __DIR__"center",
]));

    setup();
    replace_program(ROOM);
}
