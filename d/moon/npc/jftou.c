// ALi by NewX

// jftou.c 轿夫头
#include <ansi.h>

inherit NPC;

void create()
{
   set_name("轿夫头", ({ "jiaofu tou", "tou" }));
   set("long", "他是轿夫头，除了抬花轿外，他负责办理雇佣手续。\n"
     "他看起来精明强干，有点生意头脑的样子，力气也不小。\n");
   set("gender", "男性");
   set("age", 30);
   set("attitude", "peaceful");
   set("str", 80);
   set("int", 10);
   set("max_kee", 600);
   set("combat_exp", 10000);
   set_skill("force", 30);
   set_skill("dodge", 30);
   set_skill("unarmed", 30);
   set_skill("parry", 30);
   setup();
}
