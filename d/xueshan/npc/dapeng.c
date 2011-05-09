// dapeng.c...weiqi, 97.09.27.

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("大鹏明王", ({"dapeng mingwang", "dapeng", "mingwang", "wang"}));
    set("title", "云程万里");
    set("gender", "男性" );
    set("age", 45);
    set("per", 30);
    set("str", 30);
    set("long", "据说大鹏明王与其兄孔雀明王是凤凰之子，有号令百鸟之能。\n"
        "鲲鹏祖师自称是他们兄弟二人之父，不过他与孔雀明王都没有承认。\n"
        "因为孔雀明王的缘故，大鹏明王与佛门结下深仇，生平最恨的就是和尚。\n");
    set("class", "yaomo");
    set("combat_exp", 1800000);
    set("attitude", "peaceful");
    create_family("大雪山", 2, "明王");
    set("rank_info/respect", "明王");
    set_skill("unarmed", 150);
    set_skill("pressheart-hand", 150);
    set_skill("dodge", 190);
    set_skill("peripateticism", 200);
    set_skill("parry", 170);
    set_skill("throwing", 170);
    set_skill("sword", 180);
    set_skill("avian-sword", 200);
    set_skill("blade", 180);
    set_skill("ice-blade", 200);
    set_skill("force", 150);
    set_skill("iceblood-force", 180);
    set_skill("literate", 150);
    set_skill("spells", 160);
    set_skill("dengxian-dafa", 180);
    map_skill("spells", "dengxian-dafa");
    map_skill("force", "iceblood-force");
    map_skill("unarmed", "pressheart-hand");
    map_skill("sword", "avian-sword");
    map_skill("blade", "ice-blade");
    map_skill("dodge", "peripateticism");

    set("max_kee", 3500);
    set("max_sen", 3500);
    set("force", 3500);
    set("max_force", 1800);
    set("mana", 4000);
    set("max_mana", 2000);
    set("force_factor", 120);
    set("mana_factor", 100);

    set_temp("apply/damage", 50);
    set_temp("spply/armor", 50);
    set_temp("apply/dodge", 50);

    set("cast_tuntian", 1);
    set("cast_juanbi", 1);
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
                (: cast_spell, "juanbi" :),
                (: cast_spell, "tuntian" :),
                (: perform_action, "sword", "chaofeng" :),
    }));

    setup();
    carry_object("/d/obj/cloth/choupao")->wear();
    carry_object("/d/obj/weapon/sword/fenghuang-qin")->wield();
}

int check_heshang(object ob)
{
    return (string)ob->query("class") == "bonze" && (string)ob->query("gender") == "男性";
}

void attempt_apprentice(object ob)
{
    if (check_heshang(ob)) {
        command("kick " + ob->query("id"));
        command("say 快走，快走！我一看到和尚就有气。\n");
        return;
    }

    if ((string)ob->query("family/family_name") == "大雪山"){
        if ((int)ob->query("family/generation") > 4) {
            command("say 没有四大护法的推荐，本王不会考虑的。\n");
        } else {
            if ((int)ob->query("combat_exp") >= 150000) {
                command("nod ");
                command("say 好，" + RANK_D->query_respect(ob) + "好好跟我干，将来大有可为！\n");
                command("recruit " + ob->query("id"));
            } else {
                command("say 你还是找青狮，白象他们先练着吧。\n");
            }
        }
    } else {
        command("hmm");
        command("say 这位" + RANK_D->query_respect(ob) + "，在本门可没有一步登天的事。\n");
    }

    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "yaomo");
}

void init()
{
    object ob = this_player();

    ::init();
    if (check_heshang(ob) && random(3) > 1) {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }
}

void greeting(object ob)
{
    if (!ob || environment(ob) != environment()) return;
    
    switch (random(1)) {
        case 0:
            command("kick " + ob->query("id"));
            command("say 死贼秃！");
            break;
    }
}

