// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// buddhism.c

inherit SPELLS;

string name() { return "大乘佛法"; }

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if ((int)me->query("bellicosity") > 100)
        return notify_fail("你的杀气太重，无法修炼大乘佛法。\n");
    return ::valid_learn(me);
}

string cast_spell_file(string spell)
{
    return CLASS_D("bonze") + "/buddhism/" + spell;
}

