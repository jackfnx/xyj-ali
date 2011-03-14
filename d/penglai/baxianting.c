// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ROOM;
#include <room.h>

void create ()
{
    set ("short", "八仙亭");
    set ("long", @LONG

八仙离开五庄观后，就到处云游。因为他们与三星相交多年，因此在
蓬莱盘桓的时间最多。为此，这里就修建了一座八仙亭，专供他们落
脚。
LONG);
    set("exits", ([ /* sizeof() == 3 */
        "west" : __DIR__"road1",
    ]));
    set("objects", ([ /* sizeof() == 2 */
        __DIR__"npc/hanzhongli" : 1,
        __DIR__"npc/tieguaili" : 1,
        __DIR__"npc/hanxiangzi" : 1,
        __DIR__"npc/hexiangu" : 1,
        __DIR__"npc/lancaihe" : 1,
        __DIR__"npc/caoguojiu" : 1,
    ]));
    set("outdoors", 1);
    setup();
}
