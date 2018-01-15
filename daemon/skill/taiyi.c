// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// taiyi.c 【太乙仙法】
inherit SPELLS;

string name() { return "太乙仙法"; }

int query_basic_limit() { return 10; }

int valid_enable(string usage) { return usage=="spells"; }

string cast_spell_file(string spell)
{
    return CLASS_D("daxian") + "/taiyi/" + spell;
}
