// by snowcat 10/05/1997
// zhangmen.c 掌门

inherit __DIR__"puppet";

string zm_apply();

void create()
{
    set_name("大弟子", ({ "long shen", "longshen" }) );
    set("gender", "男性" );
    set("age", 30);
    set("str", 30);
    set("per", 30);
    set("int", 30);
    set("long", "掌门大弟子。\n" );
    set("attitude", "heroism");
    set("combat_exp", 100000);
    set("current_player","none of us");

    me->create_identity("/d/sea/npc/longwang", "/d/sea/inside1");
    me->set("inquiry", ([
        "name" : "嘿嘿，东海龙神便是我。\n",
        "here" : "东海水晶宫是也。\n",
        "掌门大弟子" : (: zm_apply :),
        "掌门弟子" : (: zm_apply :),
        "大弟子" : (: zm_apply :),
        "掌门" : (: zm_apply :), 
        "龙神" : (: zm_apply :),
        "东海龙神" : (: zm_apply :),
    ]) );
    setup();

    carry_object("/d/obj/cloth/linen")->wear();
}

string zm_apply()
{
    object me = this_object();
    object ob = this_player();

    if (me->query("family/family_name") != ob->query("family/family_name"))
    {
        return "我便是本派掌门弟子！\n";
    }
    if (ob->query("betrayer") || ob->query("betray/count"))
    {
        return "你曾叛师欺祖，言无信行不轨，岂能出任掌门弟子一职！\n";
    }
    if (me->query("current_player") == ob->query("id")) 
    {
        return "你又糊涂了！\n";
    }

    ob->set_temp("fangcun_zm_applied", 1);
    if ((string)ob->query("gender") == "男性")
        return "好！师兄有意出任龙神一职？我们就切磋一下吧！\n";
    else return "好！师姊有意出任龙神一职？我们就切磋一下吧！\n";
}

int accept_fight(object ob)
{
    int i;
    object* inv;

    object me = this_object();

    if (me->query("current_player") == ob->query("id"))
    {
        return notify_fail("你又糊涂了！\n");
    }

    if (me->is_fighting())
    {
        command("say 失陪了！\n");
        return notify_fail("这位龙神尚在比武之中，请稍候。\n");
    }

    if (ob->query_temp("fangcun_zm_applied"))
    {
        command("say 好！尚请未来的龙神手下留情。\n");
    }
    else
    {
        command("say 好！我们就切磋一下。\n");
    }

    me->set_temp("zhangmen/kill", 0);
    remove_call_out("check_result");
    call_out("check_result", 1, me, ob);

    fully_recover(me);
    inv = all_inventory(ob);
    for (i=0; i<sizeof(inv); i++)
    {
        if (inv[i]->query_unique())
        {
            message_vision("突然间，$n化一道白光飞去，无影无踪！\n", me, inv[i]);
            destruct(inv[i]);
        }
    }

    return 1;
}

void kill_ob(object ob)
{
    object me = this_object();
    object master;

    if (me->query("current_master"))
        master = present(me->query("current_master"), environment(me));
    if (master)
        master->kill_ob(ob);

    me->set_temp("zhangmen/kill", 1);
    ::kill_ob(ob);
}

int check_result(object me, object ob)
{
    int my_max_kee, his_max_kee;

    my_max_kee  = me->query("max_kee");
    his_max_kee = ob->query("max_kee");

    if (me->is_fighting())
    {
        call_out("check_result",1, me, ob);
        return 1;
    }

    if (!living(me)
    ||  (int)me->query("kee") < 1
    ||  (int)me->query("sen") < 1) return 1;

    if (((int)me->query("kee")*100/(1+my_max_kee)) <= 50)
    {
        object who;

        if (!living(me)
        ||  (int)me->query("kee") < 1
        ||  (int)me->query("sen") < 1) return 1;

        message_vision("$N翻身下拜，连声佩服！\n", me);

        if (me->query_temp("zhangmen/kill") && ob->query_temp("fangcun_zm_applied"))
        {
            message_vision("$N皱了皱眉道：此次比武我未能静心尽力，希望重新来过。\n", me);
            return 1;
        }

        if (ob->query_temp("fangcun_zm_applied") != 1)
            return 1;

        if (me->query("current_master"))
            who = present(me->query("current_master"), environment(me));
        if (who && who->query("id")!=me->query("current_master"))
            who = 0;

        if (who)
        { 
            call_out("master_announce",1,me,who,ob);
        }
        else
        {
            message_vision("$N躬身对$n说道：恭请拜见师父。\n",me,ob);
            command("follow "+ob->query("id"));
            if (!me->query("where"))
                me->set("where", base_name(environment(me)));
            remove_call_out("find_master");
            call_out("find_master", 1, me, ob);
        }
        return 1;
    }

    if (((int)ob->query("kee")*100/his_max_kee)<=50)
    {
        message_vision("$N将$n扶起。\n", me, ob);
    }

    return 1;
}

void find_master(object me, object ob)
{
    object who = present(me->query("current_master"), environment(me));

    if (who && who->query("id")!=me->query("current_master"))
        who = 0;

    if (!who)
    {
        remove_call_out("find_master");
        call_out("find_master", 1, me, ob);
    }
    else
    {
        message_vision("$N见了龙王赶紧下拜，又抬起头朝$n使了个眼色。\n\n", me, ob);
        message_vision("$N微微地点了点头。\n\n", who);
        message_vision("$N退下。\n\n", me);
        me->set_leader(0);
        call_out("master_announce", 1, me, who, ob);
        me->move(me->query("where"));
    }
}

void master_announce(object me, object who, object ob)
{
    CHANNEL_D->do_channel(who, "chat", "东海龙神"+ob->query("name")+"今日走马上任。恭请各位仙长多加捧场！");
    ob->delete_temp("fangcun_zm_applied");
    me->set("new_player", 1);
    convert_identity(me, ob);
}


