//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("烈火",({"star fire","fire","star"}));
  set("gender", "男性");
  set("title", "翼火星官");
  set("age", 46);
  set("long", "    \n一团熊熊燃烧的烈火\n");

  set("attitude", "heroism");
  set("class", "taoist");
  set("combat_exp", 2182331);
  set("kee", 1151);
  set("max_kee", 1151);
  set("sen", 1706);
  set("max_sen", 1706);
  set("force", 5083);
  set("max_force", 2542);
  set("mana", 5779);
  set("max_mana", 2890);
  set("force_factor", 136);
  set("mana_factor", 145);
  set("str", 19);
  set("per", 18);

setup();
carry_object("/obj/loginload/linen.c")->wear();
carry_object(__DIR__"obj/stick")->wield();
carry_object(__DIR__"obj/armor")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1;
  string weapon_id="stick";
  string armor1_id="armor";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name",HIY"火枝"NOR);
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"火焰甲"NOR);
}

