// cracked by vikee 2/09/2002   vikee@263.net

//baihua xianzi
inherit NPC;

void create()
{
    set_name("百花仙子", ({"baihua xianzi", "baihua", "xianzi"}));
    set("long", @LONG
一个气质高绝，傲气凌人的美艳女子。
她便是三界百花生杀大权的百花仙子，据说三界内的群芳都必须听从
她的号令，否则将被她整治的生不如死。
她酿造的百花酿，乃是三界第一玉液。
LONG);

    set("title", "群芳之主");
    set("gender", "女性");
    set("age", 20);
    set("class", "xian");
    set("attitude", "friendly");
    set("rank_info/respect", "仙子");
    set("per", 30);
    set("int", 30);
    set("max_gin", 600);
    set("max_sen", 3000);
    set("max_kee", 3000);
    set("force", 2000);
    set("max_force", 2000);
    set("force_factor", 100);
    set("max_mana", 2000);
    set("mana", 2000);
    set("mana_factor", 200);
    set("combat_exp", 800000);

    set("inquiry", ([
        "name" : "本座，便是三界群芳之主，执掌百花生杀大权。",
        "嫦娥" : "本座不想听到这个名字。",
        "百花酿" : "本座的百花酿乃三界第一玉液，可惜这里花种太少，如能在酒中加入(add)它种鲜花，定能更增风味。",
        "白牡丹" : "那个贱人？竟然不遵本座的号令，早晚让她生不如死。",
    ]));
    set("eff_dx", 200000);
    set("nkgain", 350);
    
    set_skill("literate", 100);
    set_skill("unarmed", 80);
    set_skill("dodge", 70);
    set_skill("force", 80);
    set_skill("parry", 80);
    set_skill("spells", 80);
    set_skill("moonshentong", 80);
    set_skill("flower-hand", 200);
    set_skill("moonforce", 80);
    set_skill("moondance", 70);
    set_skill("sword", 80);
    set_skill("snowsword", 80);
    map_skill("spells", "moonshentong");
    map_skill("unarmed", "flower-hand");
    map_skill("force", "moonforce");
    map_skill("dodge", "moondance");
    
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
            (: cast_spell, "arrow" :),
            (: cast_spell, "mihun" :),
            (: cast_spell, "shiyue" :),
    }));
    create_family("月宫", 2, "弟子");
    setup();

    carry_object("/d/moon/obj/luoyi")->wear();
    //carry_object("/d/obj/book/makeupbook");
    if (clonep()) carry_object("/d/obj/flower/rose")->wear();
}

void attempt_apprentice(object ob)
{
    if ((string)ob->query("gender") != "女性") {
        command("sneer");
        command("say 我不收男人！");
        command("say 趁我心情还算好，赶紧滚吧！\n");
        return;
    }
    
    if (ob->query("family/master_id") == "chang e") {
        command("sneer");
        command("say "+ RANK_D->query_respect(ob)
            + "既然有嫦娥指点，又何必来找我？\n");
        return;
    }

    command("pat "+ob->query("id"));
    command("say 好，希望" + RANK_D->query_respect(ob)
        + "多加努力，做出点样子来，给某些人一点颜色看看。\n");
    command("recruit " + ob->query("id") );
    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "xian");
}
