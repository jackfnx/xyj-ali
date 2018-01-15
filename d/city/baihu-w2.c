// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//changan city

inherit ROOM;

void create ()
{
        set ("short", "白虎大街");
        set ("long", @LONG

你走在一条宽阔的石板大街上，东面就快到城中心了，可以看到钟楼
耸立于前。北边有一座大的酒楼，里面唏唏嚷嚷，热闹非凡。南边有
一座大府邸，高墙青瓦，一定是什么大官住的地方。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "south" : __DIR__"zhongguan",
                "north" : __DIR__"ziyanglou",
                "west" : __DIR__"baihu-w3",
                "east" : __DIR__"baihu-w1",
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


