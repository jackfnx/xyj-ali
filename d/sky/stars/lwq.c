//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("灵",({"star lwq","lwq","star"}));
  set("gender", "男性");
  set("title", "毕月星官");
  set("age", 65);
  set("long", "    \n$N和$n\n");

  set("attitude", "heroism");
  set("class", "taoist");
  set("combat_exp", 1006693);
  set("kee", 1152);
  set("max_kee", 1152);
  set("sen", 1695);
  set("max_sen", 1695);
  set("force", 5599);
  set("max_force", 2800);
  set("mana", 6759);
  set("max_mana", 3380);
  set("force_factor", 140);
  set("mana_factor", 170);
  set("str", 15);
  set("per", 25);

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
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name","刀剑");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name","刀");
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name","剑");
}

