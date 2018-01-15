// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("离火之精", ({ "lihuo zhijing", "fire" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "南明离火的精华，焚化一切的火焰。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
        set("elements/fire", 100);
    }

    set_amount(1);
}
