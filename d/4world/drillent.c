
inherit ROOM;

void create()
{
    set("short", "演武场入口");
#if 1
    set("long", @LONG

在傲来国演武场的入口，一个人影也没有，所有人都能随便出入。
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
