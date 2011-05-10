// spells.c

inherit SKILL;

int valid_learn(object me)
{
    mapping skills;
    object skill;
    string *names, name;
    int i, basic_level, limit_level;
    
    basic_level = me->query_skill("spells", 1);
    limit_level = this_object()->query_basic_limit();
    if (basic_level < limit_level)
        return notify_fail("你的法术修为还不够高深，无法学习「" + this_object()->name() + "」。\n");

    if (mapp(skills = me->query_skills())) {
        names = keys(skills);
        for (i = 0; i < sizeof(names); i++) {
            name = names[i];
            if (!skill = find_object(SKILL_D(name)))
                skill = load_object(SKILL_D(name));
            skill = find_object(SKILL_D(name));
            if (skill == this_object()) {
                if (!this_object()->override_basic_level() && skills[name] <= basic_level)
                    return notify_fail("你的法术修为还不够高深，无法学习「" + this_object()->name() + "」1。\n");
            }
            else if (skill->valid_enable("spells")) {
                if (this_object()->is_exclusive())
                    return notify_fail(this_object()->name() + "与其他法术无法共存。\n");
                if (skill->is_exclusive())
                    return notify_fail(skill->name() + "与其他法术无法共存。\n");
            }
        }
    }
    return 1;
}
