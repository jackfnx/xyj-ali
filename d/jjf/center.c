// center.c

inherit ROOM;

void create()
{
    set("short", "飘渺仙境");
    set("long", @LONG

这是一处虚无缥缈的地方，四周云雾缭绕。你也不知道自己身在何处，
也不知道怎样回去(back)。你决定到处看看。
LONG);

    set("exits", ([ /* sizeof() == 4 */
        "southeast" : __DIR__"zuixing",
        "northwest" : __DIR__"qilin",
        "northeast" : __DIR__"yingfang",
        "southwest" : __DIR__"gate",
    ]));

  setup();
}

void init()
{
    add_action("do_back", "back");
}

int do_back(string arg)
{
    return 0;
}
