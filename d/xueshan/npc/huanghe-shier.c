// ALi by NewX

inherit NPC;

void create()
{
    set_name("黄鹤侍儿", ({"huanghe shier", "shier", "huanghe"}));
    set("gender", "女性" );
    set("age", 22);

    set("long", "孔雀公主的贴身侍卫头领。\n");
    set("class", "avian");
    set("combat_exp", 35000);
    set("daoxing", 35000);

    set("attitude", "heroism");
    create_family("大雪山", 3, "弟子");
    set_skill("unarmed", 40);
    set_skill("raptor-talon", 50);
    set_skill("pressheart-hand", 50);
    set_skill("dodge", 60);
    set_skill("peripateticism", 60);
    set_skill("parry", 60);
    set_skill("sword", 60);
    set_skill("avian-sword", 60);
    set_skill("throwing", 80);
    set_skill("force", 61);
    set_skill("iceblood-force", 60);
    set_skill("literate", 80);
    set_skill("spells", 70);
    set_skill("dengxian-dafa", 60);
    map_skill("spells", "dengxian-dafa");
    map_skill("force", "iceblood-force");
    map_skill("unarmed", "raptor-talon");
    map_skill("sword", "avian-sword");
    map_skill("parry", "avian-sword");

    set("max_kee", 300);
    set("max_sen", 300);
    set("force", 300);
    set("max_force", 300);
    set("mana", 300);
    set("max_mana", 300);
    set("force_factor", 15);
    set("mana_factor", 15);

    set("inquiry", ([
        "here" : "这就是大雪山啦！\n",
    ]) );

    setup();

    carry_object("/d/obj/cloth/xueshan-pao")->wear();
    carry_object("/d/obj/armor/tenjia")->wear();
    carry_object("/d/obj/weapon/sword/peijian")->wield();
}

void attempt_apprentice(object ob)
{
    if ((string)ob->query("gender") != "女性") {
        command("shake");
        command("say 公主的侍卫队只收女孩子。");
        command("say " + RANK_D->query_respect(ob) + "一个大男人，恐怕不太方便服侍公主吧。");
    } else if ((string)ob->query("family/family_name") == "大雪山") {
        if ((int)ob->query("family/generation") < 3)
            command("say 不敢，不敢。我该拜" + RANK_D->query_respect(ob) + "您为师才是。\n");
        else if ((int)ob->query("family/generation") == 3)
            command("say 你这个" + RANK_D->query_rude(ob) + "别来消遣本姑娘了！\n");
        else {
            command("ok");
            command("say " + RANK_D->query_respect(ob) + "投入我的门下，可要听话，不听师傅的话，有你的好看！\n");
            command("recruit " + ob->query("id") );
        }
    } else {
        command(":D ");
        command("say 好，"+ RANK_D->query_respect(ob) +"，你到我大雪山，从巡山的开始当起，早晚定能出人头第！\n");
        command("recruit " + ob->query("id") );
    }

    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob)) {
        ob->set("class", "avian");
        ob->set("title", "大雪山孔雀公主贴身侍卫");
    }
}
