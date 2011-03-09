// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//changan city

inherit ROOM;

void create ()
{
        set ("short", "青龙大街");
        set ("long", @LONG

你走在一条宽阔的石板大街上，东边就快要出了城门，远远看到一些
兵卒来回巡逻。西边直通到城中心。北边是一座极其华丽、极其宏伟
的彩楼，坐落在城边，显得极为突兀。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "south" : __DIR__"wailiu1",
                "north" : __DIR__"zuixing",
                "west" : __DIR__"qinglong-e3",
                "east" : __DIR__"dongmen",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/youxia" : 1,
        ]));


        set("outdoors", "changan");
    set("no_clean_up", 0);
        setup();
    replace_program(ROOM);
}

