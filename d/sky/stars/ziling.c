//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("����",({"star ziling","ziling","star"}));
  set("gender", "����");
  set("title", "��ľ�ǹ�");
  set("age", 51);

  set("attitude", "heroism");
  set("class", "bonze");
  set("combat_exp", 1524566);
  set("kee", 1204);
  set("max_kee", 1204);
  set("sen", 2149);
  set("max_sen", 2149);
  set("force", 5761);
  set("max_force", 2881);
  set("mana", 8439);
  set("max_mana", 4220);
  set("force_factor", 142);
  set("mana_factor", 212);
  set("str", 23);
  set("per", 28);
  set("inquiry", ([
      "name" : "�����׼����������꣬���ŷ��졣",
]));

setup();
carry_object("/obj/loginload/linen.c")->wear();
carry_object(__DIR__"obj/staff")->wield();
carry_object(__DIR__"obj/waist")->wear();
carry_object(__DIR__"obj/shoes")->wear();
}
void init()
{
  object me=this_object();
  object my_weapon,my_armor1,my_armor2;
  string weapon_id="staff";
  string armor1_id="shoes",armor2_id="waist";
  ::init();
  if (my_weapon=present(weapon_id, me))
       my_weapon->set("name",HIY"����Ĵ��ȹ�"NOR);
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"����Ľ��ƹ�"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"����Ѫ����"NOR);
}

