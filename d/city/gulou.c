// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//changan city

inherit ROOM;

void create ()
{
        set ("short", "鼓楼");
        set ("long", @LONG

这座鼓楼是前朝所建，本是坐落在长安的市中心的。因为长安城多次
改建，这里已经逐渐被废弃了。这鼓楼是一座长方形的青砖建筑，看
起来相当的古朴凝重，顶上成拱形，雕有许多鸟兽鱼虫。每到傍晚，
沉闷的鼓声就会随着蔼蔼暮气，在这偏僻的小巷中回荡。北面是城隍
庙，前来赶庙会上香的人倒是很多。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "east" : __DIR__"wailiu2",
                "west" : __DIR__"baozipu",
                "south" : __DIR__"wailiu4",
                "north" : __DIR__"chenghuang",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));


//        set("outdoors", "changan");
   set("no_clean_up", 0);
        setup();
   replace_program(ROOM);
}



