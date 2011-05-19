//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("小道童",({"star kuer","kuer","star"}));
  set("gender", "男性");
  set("title", "混天大圣");
  set("age", 25);

  set("attitude", "heroism");
  set("class", "taoist");
  set("combat_exp", 10489138);
  set("kee", 1341);
  set("max_kee", 1341);
  set("sen", 3616);
  set("max_sen", 3616);
  set("force", 6471);
  set("max_force", 3236);
  set("mana", 15259);
  set("max_mana", 7630);
  set("force_factor", 162);
  set("mana_factor", 382);
  set("str", 28);
  set("per", 15);

setup();
carry_object("/obj/loginload/linen.c")->wear();
carry_object(__DIR__"obj/stick")->wield();
carry_object(__DIR__"obj/armor")->wear();
carry_object(__DIR__"obj/ring")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="stick";
  string armor1_id="armor",armor2_id="ring";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name","木棒");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"布衣"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"戒指"NOR);
}

