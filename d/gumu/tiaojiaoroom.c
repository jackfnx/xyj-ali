// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "调教囚牢");
    set("long", @LONG

这里光线黯淡，空气中飘着一股难闻的气味。
这里是囚禁古墓派敌人的地方，也是古墓弟子可以来随意发泄欲望的
地方。当然，这里只有女俘虏，弟子们只能用双头龙享用。

LONG);

    set("objects", ([ /* sizeof() == 3 */
        __DIR__"npc/prisoner" : 3,
        __DIR__"npc/execgirl" : 1,
    ]));

    set("exits", ([ /* sizeof() == 1 */
        "west" : __DIR__"shidong3",
    ]));

    setup();
}

