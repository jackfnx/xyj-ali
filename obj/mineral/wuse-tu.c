// ALI by NewX

inherit COMBINED_ITEM;

void create()
{
    set_name("五色土", ({ "wuse tu", "mud" }));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "女娲娘娘补天时炼制的五色神石，经过漫长的岁月风化成了这种五色土。\n");
        set("unit", "团");
        set("base_unit", "份");
        set("base_weight", 1);
        set("is_mineral", 1);
    }

    set_amount(1);
}
