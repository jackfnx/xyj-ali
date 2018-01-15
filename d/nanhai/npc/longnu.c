
// longnu.c 龙女

inherit NPC;

void create()
{
    set_name("龙女", ({ "longnu" }));
    set("title", "南海观音侍从");   
    set("long", @LONG
南海观音座前龙女。
LONG);
    set("gender", "女性");
    set("age", 18);
    set("per", 25);
    set("attitude", "friendly");
    set("max_kee", 300);
    set("max_gin", 300);
    set("max_sen", 350);
    set("force", 200);
    set("max_force", 200);
    set("force_factor", 10);
    set("max_mana", 350);
    set("mana", 350);
    set("mana_factor", 20);
    set("combat_exp", 100000);

    set("eff_dx", 40000);
    set("nkgain", 200);

    set_skill("literate", 80);
    set_skill("spells", 70);
    set_skill("seashentong", 70);
    set_skill("unarmed", 60);
    set_skill("dragonfight", 55);
    set_skill("dodge", 70);
    set_skill("dragonstep", 70);
    set_skill("parry", 80);
    set_skill("force", 70);
    set_skill("dragonforce", 60);
    map_skill("spells", "seashentong");
    map_skill("unarmed", "dragonfight");
    map_skill("dodge", "dragonstep");
    map_skill("force", "dragonforce");
//   set("chat_chance_combat", 80);
//   set("chat_msg_combat", ({
//     (: cast_spell, "thunder" :),
//   }) );

    setup();
//   carry_object("/obj/money/thousand-cash");
    carry_object("/obj/money/gold");
    carry_object("/obj/money/gold");
    carry_object("/obj/money/gold");
    carry_object("/obj/money/gold");
    carry_object("/obj/money/gold");
    carry_object("/obj/loginload/skirt")->wear();
    carry_object("/obj/loginload/shoes")->wear();
}

