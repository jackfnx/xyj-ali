// dengxian-dafa.c 【登仙大法】
inherit SPELLS;

string name() { return "登仙大法"; }

int query_basic_limit() { return 10; }

int valid_enable(string usage) { return usage=="spells"; }

string cast_spell_file(string spell)
{
    return CLASS_D("dapeng") + "/dengxian-dafa/" + spell;
}


