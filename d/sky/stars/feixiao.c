//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("明厦",({"star feixiao","feixiao","star"}));
  set("gender", "男性");
  set("title", "柳土星宿");
  set("age", 60);
  set("long", "    \n$n$r\n");

  set("attitude", "heroism");
  set("class", "bonze");
  set("combat_exp", 1236121);
  set("kee", 1141);
  set("max_kee", 1141);
  set("sen", 1660);
  set("max_sen", 1660);
  set("force", 5389);
  set("max_force", 2695);
  set("mana", 6623);
  set("max_mana", 3312);
  set("force_factor", 140);
  set("mana_factor", 166);
  set("str", 18);
  set("per", 10);

setup();
carry_object(__DIR__"obj/spear")->wield();
carry_object(__DIR__"obj/armor")->wear();
carry_object(__DIR__"obj/pifeng")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="spear";
  string armor1_id="armor",armor2_id="pifeng";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name",HIY"碧玉邪妖"NOR);
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"碧玉环"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"碧玉圈"NOR);
}

