// lovefire-whip.c
// 欲火鞭

inherit SKILL;

string name() { return "欲火鞭"; }

mapping *action = ({
    ([
        "action" : "只见$N眼神迷离，浑身好像燃烧着一团火，，一式「欲火焚身」，$w向$n袭来",
        "dodge"  : -5,
        "damage" : 20,
        "parry"  : -10,
        "lvl"         : 0,
        "skill_name"  : "欲火焚身",
        "damage_type" : "割伤",
        "post_action" : (: call_other, WEAPON_D, "wave_weapon" :),
    ]),
    ([
        "action" : "$N面色通红，心口仿佛冒出了一团火，使出了「欲火焚心」，强大的内力向$n激射而来",
        "dodge"  : -10,
        "damage" : 30,
        "parry"  : 5,
        "lvl"         : 10,
        "skill_name"  : "欲火焚心",
        "damage_type" : "内伤",
    ]),
    ([
        "action" : "$N一式「欲火焚房」，小腹之中隐约透出了一团火，$w向$n猛地刺来",
        "dodge"  : -5,
        "damage" : 20,
        "parry"  : 5,
        "lvl"         : 20,
        "skill_name"  : "欲火焚房",
        "damage_type" : "刺伤",
    ]),
    ([
        "action" : "$N轻轻地呻吟，背后似乎出现了一个赤裸的女婴虚影，一招「欲火焚胎」向$n卷去",
        "dodge"  : -10,
        "damage" : 30,
        "parry"  : -10,
        "lvl"         : 30,
        "skill_name"  : "欲火焚胎",
        "damage_type" : "擦伤",
    ]),
});

int valid_enable(string usage)
{
    return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{
    if ((int)me->query_skill("foxforce",1) < 40)
        return notify_fail("你的天狐心法修为尚浅，没法学欲火鞭！\n");
    return 1;
}

mapping query_action(object me, object weapon) 
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon"))
    ||  (string)(weapon->query("skill_type")) != "whip")
        return notify_fail("你这才想起手里没鞭子，怎么练焚情鞭啊？ :)\n");
    if ((int)(me->query("kee")) < 50)
        return notify_fail("你已经精疲力竭，没法儿练下去啦！\n");
    me->receive_damage("kee", 30);
    return 1;
}

string perform_action_file(string action)
{
    return CLASS_D("fox") + "/lovefire-whip/" + action;
}

