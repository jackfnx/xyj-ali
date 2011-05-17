// ALi

// foxforce.c  【天狐心法】
inherit FORCE;

string name() { return "天狐心法"; }

int valid_enable(string usage) { return usage=="force"; }

string cast_spell_file(string spell)
{
    return CLASS_D("fox") + "/foxforce/" + spell;
}

