// ALi by NewX

// firesword. 【烈焰飞腾剑法】

/*
烈焰飞腾剑法    dodge  -20    parry  -10    damage  15

*/

// 寒芳留照魂应驻，碗凝深翠拂平沙
// 攒花染出几霜痕，霜印传神梦也空
// 篱筛破落锁玲珑，暗香浮动影黄昏
// 风波不信菱枝弱
inherit SKILL;

string name() { return "烈焰飞腾剑法"; }

mapping *action = ({
   ([   "action":
"$N使一招「寒芳留照魂应驻」，手中$w化为一道疾光刺向$n的$l",
     "dodge":     -5,
                "parry":                -10,
     "damage":     10,
     "damage_type":   "刺伤"
   ]),
   ([   "action":
"只见$N几个急转，使出「晚凝深翠拂平沙」，一声娇喝中剑光冲天而起，扫向$n的$l",
     "dodge":     -35,
                "parry":                -5,
     "damage":     20,
     "damage_type":   "割伤"
   ]),
   ([   "action":
"$N淡淡一笑，一式「攒花染出几霜痕」舞出无数幻影，$n只觉得阵阵幽香四面袭来，却不知该如何闪躲",
     "dodge":     -10,
                "parry":                -15,
     "damage":     15,
     "damage_type":   "刺伤"
   ]),
   ([   "action":
"$N手中$w轻轻一抖，一式「霜印传神梦也空」幻出一遍寒光罩向$n。$n只觉得连呼吸都被冻住了",
     "dodge":     -30,
                "parry":                -5,
     "damage":     15,
     "damage_type":   "刺伤"
   ]),
   ([   "action":
"$N手中$w再一抖，只见寒光点点，飘浮不定。\n这一招「篱筛破月锁玲珑」只看得$n眼花缭乱，哪里还能招架",
     "dodge":     -20,
                "parry":                -20,
     "damage":     15,
     "damage_type":   "刺伤"
   ]),
        ([      "action":
"$n只觉得一缕冷香掠过，$N已悄然间飘至$n身后，剑心直指$n的后胸，正是一式「暗香浮动月黄昏」",  
                "dodge":                -35,
                "parry":                -5,
                "damage":           20, 
                "damage_type":  "刺伤"
        ]),
   ([      "action":
"$N不闪不避，一式「风波不信菱枝弱」，神色娴雅，蓄势待发，一道澄如秋水、寒似玄冰的剑光直指$n破绽所在",
                "dodge":                -5,
                "parry":                -10,
                "damage":          10,
                "damage_type":  "刺伤"
        ]),
   
});

int valid_enable(string usage)
{
    return usage == "sword" || usage == "parry";
}

int valid_learn(object me) {
    if ((int)me->query_skill("foxforce",1) < 40 )
        return notify_fail("你的天狐心法修为尚浅，没法学烈焰剑！\n");
    return 1;
}

mapping query_action(object me, object weapon) 
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)(weapon->query("skill_type")) != "sword")
        return notify_fail("你这才想起手里没剑，怎么练烈焰剑啊？ :)\n");
    if ((int)(me->query("kee")) < 50)
        return notify_fail("你已经精疲力竭，没法儿练下去啦！\n");
    me->receive_damage("kee", 30);
    return 1;
}

string perform_action_file(string action)
{
    return CLASS_D("fox") + "/firesword/" + action;
}

