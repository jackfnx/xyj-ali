// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("坎水之精", ({ "kanshui zhijing", "water" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "北冥坎水的精华，消溶一切的至阴至寒之水。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
        set("elements/water", 100);
    }

    set_amount(1);
}
