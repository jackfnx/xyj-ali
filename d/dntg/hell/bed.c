
#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("地狱之床", ({"hell bed"}));
    set("env/invisibility", 1);
    set_weight(100);
    set("no_get", 1);
    seteuid(getuid());
    setup();
    call_out("destruct_me", 1200);
}

string short()
{
    object owner = query("owner");
    if (!owner) return "地狱之床";
    else return sprintf("地狱之床(owner: %s)", geteuid(owner));
}

void init()
{
    add_action("do_sleep", "sleep");
}

int is_drunk(object me)
{
    int limit = me->query("con")*6 + (int)me->query("max_force")/50;
    int duration = me->query_condition("drunk");
    if (duration > limit/10) return 1;
    return 0;
}

int do_sleep(string arg)
{
    object me = this_player();

    if (me != query("owner")) return 0;
    if (me->query("combat_exp") < 50000) return 0;
    if (me->query("dntg/hell") == "done") return 0;
    if (me->query_temp("dntg_hell/next")) return 0;
    if (!is_drunk(me)) {tell_object(me, "你精神十足，不需要睡觉。\n");return 1;}

    message_vision("$N喝得酩酊大醉，倚在在铁板桥边松阴之下，霎时间睡着了。\n", me);
    me->set_temp("block_msg/all", 1);
    me->disable_player("<睡梦中>");

    remove_call_out("go_hell");
    call_out("go_hell", 2+random(5), me);
    return 1;
}

void go_hell(object me)
{
    object env, bai, hei, piwen;

    if (!query("hell_ent_room")) return;

    me->move(query("hell_ent_room"));
    env = environment(me);
    if (!(bai = present("bai wuchang", env))) {
        bai = new(query("npc_baiwc"));
        bai->move(env);
    }
    if (!(hei = present("hei wuchang", env))) {
        hei = new(query("npc_heiwc"));
        hei->move(env);
    }
    me->enable_player();
    me->set_temp("block_msg/all", 0);
    tell_object(me, HIB "\n睡梦中忽见两人走了过来，大声喝道：“"
        + me->query("name") + "，汝阳寿已尽，吾等奉冥王之命，特来勾你。”\n"
        + "说罢不容分说，拿根铁索往你颈上一套，拉了就走。\n\n" NOR);
    me->command_function("look");

    piwen = new(__DIR__"piwen");
    piwen->setup_piwen(me, bai, hei);
    call_out("destruct_me", 1);
}

void destruct_me()
{
    destruct(this_object());
}
