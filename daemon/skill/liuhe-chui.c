
//【六合锤法】

/*
六合锤法  dodge  7    parry  -7    damage  27
*/

inherit SKILL;

string name() { return "六合锤法"; }

mapping *action = ({
    ([  "action":           "$N哪管三七二十一，左手抄起$w朝着$n当头就是一家伙",
        "dodge":        15,
        "parry":        -10,
        "damage":       35,
        "damage_type":  "砸伤",
    ]),
    ([  "action":           "只见$N眼冒凶光，青筋凸起，右手举着$w就朝$n的$l狠命扫了过去",
        "dodge":        10,
        "parry":        -15,
        "damage":       25,
        "damage_type":  "砸伤",
    ]),
    ([  "action":           "只听轰！地一声$N的$w在地上砸得尘土飞扬！紧接着$N又翻了个跟头，反身砸向了背后的$n",
        "dodge":        5,
        "parry":        -10,
        "damage":       35,
        "damage_type":  "砸伤",
    ]),
    ([  "action":           "只见$N稍一运气，手中的$w直来直去，直向$n平推过去",
        "dodge":        5,
        "parry":        0,
        "damage":       20,
        "damage_type":  "砸伤",
    ]),
    ([  "action":           "$N大喝一声，手中的$w举重若轻，势若疯虎地向$n$l连连砸去，势若万钧，如泰山压顶啊",
        "dodge":        5,
        "parry":        0,
        "damage":       20,
        "damage_type":  "砸伤",
    ]),
    ([  "action":           "但见$N高高举起了$w，猛地砸下来，$n只听一阵风声擦耳而过！\n$n正在暗叫侥幸之时，$N的$w却就势一转，又从下往上兜了回来",
        "dodge":        5,
        "parry":        -10,
        "damage":       25,
        "damage_type":  "砸伤",
    ]),
});

int valid_learn(object me)
{
    object ob;

    if ((int)me->query("max_force") < 50)
        return notify_fail("你的内力不够，没有办法练六合锤法。\n");

    if (!(ob = me->query_temp("weapon"))
    ||  (string)ob->query("skill_type") != "hammer")
        return notify_fail("你必须先找一柄大锤才能练六合锤法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="hammer" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if ((int)me->query("kee") < 50
    ||  (int)me->query("force") < 50)
        return notify_fail("你的内力或气不够，没有办法练习六合锤法。\n");
    me->receive_damage("kee", 30);
    me->add("force", -5);
    write("你按着所学练了一遍六合锤法。\n");
    return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

