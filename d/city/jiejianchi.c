// ALi by NewX
//changan city

inherit ROOM;

void create ()
{
    set ("short", "解剑池");
    set ("long", @LONG

这里曾经是开国元勋秦琼的府邸，但是后来秦琼获罪，这里也就荒废
了。据说之后的一段时间，这里经常闹鬼，于是太宗皇帝让袁天罡来
调查此事。袁天罡认为，原因在于此处杀气太重，秦琼在此记住时尚
可镇压杀气，如今秦琼已去，杀气失去压制，于是产生了各种问题。
为此，袁天罡特意在此修建了一座解剑池，用以化解杀气。
LONG);
        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 1
                "north" : __DIR__"qinglong-e2",
        ]));

        set("outdoors", "changan");
        setup();
}

