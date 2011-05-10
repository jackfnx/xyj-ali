// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// yaofa
inherit SPELLS;

string name() { return "妖法"; }

int is_exclusive() { return 1; }

int valid_enable(string usage) { return usage=="spells"; }

int practice_skill(object me)
{
    object env = environment(me);
    if (!env
    ||  !env->query("lianxi_yaofa")
    ||  (int)me->query_temp("mark/无底洞天魔台climbed") != 1)
        return notify_fail("只有身在天魔台上才可以修炼妖法。\n");
    env->practice_yaofa(me);
    return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("yushu") + "/yaofa/"+spell;
}


