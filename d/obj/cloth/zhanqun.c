
#include <armor.h>

inherit CROTCH;

void create()
{
    set_name( "虎皮战裙", ({ "zhan qun", "qun" }) );
    set_weight(2000);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "一件虎皮缝制的战裙，虽不精致，但很结实．\n");
        set("unit", "件");
        set("value", 500);
        set("material", "leather");
        set("armor_prop/armor", 6);
    }
    setup();
}

