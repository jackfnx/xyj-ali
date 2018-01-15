// ALi

// foxphantom.c  【千幻天狐道】
inherit SPELLS;

string name() { return "千幻天狐道"; }

int valid_enable(string usage) { return usage=="force"; }

string cast_spell_file(string spell)
{
    return CLASS_D("fox") + "/foxphantom/" + spell;
}

