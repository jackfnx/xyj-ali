// xunshi.c

inherit NPC;
void create()
{
    set_name("冰谷巡使", ({"xunshi", "shi"}));
    set("gender", "男性" );
    set("age", 33);
    set("long", "这位巡使来自遥远的大雪山。他身披白袍，腰跨弯刀。\n"
        "白袍当胸绣着一只飞扬欲脱的大鹏鸟。弯刀看起来晶莹透明，好像是以寒冰制成。\n");
    set("class", "yaomo");
    set("combat_exp", 50000);
    set("attitude", "peaceful");
    create_family("大雪山", 4, "弟子");
    set_skill("unarmed", 40);
    set_skill("raptor-talon", 40);
    set_skill("dodge", 40);
    set_skill("parry", 40);
    set_skill("blade", 40);
    set_skill("ice-blade", 50);
    set_skill("peripateticism", 50);
    set_skill("spells", 40);
    set_skill("dengxian-dafa", 40);
    set_skill("force", 40);   
    set_skill("iceblood-force", 40);
    map_skill("spells", "dengxian-dafa");
    map_skill("force", "iceblood-force");
    map_skill("blade", "ice-blade");
    map_skill("dodge", "peripateticism");
    map_skill("unarmed", "raptor-talon");

    set("per", 19);
    set("max_kee", 400);
    set("max_sen", 400);
    set("force", 350);
    set("max_force", 300);
    set("mana", 400);
    set("max_mana", 350);
    set("force_factor", 30);
    set("mana_factor", 17);

    set("eff_dx", -15000);
    set("nkgain", 80);

    setup();
    carry_object("/d/obj/cloth/xueshan-pao")->wear();
    carry_object("/d/obj/weapon/blade/iceblade")->wield();
}

