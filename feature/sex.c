// ALI by NewX

// sex.c

#include <ansi.h>
#include <dbase.h>
#include <origin.h>
#include <skill.h>

int update_sex_status()
{
    mapping my;
    string dodge, force, spells;
    int sex_per, update_flag, sex_affair;

    update_flag = 0;

    my = query_entire_dbase();

    if (!mapp(my)) return 0;

    if (my["want"] > 0 && my["want"] > my["eff_want"]) {
        my["want"] -= 1; update_flag++;
    }
    if (my["enjoy"] > 0) { my["enjoy"] -= 1; update_flag++; }

    sex_per = my["per"] + query_temp("apply/personality");

    dodge = query_skill_mapped("dodge");
    force = query_skill_mapped("force");
    spells = query_skill_mapped("spells");
    sex_affair = 0;
    if (dodge) {
        sex_affair += SKILL_D(dodge)->query_sex_affair();
        if (sex_affair == 0)
            ;
        else if (sex_affair < 0) {
            my["want"] += sex_affair;
            update_flag++;
        }
        else if (sex_affair > 0) {
            sex_per += sex_affair;
        }
    }
    if (force) {
        sex_affair += SKILL_D(force)->query_sex_affair();
        if (sex_affair == 0)
            ;
        else if (sex_affair < 0) {
            my["want"] += sex_affair;
            update_flag++;
        }
        else if (sex_affair > 0) {
            sex_per += sex_affair;
        }
    }
    if (spells) {
        sex_affair += SKILL_D(spells)->query_sex_affair();
         if (sex_affair == 0)
            ;
        else if (sex_affair < 0) {
            my["want"] += sex_affair;
            update_flag++;
        }
        else if (sex_affair > 0) {
            sex_per += sex_affair;
        }
    }

    sex_per += query_temp("apply/sex_personality");

    if (sex_affair > 0)
    {
        object env = environment();
        if (environment()) {
            object ob = first_inventory(environment());
            while (ob) {
                if (living(ob)) {
                    ob->add("want", sex_per);
                    update_flag++;
                }
                ob = next_inventory(ob);
            }
        }
    }

    return update_flag;
}

