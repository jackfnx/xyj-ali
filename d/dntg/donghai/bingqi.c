// bingqi.c

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("兵器",({"bing qi"}));
    set_weight(20000);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long","一大捆兵器，刀、枪、剑、戟、斧、钺、钩、叉\n"
"什么都有，上面都刻有几个大字：＂傲来国制＂。\n");
        set("unit","捆");
    }
}

void init()
{
    object ob = this_object();
    object where = environment();

    if (userp(where)) {
        if (!ob->query("owner"))
            ob->set("owner", where);
        else if (ob->query("owner") != where)
            call_out("destruct_me", 5, ob);
    }
    add_action("quest_give", "give");
}

void destruct_me(object ob)
{
    if (ob) {
        tell_object(environment(ob), "兵器唏哩哇啦撒了一地。\n");
        destruct(ob);
    }
}

int quest_give(string arg)
{
    string name;
    object me = this_player(), who, helper;

    if (me != query("owner"))
        return 0;

    if (!(helper = me->query_temp("dntg_helper")))
        return 0;

    if (sscanf(arg, "bing qi to %s", name) != 1
    &&  sscanf(arg, "%s bing qi", name) != 1)
        return 0;

    if (!(who = present(name, environment(me)))
    ||  !living(who)
    ||  !who->is_character()
    ||  who->is_corpse())
        return 0;

    if (who->query("id") != "beng jiangjun") return 0;

    if (me->query("dntg/huaguo") != "done") {
        message_vision(CYN "$N" CYN "说道：你是谁啊？\n" NOR, who);
        return 1;
    } else if (me->query("dntg/donghai")) {
        message_vision(CYN "$N" CYN "说道：兵器已经够用了，不劳大王操心了。\n" NOR, who);
        return 1;
    } else if (random(10) != 1) {
        message_vision(CYN "$N" CYN "兴奋的叫道：太好了！要是再多一点儿就更好了。\n" NOR, who);
        destruct(this_object());
        return 1;
    } else {
        message_vision(CYN "$N" CYN "高兴得跳了起来。\n" NOR, who);
        message_vision(CYN "$N" CYN "说道：太好了！大王，我们的兵器是够用了，您自己也挑一样称手的家伙吧！\n" NOR, who);
        me->set("dntg/donghai", "begin");
        helper->report_progress(10);
        destruct(this_object());
        return 1;
    }
}

