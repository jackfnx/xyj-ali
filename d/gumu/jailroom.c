// ALi by NewX

inherit ROOM;

void create ()
{
    set ("short", "淫狱");
    set ("long", @LONG

漆黑的地牢，空气中弥漫着浓浓的女性阴精气味，还有淡淡的血腥味。
周围挂满了各种恐怖的SM道具：木马、皮鞭、镣铐。。。每一件上都有少量
的血迹。
LONG);

    set("exits", ([ /* sizeof() == 1 */
        "up" : __DIR__"dajiroom.c",
    ]));

    set("objects", ([ /* sizeof() == 1 */
        "/d/moon/npc/xiwangmu" : 1,
    ]));

    setup();
}

