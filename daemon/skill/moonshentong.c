// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// moonshentong.c 【太阴仙诀】
inherit SPELLS;

string name() { return "太阴仙诀"; }

int query_basic_limit() { return 10; }

int valid_enable(string usage) { return usage=="spells"; }

string cast_spell_file(string spell)
{
    return CLASS_D("moon") + "/moonshentong/" + spell;
}

