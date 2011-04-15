// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("白金雷魄", ({ "baijin leipo", "gold" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "白金之精与雷电之魄结合的产物。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
        set("elements/gold", 100);
    }

    set_amount(1);
}
