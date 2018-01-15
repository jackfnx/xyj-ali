// Jiz
#include <ansi.h>

inherit F_SSERVER;

int cast(object me, object target)
{
    int success_adj, damage_adj;

    success_adj = 180;
    damage_adj = 170;

    if (!target) target = offensive_target(me);

    if (me->query("family/family_name")!="火云洞")
        return notify_fail("“三味真火”只有火云洞门人才可以用！\n");
    if (!target
    ||  !target->is_character()
    ||  target->is_corpse()
    ||  target==me)
        return notify_fail("你要对谁喷三味真火？\n");

    if ((int)me->query_skill("pingtian-dafa", 1) < 30)
        return notify_fail("你的平天大法火候不够，哪里喷得出真火！\n");

    if ((int)me->query("mana") < 25+(int)me->query("mana_factor"))
        return notify_fail("你的法力不够，喷出的真火恐怕没有什么用！\n");

    if ((int)me->query("force") < 100)
        return notify_fail("你的内力不够，无法将真火喷出。\n");

    if ((int)me->query("sen") < 10)
        return notify_fail("你现在神智不清，别把自己烧伤了！\n");

    me->add("mana", -25-2*(int)me->query("mana_factor"));
    me->receive_damage("sen", 50);

    if (random(me->query("max_mana")) < 50) {
        message_vision(HIM"$N口中念念有词。。。但什么也没有发生！\n"NOR,me);
        return 1;
    }
    
    me->receive_wound("kee", 10);

    msg = HIC "$N伸手在鼻子上砸了两，顿时鲜血直冒，突然红橙黄三道火焰呼！地一声向$n卷去！\n" NOR;

    message_vision(msg, me, target);

    ap = (int)me->query_skill("spells");
    ap = ap * ap / 1000 * ap;
    ap = ap * (1 + (int)me->query("combat_exp")/5000000);
    ap = ap + (int)me->query("combat_exp");
    ap = ap/100*180;

    dp = (int)target->query("combat_exp");

    if (random(ap+dp) < dp) {
        msg = HIC"\n结果被$n躲开了。\n"NOR;
        message_vision(msg, me, target);
    }
    else {
        a_damage = me->query("mana")/40;
        d_damage = target->query("mana")/40;
        a_damage += random(me->query("eff_sen")/20);
        d_damage += random(target->query("eff_sen")/20);
        a_damage += me->query("mana_factor")*170/100;
        d_damage += random(target->query("mana_factor")*170/100);
        
        if (a_damage > d_damage) {
            damage = a_damage - d_damage;
            damage += me->query("mana_factor")*170/100;
            damage = damage*170/100;
            damage_bonus = (int)me->query_skill("spells")/200;
            if (damage_bonus > 3) damage_bonus = 3;
            damage += damage*damage_bonus;
            if (damage > 3000) damage = 3000;
            
            msg = HIC "结果$n被烧得焦头烂额！\n" NOR;
            message_vision(msg, me, target);
            target->receive_damage("kee", damage*3/5, me);
            target->receive_wound("kee", damage/2, me);
            COMBAT_D->report_status(target);
        } else if (a_damage < d_damage) {
            msg = HIC "结果火焰被$n以法力一逼，反向$N回卷而去！\n" NOR;
            message_vision(msg, me, target);
            
            damage = d_damage;
            if (damage > 400) damage = 400;
            damage -= target->query("mana_factor");
            damage = damage*170/100;
            damage_bonus = (int)me->query_skill("spells")/200;
            if (damage_bonus < 1) damage_bonus = 1;
            if (damage_bonus > 10) damage_bonus = 10;
            damage += damage/damage_bonus;
            
            msg = HIR "\n结果$n躲避不及，被烧得焦头烂额！\n" NOR;
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

