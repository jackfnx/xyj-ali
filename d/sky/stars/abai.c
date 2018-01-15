//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("韩柏",({"star abai","abai","star"}));
  set("gender", "男性");
  set("title", "胃土星官");
  set("age", 51);

  set("attitude", "heroism");
  set("class", "yaomo");
  set("combat_exp", 1267587);
  set("kee", 1259);
  set("max_kee", 1259);
  set("sen", 1774);
  set("max_sen", 1774);
  set("force", 5435);
  set("max_force", 2718);
  set("mana", 6245);
  set("max_mana", 3123);
  set("force_factor", 114);
  set("mana_factor", 157);
  set("str", 29);
  set("per", 13);

setup();
carry_object(__DIR__"obj/whip")->wield();
carry_object(__DIR__"obj/armor")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="whip";
  string armor1_id="armor";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name",HIY"皮鞭"NOR);
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"白罗袍"NOR);
}

