// ALi by NewX

// lgshou.c 锣鼓手

#include <ansi.h>
inherit NPC;

void create()
{
   set_name("锣鼓手", ({ "luogu shou", "shou" }));
   set("long", "他就是婚礼上奏礼乐的吹鼓手。\n"
     "他胸前挂着一个大鼓，双手各拿一个鼓槌，起劲地敲打着。\n");
   set("gender", "男性");
   set("age", 30);
   set("attitude", "peaceful");
   set("str", 50);
   set("int", 10);
   set("max_kee", 500);
   set("combat_exp", 10000);
   set_skill("force", 30);
   set_skill("dodge", 30);
   set_skill("unarmed", 30);
   set_skill("parry", 30);
   setup();
}
