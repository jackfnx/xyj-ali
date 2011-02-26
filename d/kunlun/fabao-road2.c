// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//fabao-road2.c
inherit ROOM;

void create ()
{
    set ("short", "碎石路");
    set ("long", @LONG

一道蜿蜒的小路向东延伸而去。地上铺满了各种奇形怪状的残岩
碎石，其中有一些竟是色彩斑斓，不知是从何而来。前面有一片
开阔地，隐隐约约中似有绚光闪烁。你心中一阵狂跳，不由得加
快了脚步。
LONG);

    set("exits", 
    ([ //sizeof() == 2
        "west" : __DIR__"fabao-road1",
        "east" : __DIR__"fabao-room",
    ]));

    set("outdoors", "1");

    setup();
}

