// ALi by NewX

inherit ROOM;

void create ()
{
    set ("short", "Ììºü¹¬");
    set ("long", @LONG

æ§¼ºµÄÇÞ¹¬¡£
LONG);

    set("exits", ([ /* sizeof() == 1 */
        "south" : __DIR__"tianjing.c",
    ]));

    set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/foxqueen.c" : 1,
    ]));

    setup();
}

