//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("神话世界",({"star lisa","lisa","star"}));
  set("gender", "男性");
  set("title", "室火星官");
  set("age", 30);

  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 1214162);
  set("kee", 1058);
  set("max_kee", 1058);
  set("sen", 1817);
  set("max_sen", 1817);
  set("force", 4209);
  set("max_force", 2105);
  set("mana", 6665);
  set("max_mana", 3333);
  set("force_factor", 118);
  set("mana_factor", 167);
  set("str", 19);
  set("per", 10);

setup();
carry_object(__DIR__"obj/stick")->wield();
carry_object(__DIR__"obj/armor")->wear();
carry_object(__DIR__"obj/pifeng")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="stick";
  string armor1_id="armor",armor2_id="pifeng";
  ::init();
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"袖里乾坤"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"苍茫云海间"NOR);
}
