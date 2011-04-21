// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "冥河岸边");
    set("long", @LONG

这里就是冥河，只见一条长长的河水横亘在面前。河水是浑浊的，两
边都看不到尽头，对岸也因为离得太远看上去模模糊糊的。河边伫立
着一座样式古朴的石碑(stone)，和一个歪歪扭扭的牌子(sign)。
LONG);

    set("item_desc", ([
        "stone" : @STONE
        冥河的传说

传说冥河的长度是无限的，它的源头从来没有人见过，有人说它发源
与天上，其实它就是天上的天河。天河的尽头流入人间，又经人间流
入地府，在人间的河段就是通天河，在地府的河段就是冥河。

传说冥河的历史也是无限的，没有人能说清冥河是什么时候出现的，
唯一能确定的是，在开天辟地之初，冥河已经存在了。因此，冥河的
历史至少比绝大多数的上古神祗更古老。

冥河的无限是绝对的，正如在生的面前，死是绝对的，也是无限的。

STONE,
        "sign" : "冥河注意事项\n"
                "一、别喝冥河水(drink)！！！\n"
                "二、别把冥河水装走(fill)！！！\n"
                "三、别往冥河里挑(dive)，就算要跳，也要记得带避水咒啊！！！\n"
                "       ——地藏王菩萨留\n"
    ]));

    set("exits", ([ //sizeof() == 1
        "east" : "/d/death/new-yinyangta",
        "down" : __DIR__"styxwater1",
    ]));
    
    set("resource/poison", ([
        "name" : "冥河水",
        "condition" : "styx_water",
        "effect" : 100,
    ]));

    set("objects", ([ //sizeof() == 1
        __DIR__"npc/minghe" : 1,
    ]));
    
    setup();
}
