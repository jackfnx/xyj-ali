//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("����",({"star fer","fer","star"}));
  set("gender", "����");
  set("title", "�����ǹ�");
  set("age", 36);

  set("attitude", "heroism");
  set("class", "yaomo");
  set("combat_exp", 2414774);
  set("kee", 1312);
  set("max_kee", 1312);
  set("sen", 2211);
  set("max_sen", 2211);
  set("force", 5859);
  set("max_force", 2930);
  set("mana", 8157);
  set("max_mana", 4079);
  set("force_factor", 142);
  set("mana_factor", 204);
  set("str", 20);
  set("per", 20);

setup();
carry_object("/obj/loginload/linen.c")->wear();
carry_object(__DIR__"obj/blade")->wield();
carry_object(__DIR__"obj/armor")->wear();
carry_object(__DIR__"obj/pifeng")->wear();
}

void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="blade";
  string armor1_id="armor",armor2_id="pifeng";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name",HIY"������"NOR);
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"����Ƥ"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"����Ҷ"NOR);
}

