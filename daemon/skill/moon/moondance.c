// Ali by NewX
 
//【冷月凝香舞】 moondance.c
// cglaem...12/07/96.

inherit SKILL;

mapping *action = ({
    ([   "action":     "$N面色冷峻，如冰雪女神，背后更隐隐升起了一轮明月的虚影，\n「海上生明月」，竟是这一道『冷月凝香舞』中极富盛名的杀招",
     "dodge":     -5,
     "parry":     -5,
     "force":     50,
     "damage_type":   "瘀伤",
    ]),
    ([   "action":     "$N忽然发出一声叹息，眼神中流露出忧伤的神色，出招似乎也慢了。\n$n刚想趁势反击，忽见$N素指纤纤，直拂$n的要穴。正是『冷月凝香舞』中的绝招「举杯邀明月」",
     "dodge":     -10,
     "parry":     -10,
     "force":     120,
     "damage_type":   "刺伤",
     "weapon":     "右手掌",
    ]),
    ([   "action":     "只见$N面现凄绝之色，忽然使出了同归于尽的招数，「我本将心付明月」",
     "dodge":     -20,
     "parry":     -20,
     "force":     70,
     "damage_type":   "瘀伤",
    ]),
    ([   "action":     "$N面现娇羞之色，仿佛忽然产生了无穷绮念，$n一见，不禁心中一荡。\n谁知$N竟然抓住机会全力击向了$n的$l，「事如春梦了无痕」",
     "dodge":     15,
     "parry":     15,
     "force":     60,
     "damage_type":   "瘀伤",
    ]),
    ([   "action":     "只见$N的眼神忽然变得迷离，双手拂向了胸前的双峰，也拂向了胯下的股间。\n$n一见大惊，一时间竟不知所措，就在此时，一股逼人的杀气从他心底浮现\n——「风月无边，刻骨铭心」",
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
    return ( usage=="dodge" || usage=="charm" || usage=="unarmed" );
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
    return CLASS_D("girl") + "/moondance/" + func;
}

int help(object me)
{
    write(@HELP
【冷月凝香舞】
此舞本是嫦娥所创的一套舞蹈，后经过西王母的改造，将其改造成了
一套上乘轻功。
与妲己一战后，西王母对此舞进行了多次改造，更是将它改造成了一
套拳法，舞姿也由高傲圣洁，竟变得极邪、极淫、极媚。这些改造的
争议极大，有几个弟子表达了极其强烈的抗议；谁知，西王母的立场
更是强硬，那些表达了抗议的弟子第二天就消失了。于是，大多数弟
子只好低头，修炼起了这种全新的舞姿。

招数名称：
海上生明月                   我本将心付明月
举杯邀明月                   事如春梦了无痕
风月无边，刻骨铭心

〖特殊法门〗
①  销魂一笑：      perform supersmile on <object>
HELP);
    return 1;
}
