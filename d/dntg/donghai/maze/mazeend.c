
inherit ROOM;

void create()
{
    set("short", "海藏");
    set("long", @LONG
    
空荡荡的海藏中直立着一根铁柱子，金光闪闪
照得人睁不开眼。
LONG );

    set("exits", ([
        "up"    : "/d/changan/eastseashore",
    ]));

    setup();
}

void init()
{
    object helper = this_player()->query_temp("dntg_helper");
    if (helper) helper->make_shentie();
}
