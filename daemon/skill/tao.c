// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// tao
inherit SPELLS;

string name() { return "正宗道法"; }

int query_basic_limit() { return 20; }

int override_basic_level() { return 1; }

int valid_enable(string usage) { return usage=="spells"; }

string cast_spell_file(string spell)
{
    return CLASS_D("puti") + "/tao/" + spell;
}

