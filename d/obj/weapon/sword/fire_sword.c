// ALi by NewX

#include <weapon.h>

inherit SWORD;

void create()
{
    set_name("烈焰飞腾剑", ({ "firesword", "huo jian", "sword" }));
    set_weight(400);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "把");
        set("value", 700);
        set("material", "steel");
        set("long", "这是一把红色的长剑，红得似火，也似血。\n");
        set("wield_msg", "$N抽出一把火红的长剑，握在手中。\n");
        set("unequip_msg", "$N放下手中的$n。\n");
        set("weapon_prop/courage", 4);
    }
    init_sword(40);
    setup();
}

