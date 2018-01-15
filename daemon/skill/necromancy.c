// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// 勾魂术

inherit SPELLS;

string name() { return "勾魂术"; }

int query_basic_limit() { return 10; }

int valid_enable(string usage) { return usage=="spells"; }

string cast_spell_file(string spell)
{
    return CLASS_D("ghost") + "/necromancy/" + spell;
}
