// ALi by NewX

// snshou.c 唢呐手

#include <ansi.h>
inherit NPC;

void create()
{
   set_name("唢呐手", ({ "suona shou", "shou" }));
   set("long", "他就是婚礼上奏礼乐的吹鼓手。\n"
     "他手中拿着一只唢呐，正鼓足力气沉醉地吹着。\n");
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
