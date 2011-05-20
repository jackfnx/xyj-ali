// fighter.c

inherit NPC;

void create()
{
    set_name("巡海夜叉",({"ye cha","yecha","fighter"}));
    set("gender", "男性");
    set("age", 30);
    set("long", "    \n东海龙宫的一名夜叉，龙王的贴身护卫。\n");

    set("attitude", "peaceful");
    set("class", "dragon");
    set("combat_exp", 30000);
    set("daoxing", 25000);
    set("kee", 500);
    set("max_kee", 500);
    set("sen", 600);
    set("max_sen", 600);
    set("force", 700);
    set("max_force", 700);
    set("mana", 800);
    set("max_mana", 800);
    set("force_factor", 20);
    set("mana_factor", 20);
    set("str", 30);

    set_skill("spells", 60);
    set_skill("seashentong", 40);
    set_skill("force", 60);
    set_skill("dragonforce", 60);
    set_skill("fork", 60);
    set_skill("fengbo-fork", 60);
    set_skill("dodge", 100);

map_skill("spells", "seashentong");
map_skill("force", "dragonforce");
map_skill("fork", "fengbo-fork");

setup();

carry_object("/d/obj/armor/tenjia")->wear();
carry_object("/d/obj/armor/niupi")->wear();
carry_object("/d/obj/weapon/fork/fork")->wield();
}

int accept_fight(object who)
{
    object me = this_object();
    object weapon;
    string weapon_id;

    weapon = who->query_temp("weapon");
    if (weapon) weapon_id = weapon->query("id");

    if ((weapon_id == "da kan dao" && who->query_temp("dntg/donghai")=="try_dao")
    ||  (weapon_id == "jiu gu cha" && who->query_temp("dntg/donghai")=="try_cha")
    ||  (weapon_id == "mei hua chui" && who->query_temp("dntg/donghai")=="try_chui")
    ||  (weapon_id == "hua gan ji" && who->query_temp("dntg/donghai")=="try_ji")
        ) {
        message_vision("巡海夜叉斜眼看了$N一眼，撇嘴道：好！就让我领教领教阁下的手段！\n", who);
        me->fight_ob(who);
        who->fight_ob(me);
        remove_call_out("check_result");
        call_out("check_result", 1, me, who);
        return 1;
    } else {
        message_vision("巡海夜叉斜眼看了$N一眼，撇嘴道：就凭你？不配跟本大神动手。\n", who);
        return 0;
    }
}

int check_result(object me, object who)
{
    int my_max_kee, his_max_kee;
    object weapon;
    string weapon_id, want_id;

    weapon = who->query_temp("weapon");
    if (weapon) weapon_id = weapon->query("id");

    if (who->query_temp("dntg/donghai")=="try_dao") want_id="da kan dao";
    else if (who->query_temp("dntg/donghai")=="try_cha") want_id="jiu gu cha";
    else if (who->query_temp("dntg/donghai")=="try_chui") want_id="mei hua chui";
    else if (who->query_temp("dntg/donghai")=="try_ji") want_id="hua gan ji";

    if (!who) return 1;
    if (environment(who) != environment(me)) return 1;
    my_max_kee = me->query("max_kee");
    his_max_kee = who->query("max_kee");

    if (want_id != weapon_id) {
        message_vision("$N对$n撇嘴一笑，道：我还以为阁下十八般武艺样样精通呢！\n", me, who);
        message_vision("$N不屑的冷哼一声，转身离开了。\n", me);
        destruct(me);
        return 1;
    }

    if (me->is_fighting()) {
        call_out("check_result", 1, me, who);
        return 1;
    }

    if (((int)who->query("kee")*100/his_max_kee)<=50) {
        message_vision("$N对$n仰天狂笑：不过如此嘛！\n", me, who);
        message_vision("$N不屑的冷哼一声，转身离开了。\n", me);
        destruct(me);
        return 1;
    }

    if (((int)me->query("kee")*100/(1+my_max_kee)) <= 50) {
        message_vision("$N说道：阁下武功高强，再试试别的兵器吧！\n", me);
        who->command_function("drop " + weapon_id);
        message_vision("$N大喊道：这兵器不趁手！快换新的！\n", who);
        command("sigh");
        command("get " + weapon_id);
        who->set("dntg/donghai", weapon_id);
        who->delete_temp("dntg/donghai");
        message_vision("$N一溜烟跑了。\n",me);
        destruct(me);
        return 1;
    }

    return 1;
}
