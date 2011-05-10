// ALI

// fox-force.c  【天狐心法】
inherit FORCE;

string name() { return "天狐心法"; }

int valid_enable(string usage) { return usage=="force"; }

int practice_skill(object me)
{
    return
        notify_fail("天狐心法只能向师父学，或是从运用(exert/cast)中增加熟练度。\n");
}

string cast_spell_file(string spell)
{
    return CLASS_D("gumu") + "/fox-force/" + spell;
}

