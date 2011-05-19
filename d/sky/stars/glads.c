//sgzl

inherit NPC;
#include <ansi.h>

void create()
{
  set_name("ÀÖ¹þ¹þ",({"star glads","glads","star"}));
  set("gender", "ÄÐÐÔ");
  set("title", "ÐÇÈÕÐÇ¹Ù");
  set("age", 44);

  set("attitude", "heroism");
  set("class", "fighter");
  set("combat_exp", 8034443);
  set("kee", 1219);
  set("max_kee", 1219);
  set("sen", 2530);
  set("max_sen", 2530);
  set("force", 6139);
  set("max_force", 3070);
  set("mana", 10413);
  set("max_mana", 5207);
  set("force_factor", 141);
  set("mana_factor", 261);
  set("str", 24);
  set("per", 24);

setup();
carry_object("/obj/loginload/linen.c")->wear();
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
       my_weapon->set("name","¾µÍÈ");
  if (my_armor1=present(armor1_id, me))
       my_armor1->set("name",HIY"¹þ¹þ¾µ"NOR);
  if (my_armor2=present(armor2_id, me))
       my_armor2->set("name",HIY"¾µ¼Ü"NOR);
}

