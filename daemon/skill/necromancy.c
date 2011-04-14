// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// 死灵术

inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("spells", 1) < 10
    ||  (int)me->query_skill("spells", 1) <= (int)me->query_skill("necromancy", 1) )
        return notify_fail("你的法术修为还不够高深，无法学习死灵术．\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("ghost") + "/necromancy/" + spell;
}

int help(object me)
{
    write(@HELP
【勾魂术】
鬼乃阴神，有灵有能。鬼即魂，所以能『摄魂』。

小鬼勾魂：cast gouhun
幽冥升天：cast miwu
HELP);
    return 1;
}