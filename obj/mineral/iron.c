// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("九阴玄铁", ({ "jiuyin xuantie", "iron" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "从玄铁中提取的精华材料，具有极大的战略价值，因此实行朝廷专卖。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("value", 100000);
        set("is_mineral", 1);
        set("no_sell", "九阴玄铁是朝廷专卖物资，私人禁止买卖。");
    }

    set_amount(1);
}
