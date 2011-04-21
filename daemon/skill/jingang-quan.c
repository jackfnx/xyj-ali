// ALi by NewX
 
// jingang-quan.c, 【魔女金刚拳】

// 淫邪之拳 怨恨之拳 绝望之拳 毁灭之拳

inherit SKILL;

string name() { return "魔女金刚拳"; }

mapping *action = ({
    ([
     "name":     "「淫邪之拳」",
     "action":
"$n只觉得$N的身上散发着一股强烈淫靡气息，不禁微微恍惚。\n"
"谁知就在此时，$N轰出了石破天惊的一拳。\n"
"原来，$N竟然引爆了体内的欲火，用欲火推动力量，挥出了这震撼的一拳",
     "force":     50,
     "dodge":     -10,
     "parry":     -10,
     "damage_type":   "瘀伤",
     ]),
    ([
     "name":     "「怨恨之拳」",
     "action":
"$n忽然感到周遭温度骤然下降，潮水般的怨恨意念忽然涌入了$p的意识。\n"
"就在$n心神恍惚之际，$N的拳头从一个诡异的角度轰向了$n的$l",
     "force":     100,
     "dodge":     10,
     "parry":     -10,
     "damage_type":   "瘀伤",
     ]),
    ([
     "name":     "「绝望之拳」",
     "action":
"巨大的绝望感忽然袭上了$n的心头，想要放弃的念头突然从$p的心中闪现。\n"
"就在这时，$N的拳头到了，这是饱含人世间绝望情绪的一拳",
     "force":     70,
     "dodge":     10,
     "parry":     10,
     "damage_type":   "瘀伤",
     ]),
    ([
     "name":     "「毁灭之拳」",
     "action":
"一切似乎都停止了下来，一片萧瑟肃杀之气充塞了整个空间。\n"
"毁灭！无尽的毁灭！\n"
"$N的拳头，携带着无尽的毁灭气息，就这样袭向了$n的$l",
     "force":     70,
     "dodge":     -10,
     "parry":     10,
     "damage_type":   "瘀伤",
     ]),
});

int valid_learn(object me)
{
    if (me->query("gender") != "女性")
        return notify_fail("魔女金刚拳，女性专用。\n");
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("练魔女金刚拳必须空手。\n");
    return 1;
}

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if ((int)me->query("sen") < 40)
        return notify_fail("你的精神无法集中了，休息一下再练吧。\n");
    if ((int)me->query("kee") < 40)
        return notify_fail("你现在手足酸软，休息一下再练吧。\n");
    if ((int)me->query("force") < 10)
        return notify_fail("你的内力不够了。\n");

    me->receive_damage("kee", 30);
    me->add("force", -10);

    return 1;
}
