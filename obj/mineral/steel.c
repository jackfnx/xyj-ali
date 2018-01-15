// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("六阳钨钢", ({ "liuyang wugang", "steel" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "从钨钢中提取的精华材料，具有极大的战略价值，因此实行朝廷专卖。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
        set("value", 100000);
        set("no_sell", "六阳钨钢是朝廷专卖物资，私人禁止买卖。");
    }

    set_amount(1);
}
