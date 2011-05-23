// flag.c

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("大旗", ({"flag","qi"}));
    set("unit", "面");
    set_weight(500);
    set("long", @LONG
        ***********************************************
        **      得此旗者可为仙灵福地水帘洞之洞主     **
        ***********************************************
LONG);
    set("env/invisibility", 1);
    set("no_get", 1);
    seteuid(getuid());
    setup();
}

string short()
{
    object owner = query("owner");
    int inv = (int)query("env/invisibility");
    
    if (!owner || !inv) return ::short();
    else return sprintf("%s[owner: %s]", ::short(), geteuid(owner));
}

void place_room(string room)
{
    room->set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床(bed)、
石凳，各种家当样样俱全。好一座天造地设的安身之所。正中间插着
一杆大旗(flag)。
LONG);
    room->set("item_desc/flag",
            "一面迎风招展的三色大旗，在空旷之处迎风挥舞(wave)起来一定煞是好看，但似乎很难拔(ba)动。\n");
    this_object()->set("home", room);
    this_object()->move(room);
}

void init()
{
    object who = environment();
    
    if (userp(who)) {
        if (query("owner") != who)
            call_out("destruct_me", 1, who, this_object());
    }
    add_action("do_ba", "ba");
    add_action("do_wave", "wave");
}

void destruct_me(object who, object me)
{
    message_vision("一阵清风吹过，$n化作一团灰烬。\n", who, me);
    destruct(me);
}

int do_ba(string arg)
{
    object me = this_player();
    object env = environment();

    if (file_name(env) != query("home")) return 0;

    if (!arg || !id(arg)) return notify_fail("你要拔什么？\n");

    if (me->query("dntg/huaguo") == "done")
        return notify_fail("你手握"+name()+"，不禁想起自己当年在此称王的快乐时光。\n");

    if (me != query("owner"))
        return notify_fail("你使尽吃奶的力气也没将"+name()+"拔出来。\n");

    if (me->query("kee") <= 200) {
        me->unconcious();
        return 1;
    }
    me->receive_damage("kee", 200);
    if (random(10) < 5)
        message_vision("$N使尽吃奶的力气也没将"+name()+"拔出来。\n", me);
    else {
        env->set("long", @LONG

一座宽大的石房，房内有石窝、石灶、石碗、石盆、石床(bed)、
石凳，各种家当样样俱全。好一座天造地设的安身之所。
LONG);
        env->delete("item_desc/flag");
        this_object()->delete("env/invisibility");
        this_object()->delete("no_get");
        this_object()->move(me);
        message_vision("$N大喝一声，将"+name()+"拔了下来。\n", me);
    }
    return 1;
}

int do_wave(string arg)
{
    object me = this_player();
    object hb;

    if (me != query("owner") || me != environment()) return 0;
    if (!arg || !id(arg)) return notify_fail("你想挥舞什么？\n");

    if (!(hb = me->query_temp("dntg_helper"))) {
        destruct_me(me, this_object());
        return 1;
    }
    if (!hb->check_huaguo_waveroom())
        return notify_fail("看样子，要挥舞这"+name()+"还是应该找片开阔地。\n");
    if (me->query("dntg/huaguo") == "done")
        return notify_fail("你挥起手中的"+name()+"，想起了当年在此称王的快乐时光。\n");
    message_vision("$N挥舞着起旗子，大喝一声：“大造化！大造化！下面没水！原来是一座铁板桥。桥那边是一座天造地设的家当。兄弟们快去呀！”\n", me);
    call_out("monkeys_jump", 2, environment(me));
    call_out("monkeys_follow", 1, me);
    load_object("/obj/empty");
    move("/obj/empty");
    return 1;
}

void monkeys_jump(object where)
{
    object who1 = present("hou zi 1", where);
    object who2 = present("hou zi 2", where);
    object who3 = present("hou zi 3", where);
    object who4 = present("hou zi 4", where);
    if (who1) destruct(who1);
    if (who2) destruct(who2);
    if (who3) destruct(who3);
    if (who4) destruct(who4);
    message("vision", "猴子们听罢争先恐后的跳下瀑布。\n", where);
    set("monkeys_jumped", 1);
}

void monkeys_follow(object me)
{
    object hb;
    object houzi;
    object where = environment(me);
    
    if (!(hb = me->query_temp("dntg_helper"))) {
        destruct(this_object());
        return;
    }
    
    if (!query("monkeys_jumped") || !hb->check_huaguo_voteroom()) {
        remove_call_out("monkeys_follow");
        call_out("monkeys_follow", 2, me);
        return;
    }
    
    message_vision("一群猴子跟着$N蹦蹦跳跳的跑了过来。\n", me);
    while (!present("hou zi 4", where)) {
        houzi = new(__DIR__"hou");
        houzi->set("king", me);
        houzi->move(where);
        me->set_temp("people/" + me->add_temp("people_num", 1), houzi);
    }
    me->start_busy(25);
    call_out("jing_appearing", 25, me);
}

void jing_appearing(object me)
{
    object jing;
    object where = environment(me);
    
    message("vision", HIR "\n黑暗中突然窜出一群狼虫虎豹！！！\n\n" NOR, where);
    while (!present("jing 3", where)) {
        jing = new(__DIR__"jing");
        jing->move(where);
        jing->kill_ob(me);
    }
    destruct(this_object());
}
