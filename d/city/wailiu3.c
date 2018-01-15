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
内的繁华热闹相比却多出几分闲情安逸。东南边有一个仓库。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "north" : __DIR__"wailiu2",
                "west" : __DIR__"wailiu4",
                "southeast" : __DIR__"huohang",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                "/d/obj/book/misc" : 1,
        ]));


        set("outdoors", "changan");
    set("no_clean_up", 0);
        setup();
    replace_program(ROOM);
}



