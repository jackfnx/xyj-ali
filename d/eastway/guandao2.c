// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// create by snowcat.c 4/20/1997
// room: /d/eastway/guandao2.c

inherit ROOM;

void create ()
{
    set ("short", "官道");
    set ("long", @LONG

这是一条长长的官道，官道上马车并行，人来人往。官道一边通向西
南，一边通向东北，而东南是一座陵墓。
LONG);

    set("exits", ([
            "southwest" : __DIR__"guandao1",
            "northeast" : __DIR__"guandao3",
            "southeast" : __DIR__"shihuang",
        ]));
    set("outdoors", __DIR__);
    
    setup();
}






