// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// zhuban.c

#include <weapon.h>

inherit SWORD;

void create()
{
   set_name("竹板", ({ "zhu ban","ban" }) );
   set_weight(1000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "副");
     set("value", 200);
     set("material", "bamboo");
     set("long", "一副说唱艺人用的竹板。\n");
     set("wield_msg", "$N拿出一幅竹板，拍了几下，节奏感十足。\n");
     set("unwield_msg", "$N将$n收了起来。\n");
   }
   init_sword(10);
   setup();
}
