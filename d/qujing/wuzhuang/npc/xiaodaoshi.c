// ALi by NewX

inherit NPC;
void create()
{
   set_name("小道士", ({"xiao daoshi", "daoshi"}));
   //set("title", "");
   set("gender", "男性" );
   set("age", 16);
   set("long", "一个不大的小道士。\n");
   set("class", "xian");
   set("combat_exp", 100);
   set("attitude", "peaceful");

   setup();
   carry_object("/d/obj/cloth/xianpao")->wear();
}
