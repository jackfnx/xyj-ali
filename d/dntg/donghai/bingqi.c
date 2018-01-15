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
    object where, owner;

    if (userp(where = environment())) {
        if (!(owner = query("owner")))
            set("owner", where);
        if (query("owner") != where)
            call_out("destruct_me", 5);
    }
    
    add_action("do_dist", "distribute");
    add_action("do_dist", "distrib");
    add_action("do_dist", "fenfa");
}

void destruct_me()
{
    tell_object(environment(), "兵器唏哩哇啦撒了一地。\n");
    destruct(this_object());
}

int do_dist(string arg)
{
    object me, helper, where, who;

    me = this_player();
    if (me != query("owner"))
        return 0;

    helper = me->query_temp("dntg_helper");
    if (!helper)
        return 0;

    where = environment(me);
    if (!where)
        return 0;

    who = present("beng jiangjun", where);
    if (!who) {
        if (where != helper->get_playg_room())
            return 0;
        where->reset();
        who = present("beng jiangjun", where);
    }
    if (!who || !living(who))
        return 0;

    if (!arg || !id(arg))
        return notify_fail("你要分发什么？\n");

    message_vision("$N拿出一捆兵器，堆在山前，叫道：＂小的们！都来领兵器！＂\n\n", me);
    if (me->query("dntg/huaguo") != "done") {
        message_vision("$N疑惑的看着$n，道：你是何许人也，为何在此喧哗？\n", who, me);
        return 1;
    } else if (me->query("dntg/donghai")) {
        message_vision("$N跑过来说：兵器已经够用了，不劳大王操心了。\n", who);
        return 1;
    } else if (random(10) != 1) {
        message_vision("群猴兴高采烈的围拢过来，你挑我捡，从兵器堆里各自拿了一件兵器。\n", who);
        message_vision("不一会，一捆兵器被抢拾一空。有些动手慢的，没抢到趁手兵器，急得抓耳挠腮，上窜下跳。\n", who);
        destruct(this_object());
        return 1;
    } else {
        message_vision("群猴兴高采烈的围拢过来，你挑我捡，从兵器堆里各自抽了一条兵器。\n", who);
        message_vision("$N在一旁叫道：太好了！大王，我们的兵器是够用了，您自己也挑一样称手的家伙吧！\n", who);
        me->set("dntg/donghai", "begin");
        helper->report_progress(10);
        destruct(this_object());
        return 1;
    }
}
