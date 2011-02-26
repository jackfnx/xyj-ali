// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// create by snowcat.c 4/20/1997
// room: /d/eastway/guandao3.c

inherit ROOM;

void create ()
{
    set ("short", "官道");
    set ("long", @LONG

这是一条长长的官道，官道上马车并行，人来人往。官道的西边通向
进士场，远远看去似乎有一座高塔，东边则是雾濛濛的，看不清楚。
LONG);

    set("exits", ([
            "southwest"  : __DIR__"guandao2",
            "east"       : __DIR__"huaqing",
            "west"       : __DIR__"jinshi",
        ]));
    set("outdoors", __DIR__);
    
    setup();
}






