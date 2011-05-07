// tuntian.c
#include <ansi.h>

inherit F_SSERVER;

int cast(object me, object target)
{
    string msg;
    int ap, dp, a_damage, d_damage, damage, damage_bonus;

    if (!target) target = offensive_target(me);
    if (!target
    ||  !target->is_character()
    ||  target->is_corpse()
    ||  target==me)
        return notify_fail("你要对谁施展魔兽吞天？\n");
    if (!me->query("cast_tuntian"))
        return notify_fail("「魔兽吞天」是青狮老魔的绝活，没有他的亲传谁也用不了！\n");
    if ((int)me->query("mana") < 100+2*(int)me->query("mana_factor"))
        return notify_fail("你的法力不够！\n");
    if ((int)me->query("sen") < 100)
        return notify_fail("你无法集中精力！\n");

    me->add("mana", -25 - 2*(int)me->query("mana_factor"));
    me->receive_damage("sen", 50);

    if (random(me->query("max_mana")) < 50) {
        write("坏了，青面狮子不知跑哪去了！\n");
        return 1;
    }

    if (me->query("cast_tuntian") > 0)
        msg = HIC "\n$N口中念了句咒文，半空闪出一只青面獠牙的狮子，"
                +"张开血盆大口向$n咬去！\n" NOR;
    else // cast_tuntian == -1, it's qingshi-laomo himself
        msg = HIC "\n$N口中念了句咒文，现出青色狮子原型，"
                +"张开血盆大口向$n咬去！\n" NOR;

    message_vision(msg, me, target);

    ap = (int)me->query_skill("spells");
    ap = ap * ap / 1000 * ap;
    ap = ap * (1 + (int)me->query("combat_exp")/5000000);
    ap = ap + (int)me->query("combat_exp");
    ap = ap/100*120;

    dp = (int)target->query("combat_exp");

    if (random(ap+dp) < dp) {
        msg = HIC "\n$n连忙一侧身闪在一旁。\n" NOR;
        message_vision(msg, me, target);
    }
    else {
        a_damage = me->query("mana")/40;
        d_damage = target->query("mana")/40;
        a_damage += random(me->query("eff_sen")/20);
        d_damage += random(target->query("eff_sen")/20);
        a_damage += me->query("mana_factor")*120/100;
        d_damage += random(target->query("mana_factor")*120/100);
        
        if (a_damage > d_damage) {
            damage = a_damage - d_damage;
            damage += me->query("mana_factor")*120/100;
            damage = damage*120/100;
            damage_bonus = (int)me->query_skill("spells")/200;
            if (damage_bonus > 3) damage_bonus = 3;
            damage += damage*damage_bonus;
            if (damage > 3000) damage = 3000;
            
            msg = HIR "\n结果$n被咬了个正着！\n" NOR;
            message_vision(msg, me, target);
            target->receive_damage("kee", damage*3/5, me);
            target->receive_wound("kee", damage/2, me);
            COMBAT_D->report_status(target);
        } else if (a_damage < d_damage) {
            msg = HIC "只听$n一声怒吼，青毛狮子被震得辨不清方向，反而咬向了$N！\n" NOR;
            message_vision(msg, me, target);
            
            damage = d_damage;
            if (damage > 400) damage = 400;
            damage -= target->query("mana_factor");
            damage = damage*120/100;
            damage_bonus = (int)me->query_skill("spells")/200;
            if (damage_bonus < 1) damage_bonus = 1;
            if (damage_bonus > 10) damage_bonus = 10;
            damage += damage/damage_bonus;
            
            msg = HIR "\n结果$N被咬了个正着！\n" NOR;
            message_vision(msg, me, target);
            me->receive_damage("kee", damage*3/5, target);
            me->receive_wound("kee", damage/2, target);
            COMBAT_D->report_status(me);
        } else
            message_vision(HIB "结果正好被$N以法力逼住，谁也没有吃亏。\n" NOR, target);
    }

    me->start_busy(1+random(2));
    target->kill_ob(me);

    return 3+random(5);
}

