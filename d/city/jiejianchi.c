// ALi by NewX
//changan city

inherit ROOM;

void create ()
{
    set ("short", "解剑池");
    set ("long", @LONG

这里曾经是开国元勋秦琼的府邸，后来秦琼获罪，这里也就荒废了。
据说之后的一段时间里，这里经常闹鬼。袁天罡在此地探查一番后，
认为此地杀气过重，当初秦琼在此居住时，尚可镇压杀气，如今秦琼
不再，杀气失去压制，于是产生了各种问题。为此，袁天罡特意在此
修建了一座解剑池，用以化解杀气。
LONG);
    //set("item_desc", ([" *** " : " *** ", ]));

    set("exits", 
    ([ //sizeof() == 1
            "north" : __DIR__"qinglong-e2",
    ]));

    set("outdoors", "changan");
    setup();
}

void init()
{
    add_action("do_bath", "bath");
}

int do_bath(string arg)
{
    object me;
    me = this_player();
    message_vision("$N诚心实意的跪在地上，捧起一把池水，浇在了头上。\n", me);
    me->start_busy(3+random(4));
    call_out("bath_finish", 3, me);
    return 1;
}

void bath_finish(object me)
{
    if (me->query("bellicosity") < 50) {
        message_vision("$N身上散发出一阵祥和之气，周围的人忍不住驻足观看。\n", me);
    }
    else if (random(me->query_kar() + 40) > 40) {
        message_vision("周围的人都感觉到$N身上浓重的杀气变淡了一些。\n", me);
        me->add("bellicosity", -50);
    }
    else {
        message_vision("池水浇在$N身上竟冒起一阵阵黑烟，$N也不禁发出几声惨叫，慌忙站起了身来。\n", me);
    }
}