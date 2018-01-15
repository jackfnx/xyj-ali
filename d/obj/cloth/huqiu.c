// ALi by NewX

// huqiu.c 千狐裘

#include <armor.h>

inherit CLOTH;

void create()
{
   set_name("千狐裘", ({ "huqiu", "cloth" }) );
   set_weight(1000);
   if (clonep())
       set_default_object(__FILE__);
   else {
       set("long", "一条雪白的狐裘外袍，质地极柔。传说集腋成裘，上等的狐裘只能取自通灵雌狐的腋下，这样一条狐裘不知要收集多少灵狐的狐裘。\n");
       set("unit", "条");
       set("value", 8000);
       set("material", "cloth");
       set("armor_prop/armor", 1);
       set("armor_prop/personality", 5);
       set("female_only", 1);
   }
   setup();
}

