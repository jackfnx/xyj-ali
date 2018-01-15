// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// baguazhou
inherit SPELLS;

string name() { return "八卦咒"; }

int query_basic_limit() { return 10; }

int valid_enable(string usage) { return usage=="spells"; }

string scribe_spell_file(string spell)
{
    return CLASS_D("fighter") + "/baguazhou/" + spell;
}
