// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//fabao-road1.c
inherit ROOM;

void create ()
{
    set ("short", "碎石路");
    set ("long", @LONG

一道蜿蜒的小路向东延伸而去。地上铺满了各种奇形怪状的残岩
碎石，其中有一些竟是色彩斑斓，不知是从何而来。
LONG);

    set("exits", 
    ([ //sizeof() == 2
        "west" : __DIR__"kunlun",
        "east" : __DIR__"fabao-road2",
    ]));

    set("outdoors", "1");

    setup();
}

