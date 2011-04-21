//情丝
//requirement: jueqingbian > 100, kee > 20%, sen > 50%

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
    string msg;
    int ap, dp, bonus, my_exp, your_exp;
    int qi, max_qi, qi_pcg, shen, max_shen, shen_pcg;
    object whip, weapon;

    if (!target) target = offensive_target(me);

    if (!target || !target->is_character()
            || target->is_corpse()
            || target == me)
        return notify_fail("你要打谁？\n");

    if (!whip = me->query_temp("weapon"))
        return notify_fail("你没拿鞭子，怎么夺取别人的兵器？\n");
    if (!weapon = target->query_temp("weapon"))
        return notify_fail("对方没拿兵器，你怎么夺取？\n");

    if ((int)me->query_skill("jueqingbian", 1) < 100)
        return notify_fail("你的绝情鞭火候还不够！\n");
    if (me->query_skill_mapped("force") != "moonforce")
        return notify_fail("绝情鞭必须配合玉女心经才能使用。\n");
    if (me->query_skill("moonforce", 1) < 100)
        return notify_fail("你的玉女心经不够纯熟。\n");
    if (!target->is_fighting(me))
        return notify_fail("你们没有在打架！\n");

    qi = me->query("kee");
    max_qi = me->query("max_kee");
    qi_pcg = qi*100/max_qi;
    if (qi < 20 || qi_pcg < 50)
        return notify_fail("你气力不济，心有余而力不足。\n");

    shen = me->query("sen");
    max_shen = me->query("max_sen");
    shen_pcg = shen*100/max_shen;
    if (shen < 20 || shen_pcg < 50)
        return notify_fail("你神志不清，心有余而力不足。\n");

    if (me->query("force") < 200)
        return notify_fail("你内力不继，心有余而力不足。\n");

    me->add("force", -200);
    me->receive_damage("kee", 20);
    me->receive_damage("sen", 20);

    msg = HIC "$N的双眼忽然变得空洞，手中的" + whip->query("name")
        + HIC "若虚若实，转眼间竟已缠上了$n手中的" + weapon->query("name")
        + HIC "。\n" NOR;

    ap = me->query_skill("jueqingbian", 1) + me->query_str() * 10;
    dp = target->query_str() * 10;
    my_exp = me->query("combat_exp");
    your_exp = target->query("combat_exp");
    if (my_exp > your_exp)
    {
        bonus = 100 * my_exp / your_exp - 100;
    }
    else
    {
        bonus = 100 - 100 * my_exp / your_exp;
    }

    if (random(ap + dp + bonus) > dp)
    {
        weapon->unequip();
        msg += HIC "$n大惊，连忙奋力回夺，谁知" + whip->query("name")
            + HIC "上经传来阵阵潜力，丝丝缕缕化解了$n的力量。\n" NOR;
        if ((int)me->query_encumbrance() + weapon->weight()
                < (int)me->query_max_encumbrance())
        {
            weapon->move(me);
            msg += HIC "$N突然将手中" + whip->query("name")
                + HIC "一抖，$n再也拿捏不住手中的" + weapon->query("name")
                + HIC "，被$N硬夺了过去。\n" NOR;
        }
        else
        {
            weapon->move(environment(me));
            msg += HIC "$N突然将手中" + whip->query("name")
                + HIC "一抖，$n再也拿捏不住手中的" + weapon->query("name")
                + HIC "，远远的飞了出去。\n" NOR;
        }
    }
    else
    {
        msg += HIC "$n并不惊慌，手中" + weapon->query("name")
            + HIC "连续抖动，很快就将上面" + whip->query("name")
            + HIC "的缠绕挣脱了。\n" NOR;
    }

    me->start_busy(2+random(3));

    message_vision(msg, me, target);
    return 1;
}

