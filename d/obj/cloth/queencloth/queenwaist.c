// ALI by NewX

#include <armor.h>

inherit WAIST;

void create()
{
    set_name( "女王胸衣", ({ "queen waist", "waist" }) );
    set_weight(2000);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("long", @LONG
一件漆黑发亮的皮衣，材料华丽，做工考究。
胸前的一对乳甲堪堪可以覆盖住乳房，下身的一片胯甲堪堪可以覆盖住私处。
暴露，性感，散发着SM女王的暴虐气息。
LONG);
        set("unit", "件");
        set("value", 400);
        set("material", "leather");
        set("armor_prop/armor", 10);
        set("armor_prop/dodge", 10);
        set("armor_prop/personality", 5);
//        set("wear_msg", "$N取出了一件性感的皮衣穿上，顿时化身成为一个性感的SM女王。\n");
        set("female_only", 1);
    }

    setup();
}

