//created by vikee
//2000.10

inherit NPC;
#include "huoyannpc.h"

void create()
{
    set_name("灵官",({"ling guan", "guan", "xian",}));
    set("long", "佑圣真君手下的灵官，骁勇无比。.\n");
    set("per", 23);
    set("str", 30);
    set_skill("force", 100);
    set_skill("dodge", 100);
    set_skill("bagua-zhen", 140);
    set_skill("parry", 140);
    set_skill("spells", 100);
    set_skill("whip", 200);
    set_skill("hellfire-whip", 200);
    map_skill("whip", "hellfire-whip");
    map_skill("parry", "wuxing-quan");
    set("max_force", 1600);
    set("max_mana", 2000);
    set("mana", 2000);
    set("force", 1600);
    set("mana_factor", 80);
    set("force_factor", 70);
    set("max_kee", 1600);
    set("max_sen", 2000);
    set("combat_exp", 800000);
    setup();

   carry_object("/d/obj/weapon/whip/whip")->wield();
   carry_object("/d/obj/cloth/jinpao")->wear();
}

