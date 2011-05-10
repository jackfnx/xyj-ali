// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// yaofa
inherit SPELLS;

string name() { return "妖法"; }

int is_exclusive() { return 1; }

int valid_enable(string usage) { return usage=="spells"; }

string cast_spell_file(string spell)
{
        return CLASS_D("yushu") + "/yaofa/"+spell;
}


