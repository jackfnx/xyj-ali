// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ROOM;

void create ()
{
    set ("short", "西营寨");
    set ("long", @LONG

这里是兵营，到处都是官兵走来走去，有的在武将的指挥下列队操
练，有的独自在练功，有的坐着、躺着正在休息。不过没有看到主
帅。
LONG);
    
    set("exits", ([ /* sizeof() == 1 */
        "south" : "/d/city/baihu-w4",
    ]));
    set("objects", ([ /* sizeof() == 2 */
        "/d/jjf/npc/fujiang" : 2,
    ]));
    
    setup();
}

