// sgzl

inherit NPC;

string *names = ({
  "»ÆÝºÊÌ¶ù",
  "»Æð¿ÊÌ¶ù",
  "»ÆÈ¸ÊÌ¶ù",
});

void create()
{
    set_name(names[random(sizeof(names))], ({"shi er", "shier"}));
    set("gender", "Å®ÐÔ");
    set("title", "ÊÌÎÀ");
    set("age", 16);
    set("long", "¿×È¸¹«Ö÷ÃÅÏÂÊÌÎÀ¡£\n");
    set("class", "avian");
    set("combat_exp", 25000);

    set("attitude", "peaceful");
    create_family("´óÑ©É½", 4, "µÜ×Ó");
    set_skill("unarmed", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    set_skill("sword", 20);
    set_skill("avian-sword", 10);
    set_skill("peripateticism", 20);
    set_skill("force", 20);   
    set_skill("ice-force", 20);
    map_skill("force", "ice-force");
    map_skill("sword", "avian-sword");
    map_skill("dodge", "peripateticism");

    set("per", 21);
    set("max_kee", 300);
    set("max_sen", 300);
    set("force", 300);
    set("max_force", 120);
    set("force_factor", 2);
    setup();

    set("nkgain", 20);

    carry_object("/d/obj/cloth/skirt")->wear();
    carry_object("/d/obj/cloth/shoes")->wear();
    carry_object("/d/obj/weapon/sword/peijian")->wield();
    carry_object("/d/obj/weapon/throwing/yinzhen");

    setup();
}
