// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ROOM;

void create ()
{
        set ("short", "货行仓库");
        set ("long", @LONG

这里是家大货行的仓库，里面货架上堆着不少货物，地下还有不少货
柜。货行是靠替人送货为生，信用还是不错。不时有马车出入装卸货
物，忙坏了一旁的伙计。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "northwest" : __DIR__"wailiu3",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/dai" : 1,
                __DIR__"npc/huoji" : 3,
        ]));


//        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

