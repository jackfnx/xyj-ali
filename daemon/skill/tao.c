// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// tao
inherit SKILL;

string name() { return "正宗道法"; }

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("spells", 1) < 20)
        return notify_fail("道可道，非常道，你的法术修为还不够高深。\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("puti") + "/tao/" + spell;
}

