// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// create by snowcat.c 4/20/1997
// room: /d/eastway/huaqing.c

inherit ROOM;

void create ()
{
    set ("short", "曲江池");
    set ("long", @LONG

这里已经距离长安很远了，但是游人仍然不少。听人讲，这里有一个
神秘的温泉，泉水清澈，雾气缭绕，为修补成仙的极佳场所。因此有
许多人纷纷远道而来，求得一浴。
LONG);

    set("exits", ([
            "east"          : __DIR__"xianquan",
            "west"          : __DIR__"guandao3",
        ]));
    set("objects", ([
            __DIR__"npc/luren"     : 2,
        ]));
    set("outdoors", __DIR__);
    
    setup();
}






