// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//changan city

inherit ROOM;

void create ()
{
        set ("short", "歪柳巷");
        set ("long", @LONG

巷子两边是成行的柳树，而柳树皆成扭曲状，故名歪柳巷。巷中有青
石铺成的大路供人行走，两旁是青砖瓦房，来往人物恭而有礼，与城
内的繁华热闹相比却多出几分闲情安逸。北边是一座鼓楼。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "north" : __DIR__"gulou",
                "east" : __DIR__"wailiu3",
                "southwest" : __DIR__"wailiu5",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));


        set("outdoors", "changan");
    set("no_clean_up", 0);
        setup();
    replace_program(ROOM);
}



