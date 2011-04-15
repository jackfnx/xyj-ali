// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("青木风魂", ({ "qingmu fenghun", "wood" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "青木精华与清风之魂结合的产物。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
        set("elements/wood", 100);
    }

    set_amount(1);
}
