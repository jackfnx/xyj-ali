//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("瓜瓜",({"star ggggg","ggggg","star"}));
  set("gender", "女性");
  set("title", "移山大圣");
  set("age", 29);

  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 5787884);
  set("kee", 1304);
  set("max_kee", 1304);
  set("sen", 3056);
  set("max_sen", 3056);
  set("force", 6819);
  set("max_force", 3410);
  set("mana", 12767);
  set("max_mana", 6384);
  set("force_factor", 161);
  set("mana_factor", 320);
  set("str", 14);
  set("per", 26);

setup();
carry_object("/obj/loginload/skirt.c")->wear();
carry_object("/obj/loginload/shoes.c")->wear();
carry_object(__DIR__"obj/sword")->wield();
carry_object(__DIR__"obj/armor")->wear();
carry_object(__DIR__"obj/pifeng")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="sword";
  string armor1_id="armor",armor2_id="pifeng";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name",GRN"碧海");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIG"绿洲"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIW"苍原"NOR);
}

