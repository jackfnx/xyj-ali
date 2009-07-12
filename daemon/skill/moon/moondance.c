// Ali by NewX
 
//【冷月凝香舞】 moondance.c
// cglaem...12/07/96.

inherit SKILL;

mapping *action = ({
    ([   "action":     "$N浅浅一笑，一招「自在飞花轻似梦」若有若无地拍向$n的$l",
     "dodge":     -5,
     "parry":     -5,
     "force":     50,
     "damage_type":   "瘀伤",
    ]),
    ([   "action":     "$N身形一顿，似有退意。$n正待反攻，\n忽见$N纤纤五指，直拂$n双目。正是“百花掌”之杀手「一枝红杏出墙来」",
     "dodge":     -10,
     "parry":     -10,
     "force":     120,
     "damage_type":   "刺伤",
                        "weapon":     "右手掌",
    ]),
    ([   "action":     "只见$N嫣然一笑，双掌翻飞，一招「人面桃花相映红」当真是妙到毫巅",
     "dodge":     -20,
     "parry":     -20,
     "force":     70,
     "damage_type":   "瘀伤",
    ]),
    ([   "action":     "$N纤腰一摆，陡然滑出数尺，右手顺势一招「黄菊枝头生晓寒」往$n的$l拍去",
     "dodge":     15,
     "parry":     15,
     "force":     60,
     "damage_type":   "瘀伤",
    ]),
    ([   "action":     "只见$N双唇紧闭，面色凝重，一招「此花开尽更无花」全力击向$n的$l",
     "dodge":     5,
     "parry":     5,
     "force":     80,
     "damage_type":   "瘀伤",
    ]),
});

string *dodge_msg = ({
     "$n低头细数裙褶，情思困困，步法回旋之际似乎娇柔无力，却将$N攻势一一化于无形。\n",
     "只见$n一个转身，忽然回眸一笑。$N一楞之下，哪里还有人在。\n",
     "可是$n婉尔一笑，不退反进，身形径向$N飘来。\n$N只觉一股甜香入鼻，这一招竟无着力之处。\n",
     "$n身法轻灵，腰肢几拧，居然幻出斑驳月影。$N眼一花，哪里分得出是人，是影。\n",
     "$n裙裾飘飘，白衣姗姗，已然从$N头顶飞过，这般女神端丽之姿，仙子缥缈之形，$N不由得看呆了！\n",
     "$n脚步轻盈，风姿嫣然，身子便如在水面上飘浮一般掠过，不等$N劲风袭到，已悄然隐去。\n",
     "$n纤腰微颤，带飞如虹，轻轻将$N的劲力拨在一旁，尽数化解。\n",

});

int valid_enable(string usage)
{
    return ( usage=="dodge" || usage=="fascination" || usage=="unarmed" );
}

int valid_learn(object me)
{
    if ((string)me->query("gender") != "女性")
        return notify_fail("冷月凝香舞只有女性才能练。\n");
    if ((int)me->query("spi") < 10)
        return notify_fail("你的灵性不够，没有办法练冷月凝香舞。\n");
    return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if ( (int)me->query("sen") < 30 )
        return notify_fail("你的精神太差了，不能练冷月凝香舞。\n");
    me->receive_damage("sen", 30);
    return 1;
}

string perform_action_file(string func)
{
    return CLASS_D("moon") + "/moondance/" + func;
}
