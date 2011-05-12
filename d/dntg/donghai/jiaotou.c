inherit NPC;

void create()
{
    set_name("禁军教头", ({"jinjun jiaotou", "jiaotou"}));
    set("title", "傲来国");
    set("gender", "男性");
    set("age", 45);

    set("max_gin", 500);
    set("eff_gin", 500);
    set("gin", 500);
    set("max_kee", 500);
    set("eff_kee", 500);
    set("kee", 500);
    set("max_sen", 500);
    set("eff_sen", 500);
    set("sen", 500);

    set("combat_exp", 35000);

    set_skill("unarmed", 70);
    set_skill("spear", 70);
    set("force", 500);
    set("force_factor", 40);
    set_skill("dodge", 70);
    set_skill("parry", 70);
    setup();

    carry_object("/d/obj/cloth/bingfu")->wear();
    carry_object("/d/obj/weapon/spear/tieqiang")->wield();

}
void init()
{
    add_action("do_answer", "answer");
    add_action("guard_dir", ({ "go", "south" }));
}

int guard_dir(string dir)
{
    object who = this_player();
    string verb = query_verb();
    object helper = query("helper");

    if (verb != "go") dir = verb;
    if (!helper) return 0;
    if (!living(this_object())) return 0;
    if (environment() != helper->get_drillent_room()) return 0;
    if (dir != "south") return 0;
    if (who->query("aolai_drill_allow")) return 0;

    tell_object(who, "禁军教头喝道：我国兵马正在里面训练！你来这干什么(answer)？\n"
                    + "(０．比武　１．看热闹　２．捣乱　３．从军)\n");
    who->set_temp("aolai_drill_wait_answer", 1);
    return 1;
}

int do_answer(string arg)
{
    string *ans = ({"比武","看热闹","捣乱","从军"});
    object who = this_player();

    if (!who->query_temp("aolai_drill_wait_answer")) return 0;
    if (!arg) return notify_fail("你说什么？\n");
    if (arg == "0" || arg == "1" || arg == "2" || arg == "3")
        arg = ans[atoi(arg)];
    message_vision("$N答道：" + arg + "。\n", who);
    if (arg == "看热闹") {
        command("consider");
        command("say 看热闹可以，但不准大声喧哗，扰乱训练。\n");
        who->set_temp("aolai_drill_allow", 1);
    }
    else
        command("say 你胡说什么？别来捣乱！\n");
    return 1;
}

void unconcious()
{
    object ob;
    object me = this_object();
    object where = environment (me);

    message_vision("\n$N喊到：＂好啊，你敢到这行凶！看我们怎么收拾你！＂说罢跌跌撞撞勉强爬回演武场。\n",me);
    message_vision("\n又一个$N走了过来。\n",me);
    ob = new(__FILE__);
    ob->move(where);
    destruct(me);
}

void die()
{
    unconcious();
}

