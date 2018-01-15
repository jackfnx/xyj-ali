#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
    object weapon;
    int damage;
    string msg,str;

    if (!target) target = offensive_target(me);
    if (!target
    ||  !target->is_character()
    ||  target->is_corpse()
    ||  target==me)
        return notify_fail("你要对谁施展这一招「暴雪天威」？\n");
    if (!me->is_fighting())
        return notify_fail("「暴雪天威」只能在战斗中使用！\n");
    if ((int)me->query("max_force") < 500 || (int)me->query("force") < 500)
        return notify_fail("你的内力不够！\n");
    if ((int)me->query("sen") < 500)
        return notify_fail("你的精神不足，没法子施用外功！\n");
    if ((int)me->query_skill("ice-blade", 1) < 100)
        return notify_fail("你的冰魄寒刀级别还不够，使用这一招会有困难！\n");
    message_vision(HIW"\n$N运起寒气，身形一转，四周顿时冰冻数尺，空气中寒气逼人$n只冻的忘记的抵抗！\n"NOR, me, target);
    me->set_temp("noauto", 1);
    target->start_busy(random(2));
    damage = random(((int)me->query_skill("blade")));
    message_vision(HIW"\n$N嘿嘿一声冷笑，竟然隐入雪花之中。$n大急，四下找寻$N，忽然背后一阵寒气随着\n"NOR, me, target);
    message_vision(HIW"\n刀光狂袭过来！！！\n"NOR, me, target);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
    COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
    if (random(me->query("combat_exp"))>random(target->query("combat_exp"))/4) {
        message_vision(HIY"\n打斗中,一只金色大鹏鸟远远飞来！$N和$n都看呆了！\n"NOR, me, target);
        message_vision(HIY"\n突然大鹏鸟用翅膀一扇,顿时狂风大作！\n"NOR, me, target);
        if (random(me->query("force_factor"))>target->query("force_factor")/4) {
            message_vision(HIR"\n$N见机不可失,连忙攻出一招！\n"NOR,me,target);
            target->receive_damage("kee", damage*2); 
            target->receive_damage("sen", damage*2); 
            message_vision(HIR"\n狂风夹杂着碎石漫天飞舞,把$n砸得遍体鳞伤！\n"NOR, me, target);
            target->receive_wound("kee", damage);
            target->receive_wound("sen", damage);
            COMBAT_D->report_status(target);
        } else if(random(me->query("force_factor"))>target->query("force_factor")/2) {
            message_vision(HIR"\n狂风夹杂着碎石漫天飞舞,把$n砸得遍体鳞伤！\n"NOR, me, target);
            target->receive_wound("kee", damage);
            COMBAT_D->report_status(target);
        } else {
            message_vision(HIR"\n狂风夹杂着碎石漫天飞舞,把$N和$n砸得遍体鳞伤！\n"NOR, me, target); 
            target->receive_wound("kee", damage);
            target->receive_wound("sen", damage);
            COMBAT_D->report_status(target);
            me->receive_wound("kee", damage/10);
            COMBAT_D->report_status(me);
        }
    }
    me->delete_temp("noauto");
    me->receive_damage("sen", 100);
    me->add("force", -300);
    
    me->start_busy(2);
    return 1;
}
