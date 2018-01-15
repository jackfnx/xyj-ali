//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("文十五",({"star beng","beng","star"}));
  set("gender", "男性");
  set("title", "壁水星官");
  set("age", 39);

  set("attitude", "heroism");
  set("class", "taoist");
  set("combat_exp", 1579579);
  set("kee", 1133);
  set("max_kee", 1133);
  set("sen", 1674);
  set("max_sen", 1674);
  set("force", 4617);
  set("max_force", 2309);
  set("mana", 5793);
  set("max_mana", 2897);
  set("force_factor", 162);
  set("mana_factor", 145);
  set("str", 23);
  set("per", 14);

setup();
carry_object("/obj/loginload/linen.c")->wear();
carry_object("/d/obj/weapon/standard/stick")->wield();
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
       my_weapon->set("name","木棒");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"布衣"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"披风"NOR);
}

