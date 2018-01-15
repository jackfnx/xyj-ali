
#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("批文", ({"pi wen","piwen","wen"}));
    set_weight(10);
    set("unit", "张");
    setup();
}

void init()
{
    object wc, me = this_player();
    if (userp(environment()))
        call_out("wc_lootme", 1, me);
    add_action("do_look","look");
}

void wc_lootme(object me)
{
    object wc;

    if (environment() != me) return;

    if (wc = query("bai") || wc = query("hei")) {
        if (environment(me) == environment(wc))
            message_vision("$N一把将$n手中的批文夺了回去，道：阴司公文岂可乱抢？\n", wc, me);
        else
            message_vision("$N急急忙忙跑过来，一把将$n手中的批文夺了回去，道：阴司公文岂可乱抢？\n", wc, me);
        move(wc);
    }
}

int do_look(string arg)
{
    object me = this_player();
    object helper = me->query_temp("dntg_helper");

    if (!arg || !id(arg)) return 0;
    if (!helper) return 0;
    write(this_object()->long());
    if (query("target") != me->query("name")) return 1;
    me->set_temp("dntg_hell/next", query("wang"));
    message_vision(HIR "$N看罢批文，勃然大怒，把批文撕了个粉碎，大叫：“待我去找这个昏王评理！”\n" NOR, me);
    __DIR__"trouble"->install(me, helper->get_palace_rooms());
    destruct(this_object());
    return 1;
}

void setup_piwen(object me, object bai, object hei)
{
    mapping wangs = ([ "qingguang":"秦广王", "songdi":"宋帝王", "chujiang":"楚江王",
        "chuguan":"仵官王", "pingdeng":"平等王", "dushi":"都市王", "taishan":"泰山王",
        "lunzhuan":"轮转王", "biancheng":"卞城王", "yanluo":"阎罗王" ]);
    string wang;

    wang = keys(wangs)[random(sizeof(wangs))];
    set("long","    查" + me->query("name")
                + "阳寿已尽，着令黑白无常将其魂魄勾拿归案。\n\n"
                + "                            "+wangs[wang]+"  谕\n\n\n");
    set("target", me->query("name"));
    set("wang", wang);

    bai->set("inquiry/勾魂", (: call_other, __FILE__, "assail", this_object() :));
    bai->set("inquiry/冤枉", (: call_other, __FILE__, "assail", this_object() :));
    bai->set("inquiry/冤屈", (: call_other, __FILE__, "assail", this_object() :));
    hei->set("inquiry/勾魂", (: call_other, __FILE__, "assail", this_object() :));
    hei->set("inquiry/冤枉", (: call_other, __FILE__, "assail", this_object() :));
    hei->set("inquiry/冤屈", (: call_other, __FILE__, "assail", this_object() :));
    set("bai", bai);
    set("hei", hei);
}

string assail(object ob, object wc)
{
    object me = this_player();
    if (!ob || !me) return 0;
    
    if (me->query("name") != ob->query("target")) return 0;

    ob->move(wc);
    return "我按批文所书勾人，若有冤屈，可与发此公文之冥王申诉(complain)。";
}
