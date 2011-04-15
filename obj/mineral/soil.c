// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("戊土之灵", ({ "wutu zhiling", "soil" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "土行元素的精华，生发一切的土壤。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
        set("elements/soil", 100);
    }

    set_amount(1);
}
