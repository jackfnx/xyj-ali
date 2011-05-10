
inherit ROOM;

void create()
{
    set("short", "演武场入口");
#if 1
    set("long", @LONG

这里是傲来国演武场的入口。按理来说这里是军事重地，闲杂人等
是不能出入的，可是因为傲来国承平日久，武备松弛，所以这里的
演武场已经很多年没有使用过了，因此这里现在根本没有守卫。
LONG
    );
#else
    set("long", @LONG

在傲来国演武场的入口，站立着几个威武的禁军教头，
守卫着这里。里面不时传来雄壮的号角声。
LONG
    );
#endif

    set("exits", ([ /* sizeof() == 2 */
        "south" : __DIR__"drill",
        "west"  : __DIR__"northgate",
    ]));
    set("outdoors", __DIR__);


    setup();
}
