// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// yaofa
inherit SPELLS;

string name() { return "妖法"; }

int is_exclusive() { return 1; }

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
        if( 2*(int)me->query_skill("spells") <= (int)me->query_skill("yaofa") )
        return notify_fail("你的法术修为还不够高深，无法学习「妖法」。\n");
        return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("yushu") + "/yaofa/"+spell;
}


