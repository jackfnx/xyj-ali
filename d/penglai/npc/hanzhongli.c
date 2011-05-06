// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// hanzhongli.c...weiqi, 98.02.24.

inherit NPC;
void create()
{
    set_name("汉钟离", ({"han zhongli", "han", "zhongli"}));
    //set("title", "");
    set("nickname", "八仙之一");
    set("gender", "男性" );
    set("age", 50);
    set("per", 20);
    set("long", "一位大腹便便的胖老头。大概总是觉得太热，时不时地要扇几扇。\n");
    set("class", "xian");
    set("combat_exp", 120000);
    set("attitude", "peaceful");
    set_skill("unarmed", 60);
    set_skill("wuxing-quan", 60);
    set_skill("dodge", 80);
    set_skill("bagua-zhen", 70);
    set_skill("parry", 80);
    set_skill("sword", 90);
    set_skill("xiaofeng-sword", 100);
    set_skill("force", 70);   
    set_skill("zhenyuan-force", 70);
    set_skill("literate", 80);
    set_skill("spells", 80);
    set_skill("taiyi", 80);
    map_skill("spells", "taiyi");
    map_skill("force", "zhenyuan-force");
    map_skill("unarmed", "wuxing-quan");
    map_skill("sword", "xiaofeng-sword");
    map_skill("dodge", "bagua-zhen");
    
    set("max_kee", 500);
    set("max_sen", 500);
    set("force", 1000);
    set("max_force", 800);
    set("mana", 1600);
    set("max_mana", 800);   
    set("force_factor", 40);
    set("mana_factor", 40);
    
    setup();
    carry_object("/d/obj/cloth/xianpao")->wear();
    carry_object("/d/obj/weapon/sword/bajiaoshan")->wield();
}
