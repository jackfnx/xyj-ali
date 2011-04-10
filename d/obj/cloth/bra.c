
#include <armor.h>

inherit CHEST;

void create()
{
    set_name( "胸罩", ({ "bra" }) );
    set_weight(1000);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "一副很性感的胸罩，堪堪只能覆盖住乳晕．\n");
        set("unit", "副");
        set("value", 800);
        set("material", "cloth");
        set("armor_prop/armor", 1);
        set("armor_prop/personality", 2);
        set("female_only", 1);
    }
    setup();
}

