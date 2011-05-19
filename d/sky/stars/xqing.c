//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("小青",({"star xqing","xqing","star"}));
  set("gender", "女性");
  set("title", "齐天大圣");
  set("age", 39);

  set("attitude", "heroism");
  set("class", "taoist");
  set("combat_exp", 5104540);
  set("kee", 1295);
  set("max_kee", 1295);
  set("sen", 2976);
  set("max_sen", 2976);
  set("force", 5853);
  set("max_force", 2927);
  set("mana", 12061);
  set("max_mana", 6031);
  set("force_factor", 164);
  set("mana_factor", 302);
  set("str", 16);
  set("per", 14);

setup();
carry_object("/obj/loginload/skirt.c")->wear();
carry_object(__DIR__"obj/stick")->wield();
carry_object(__DIR__"obj/armor")->wear();
carry_object(__DIR__"obj/shoes")->wear();
}
void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="stick";
  string armor1_id="shoes",armor2_id="armor";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name","绣花针");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name","绣鞋");
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name","绣裙");
}

