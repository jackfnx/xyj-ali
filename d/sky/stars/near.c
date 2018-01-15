//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("九流人",({"star near","near","star"}));
  set("gender", "男性");
  set("title", "觜火星官");
  set("age", 54);
  set("long", "    \n小道士(Xiao dao)\n");

  set("attitude", "heroism");
  set("class", "taoist");
  set("combat_exp", 1492484);
  set("kee", 1179);
  set("max_kee", 1179);
  set("sen", 1690);
  set("max_sen", 1690);
  set("force", 4793);
  set("max_force", 2397);
  set("mana", 6143);
  set("max_mana", 3072);
  set("force_factor", 140);
  set("mana_factor", 154);
  set("str", 15);
  set("per", 14);

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
       my_weapon->set("name",HIY"桂树枝"NOR);
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"粗布衣"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"太极道袍"NOR);
}

