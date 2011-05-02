// flag.c

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
}

void init()
{
    object who = environment();
    
    if (userp(who)) {
        if (query("owned")) {
            if (query("owned") != who->query("id"))
                call_out("destruct_me", 1, who, this_object());
        } else {
            set("owned", who->query("id"));
        }
    }
    add_action("do_wave", "wave");
}

void destruct_me(object who, object me)
{
    message_vision("一阵清风吹过，$n化作一团灰烬。\n", who, me);
    destruct(me);
}

int do_wave(string arg)
{
    object me = this_player();
    object hb;

    if (me->query("id") != query("owned") || me != environment()) return 0;
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
    me->set("dntg/huaguo", "allow");
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
    destruct(this_object());
}
