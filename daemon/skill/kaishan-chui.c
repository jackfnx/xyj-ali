/*
开山锤  dodge  15    parry  -15    damage  30
其锤法直来直去，招招为实，势大力猛，招架抵挡
甚为不易，一但碰上则伤害极大。但不足是不够轻
盈。
*/
inherit SKILL;

void hitagain(object me, object victim, object weapon,int damage);

string name() { return "开山锤"; }

mapping *action = ({
    ([   "action":   "$N手中$w一转，卷着一股强劲的风力挥向$n的$l，\n这一下又急又猛，势大力狠，眼见就到了$n身前",
        "dodge":   10,
        "parry":   -10,
        "damage":   30,
        "damage_type":   "砸伤",
        "post_action":      (: hitagain :),
    ]),
    ([   "action":   "$N双手一震，手中$w夹带着闷雷般的响声，劈头盖脸地就向$n砸了过去",
        "dodge":   15,
        "parry":   -15,
        "damage":   30,
        "damage_type":   "砸伤",
        "post_action":      (: hitagain :),
    ]),
    ([   "action":   "$N将$w高举过肩，蓄紧力发，对准$n的$l发出雷霆一击",
        "dodge":   20,
        "parry":   -20,
        "damage":   35,
        "damage_type":   "砸伤",
        "post_action":      (: hitagain :),
    ]),
    ([   "action":   "$N身走轻灵，手中$w忽上忽下，令人捉摸不清去路，\n就在$n一恍惚间，“唰”地砸向$n的$l",
        "dodge":   0,
        "parry":   -10,
        "damage":   25,
        "damage_type":   "砸伤",
        "post_action":      (: hitagain :),
    ]),
    ([   "action":   "$N趁与$n错身之机，倒转$w，锤把戳向了$n，\n这一下如白蛇吐芯，悄无声息的点上了$n的$l",
        "dodge":   10,
        "parry":   -10,
        "damage":   20,
        "damage_type":   "戳伤",
        "post_action":      (: hitagain :),
    ]),
    ([   "action":   "$N紧握$w猛挥了个大圆，卷的周身长内沙土尘扬，\n趁$n不能辨物之记，手中$w斜斜地砸向$n的$l",
        "dodge":   20,
        "parry":   -25,
        "damage":   30,
        "damage_type":   "砸伤",
        "post_action":      (: hitagain :),
    ]),
});

int valid_learn(object me)
{
    object ob;

    if ((int)me->query("str") < 25)
        return notify_fail("开山锤要身强力壮才能发挥作用。\n");

    if ((int)me->query("max_force") < 100)
        return notify_fail("你的内力不够，没有办法学开山锤。\n");

    if (!(ob = me->query_temp("weapon")) || (string)ob->query("skill_type") != "hammer")
        return notify_fail("你必须先找一把锤子才能学开山锤。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="hammer"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if ((int)me->query("str") < 25)
        return notify_fail("开山锤要身强力壮才能发挥作用。\n");

    if ((int)me->query("kee") < 30 || (int)me->query("force") < 5)
        return notify_fail("你现在太累了，强练无益。\n");
    me->receive_damage("kee", 30);
    me->add("force", -5);
    write("你按着所学练了一遍开山锤。\n");
    return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

void hitagain(object me, object victim, object weapon,int damage)
{
    if (damage != -2) return;

    // if victim parried out the attack, we attack again...
    message_vision("$N震得两臂发麻，动弹不得$n趁机发动攻击！\n", victim, me);
    COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
}
