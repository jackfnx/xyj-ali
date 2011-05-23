
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
    int phase = NATURE_D->get_current_day_phase();

    if (me != query("owner")) return 0;
    if (me->query("combat_exp") < 50000) return 0;
    if (me->query("dntg/hell") == "done") return 0;
    if (me->query_temp("dntg_hell/next")) return 0;
    if (phase > 0 && phase < 5) {tell_object(me, "大白天的睡什么觉？\n");return 1;}
    if (!is_drunk(me)) {tell_object(me, "你精神十足，不需要睡觉。\n");return 1;}

    message_vision("$N喝得酩酊大醉，倚在在铁板桥边松阴之下，霎时间睡着了。\n",me);
    remove_call_out("go_hell");
    call_out("go_hell", 2+random(5), me);
    return 1; 
}

void go_hell(object me)
{
    object env;
    object hei, bai;
    object piwen;
    string bwc = "/d/death/npc/baiwuchang";
    string hwc = "/d/death/npc/heiwuchang";
    string hell_room = "/d/death/new-zhaopo";
    mapping wang = ([ "qingguang":"秦广王", "songdi":"宋帝王", "chujiang":"楚江王",
        "chuguan":"仵官王", "pingdeng":"平等王", "dushi":"都市王", "taishan":"泰山王",
        "lunzhuan":"轮转王", "biancheng":"卞城王", "yanluo":"阎罗王" ]);
    string sb;

    tell_object(me, HIB "\n睡梦中忽见两人走了过来，大声喝道：“"
                + me->query("name") + "，汝阳寿已尽，吾等奉冥王之命，特来勾你。”\n"
                + "说罢不容分说，拿根铁索往你颈上一套，拉了就走。\n\n" NOR);
    me->move(hell_room);
    env = environment(me);
    if (!(bai = present("bai wuchang", env))) {
        bai = new(bwc);
        bai->move(env);
    }
    if (!(hei = present("hei wuchang", env))) {
        hei = new(hwc);
        hei->move(env);
    }

    piwen = new(__DIR__"piwen");
    if (random(2)) piwen->move(hei);
    else piwen->move(bai);

    sb = keys(wang)[random(sizeof(wang))];
    me->set_temp("dntg_hell/next", sb);
    piwen->set("long","    查"+me->query("name")
                + "阳寿已尽，着令黑白无常将其魂魄勾拿归案。\n\n"
                + "                            "+wang[sb]+"  谕\n\n\n");
    piwen->set("target", me->query("name"));
    call_out("destruct_me", 1);
}

void destruct_me()
{
    destruct(this_object());
}

