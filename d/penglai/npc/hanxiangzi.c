// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// hanxiangzi.c...weiqi, 98.02.24.

inherit NPC;
void create()
{
    set_name("韩湘子", ({"han xiangzi", "han", "xiangzi"}));
    //set("title", "");
    set("nickname", "八仙之一");
    set("gender", "男性" );
    set("age", 22);
    set("per", 30);
    set("long", "好一位俊雅潇洒的相公。\n");
    set("class", "xian");
    set("combat_exp", 120000);
    set("attitude", "peaceful");
    set_skill("unarmed", 60);
    set_skill("wuxing-quan", 60);
    set_skill("dodge", 80);
    set_skill("bagua-array", 80);
    set_skill("parry", 80);
    set_skill("sword", 90);
    set_skill("xiaofeng-sword", 100);
    set_skill("force", 70);   
    set_skill("zhenyuan-force", 70);
    set_skill("literate", 120);
    set_skill("spells", 80);
    set_skill("taiyi", 80);
    map_skill("spells", "taiyi");
    map_skill("force", "zhenyuan-force");
    map_skill("unarmed", "wuxing-quan");
    map_skill("sword", "xiaofeng-sword");
    map_skill("dodge", "bagua-array");
    
    set("max_kee", 500);
    set("max_sen", 500);
    set("force", 1000);
    set("max_force", 800);
    set("mana", 1600);
    set("max_mana", 800);   
    set("force_factor", 40);
    set("mana_factor", 40);
    
    setup();
    carry_object("/d/obj/cloth/choupao")->wear();
    carry_object("/d/obj/weapon/sword/yudi")->wield();
}
