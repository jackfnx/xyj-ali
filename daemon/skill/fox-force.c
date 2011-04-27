// ALI

// fox-force.c  【天狐心法】
inherit FORCE;

string name() { return "天狐心法"; }

int valid_enable(string usage) { return usage=="force" || usage=="spells" || usage=="magic"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("spells") <= (int)me->query_skill("fox-dao"))
        return notify_fail("你的法术修为还不够高深，无法学习天狐道。\n");
    return 1;
}

int practice_skill(object me)
{
    return
        notify_fail("天狐心法只能向师父学，或是从运用(exert/cast)中增加熟练度。\n");
}

string exert_function_file(string func)
{
    return CLASS_D("gumu") + "/fox-force/" + func;
}

string cast_spell_file(string spell)
{
    return CLASS_D("gumu") + "/fox-force/" + spell;
}

