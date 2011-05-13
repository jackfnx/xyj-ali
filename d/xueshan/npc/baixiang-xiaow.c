// baixiang-xiaow.c...weiqi, 97.09.15.

inherit NPC;

void create()
{
    set_name("白象小王", ({"baixiang xiaowang", "baixiang", "xiaowang"}));
    set("title", "狮驼山");
    set("gender", "男性" );
    set("age", 43);
    set("per", 112);//no rongmao description.
    set("str", 50);
    set("long", "这位白象小王是有名的大力士。以前在狮驼山做二大王，\n"
        "与青狮老魔交称莫逆。狮驼山被剿灭后，他跟着青狮老魔一起投奔大鹏明王，\n"
        "做了护法尊者。谁知，加入大雪山以后，他审时度势，果断的抛弃了青狮老魔，\n"
        "转而投入大鹏明王麾下，甚至主动替大鹏监视青狮的动向。于是，\n"
        "他很快的获得了大鹏的信任，在大雪山中，混的如鱼得水。\n"
        "谁想，风云突变，孔雀明王回归后又把大鹏明王的势力打压下去，\n"
        "白象小王看准时机，转而向孔雀明王效忠，进一步提升了地位。\n"
        "他觉得自己原本『二大王』称号过于僭越，因此主动改名为『白象小王』。\n"
        "他生平最怕老鼠，因此看到尖嘴猴腮的人就讨厌。\n");
    set("class", "yaomo");
    set("combat_exp", 800000);
    set("attitude", "peaceful");
    create_family("大雪山", 2, "弟子");
    set_skill("unarmed", 150);
    set_skill("pressheart-hand", 80);
    set_skill("dodge", 60);
    set_skill("peripateticism", 70);
    set_skill("parry", 120);
    set_skill("blade", 110);
    set_skill("ice-blade", 120);
    set_skill("force", 90);
    set_skill("iceblood-force", 80);
    set_skill("literate", 70);
    set_skill("spells", 90);
    set_skill("dengxian-dafa", 80);
    map_skill("spells", "dengxian-dafa");
    map_skill("force", "iceblood-force");
    map_skill("unarmed", "pressheart-hand");
    map_skill("blade", "ice-blade");
    map_skill("dodge", "peripateticism");

    set("max_kee", 1200);
    set("max_sen", 600);
    set("force", 1600);
    set("max_force", 800);
    set("mana", 800);
    set("max_mana", 400);
    set("force_factor", 60);
    set("mana_factor", 20);

    set("eff_dx", -200000);
    set("nkgain", 400);

    set("cast_juanbi", -1);
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
                (: cast_spell, "juanbi" :),
    }));

    setup();
    carry_object("/d/obj/armor/yinjia")->wear();
    carry_object("/d/obj/weapon/blade/yanblade")->wield();
}

void attempt_apprentice(object ob)
{
    if ((int)ob->query("str") < 20) {
        command("kick " + ob->query("id"));
        command("say 快走，快走！我一看到尖嘴猴腮的人就有气。\n");
        return;
    }

    if ((string)ob->query("family/family_name")=="大雪山") {
        if ((int)ob->query("family/generation") < 2) {
            command("say 不敢，不敢。我该拜" + RANK_D->query_respect(ob) + "您为师才是。\n");
        } else if ((int)ob->query("family/generation") == 2) {
            command("say 你这个" + RANK_D->query_rude(ob) + "别来消遣你爷爷我了！\n");
        } else if ((int)ob->query("family/generation") == 3) {
            if ((string)ob->query("family/master_id") == "dapeng mingwang") {
                command("shake");
                command("say 我怎么能抢明王陛下的徒弟呢。\n");
            } else {
                command(":D");
                command("say 你这个" + RANK_D->query_rude(ob) + "是不是被师父赶出来了？你爷爷我今天心情好，就收留你吧...\n");
                command("recruit " + ob->query("id") );
            }
        } else {
            if((int)ob->query("combat_exp") >= 50000){
                command(":D ");
                command("say 好，" + RANK_D->query_respect(ob) + "好好跟我干，将来有你的好处！\n");
                command("recruit " + ob->query("id") );
            } else {
                command("say 你还是找鹦鹉，乌鸦他们先练着吧。\n");
            }
        }
    } else {
        command("hmm");
        command("say 这位" + RANK_D->query_respect(ob) + "，你还是找鹦鹉，乌鸦他们先练练吧。\n");
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
    if ((string)ob->query("gender")=="男性" && (int)ob->query("str") < 20 && random(3) > 1) {
        remove_call_out("greeting1");
        call_out("greeting1", 1, ob);
    }
    else if ((string)ob->query("family/family_name") == "陷空山无底洞" && random(3) > 1) {
        remove_call_out("greeting2");
        call_out("greeting2", 1, ob);
    }
}

void greeting1(object ob)
{
    if (!ob || environment(ob) != environment()) return;

    switch (random(1)) {
        case 0:
            command("kick " + ob->query("id"));
            command("say 尖嘴猴腮！");
            command("laugh");
            break;
    }
}

void greeting2(object ob)
{
    if (!ob || environment(ob) != environment()) return;

    switch (random(1)) {
        case 0:
            command("fear " + ob->query("id"));
            command("say 老鼠！老鼠！");
            command("kick " + ob->query("id"));
            command("laugh");
            break;
    }
}
