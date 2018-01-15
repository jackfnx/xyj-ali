// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit NPC;

void create()
{
    set_name("龙表弟", ({"long biaodi", "long", "biaodi"}));

    set("long","龙少爷的表弟和死党．\n");
    set("gender", "男性");
    set("age", 16);
    set("per", 15);
    set("attitude", "peaceful");
    set("shen_type", 1);
    set_skill("unarmed", 40);
    set_skill("dragonfight", 40);
    set_skill("dodge", 30);
    set_skill("parry", 30);
    set_skill("dragonstep", 30);
    map_skill("dodge", "dragonstep");
    map_skill("unarmed", "dragonfight");
    set("force", 400);
    set("max_force", 400);
    set("force_factor", 5);
    set("combat_exp", 126000);
    setup();
    add_money("gold", 1);
    carry_object("/d/ourhome/obj/choupao")->wear();
}

