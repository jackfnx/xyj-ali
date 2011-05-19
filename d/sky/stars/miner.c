//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("魂断兰桥",({"star miner","miner","star"}));
  set("gender", "女性");
  set("title", "平天大圣");
  set("age", 29);

  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 11709356);
  set("kee", 1920);
  set("max_kee", 1920);
  set("sen", 3042);
  set("max_sen", 3042);
  set("force", 11105);
  set("max_force", 5553);
  set("mana", 12633);
  set("max_mana", 6317);
  set("force_factor", 278);
  set("mana_factor", 316);
  set("str", 28);
  set("per", 21);

setup();
carry_object("/obj/loginload/skirt.c")->wear();
carry_object(__DIR__"obj/sword")->wield();
carry_object(__DIR__"obj/ring")->wear();
carry_object(__DIR__"obj/waist")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="sword";
  string armor1_id="ring",armor2_id="waist";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name","断魂剑");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"诱魂腕镯"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"护魂束腰"NOR);
}

