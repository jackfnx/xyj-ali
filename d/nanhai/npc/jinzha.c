
// jinzha.c 金吒

inherit NPC;

void create()
{
    set_name("金吒", ({ "jinzha" }));
    set("title", "文殊首徒");   
    set("long", @LONG
李天王大公子金吒，乃文殊菩萨首徒，来普陀山支援自己的弟弟。
LONG);
    set("gender", "男性");
    set("age", 25);
    set("attitude", "peaceful");
    set("rank_info/self", "贫僧");
    set("class", "bonze");
    set("max_kee", 850);
    set("max_gin", 800);
    set("max_sen", 850);
    set("force", 400);
    set("max_force", 500);
    set("force_factor", 50);
    set("max_mana", 250);
    set("mana", 300);
    set("mana_factor", 20);
    set("combat_exp", 40000);

    set("eff_dx", 150000);
    set("nkgain", 300);

    set_skill("literate", 100);
    set_skill("spells", 80);
    set_skill("buddhism", 80);
    set_skill("unarmed", 70);
    set_skill("jienan-zhi", 70);
    set_skill("dodge", 70);
    set_skill("lotusstep", 70);
    set_skill("parry", 80);
    set_skill("force", 80);
    set_skill("lotusforce", 80);
    set_skill("staff", 90);
    set_skill("lunhui-zhang", 90);
    map_skill("spells", "buddhism");
    map_skill("unarmed", "jienan-zhi");
    map_skill("dodge", "lotusstep");
    map_skill("force", "lotusforce");
    map_skill("parry", "lunhui-zhang");
    map_skill("staff", "lunhui-zhang");
    
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: cast_spell, "bighammer" :),
        (: cast_spell, "jingang" :)
    }) );
    
    create_family("南海普陀山", 2, "弟子");

    setup();
//    carry_object("/obj/money/thousand-cash");
    carry_object("/obj/money/gold");
    carry_object("/d/nanhai/obj/sengpao")->wear();
    carry_object("/d/nanhai/obj/budd_staff")->wield();
}

void attempt_apprentice(object ob)
{
   if (!((string)ob->query("bonze/class") =="bonze" )) {
     command("say " + RANK_D->query_respect(ob) + "未入佛门，恕贫僧不能接纳。\n");
     return;
   }
   if (((int)ob->query_skill("buddhism", 1) < 50 )) {
     command("say " + RANK_D->query_respect(ob) + "若欲深修，需得熟读佛法。\n");
     return;
   }
   command("nod");
   command("say 很好，贫僧就收下你，希望你多加努力，早成正果。\n");

   command("recruit " + ob->query("id") );
   return;   
}
