// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// created 12/18/1997 by snowcat

inherit NPC;

void create()
{
  set_name("精细鬼", ({ "jingxi gui", "jingxi gui", "gui" }));
  set("gender", "男性");
  set("age", 24);
  set("attitude", "heroism");
  set("per", 30);
  set("max_kee", 500);
  set("max_gin", 500);
  set("max_sen", 500);
  set("force", 500);
  set("max_force", 500);
  set("force_factor", 20);
  set("max_mana", 500);
  set("mana", 500);
  set("mana_factor", 20);
  set("combat_exp", 400000);
  set_skill("spells", 40);
  set_skill("taoism", 40);
  set_skill("unarmed", 40);
  set_skill("puti-zhi", 40);
  set_skill("dodge", 40);
  set_skill("cloud-steps", 40);
  set_skill("parry", 40);
  set_skill("force", 40);
  set_skill("azoth", 40);
  map_skill("spells", "taoism");
  map_skill("unarmed", "puti-zhi");
  map_skill("dodge", "cloud-steps");
  map_skill("force", "azoth");
  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
}

