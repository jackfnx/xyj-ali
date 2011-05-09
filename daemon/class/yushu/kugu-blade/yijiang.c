#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
    string msg;
    int extra,lvl,lv;
    int i;
    object weapon;

    if (!target) target = offensive_target(me);
    if (!target
    ||  !target->is_character()
    ||  !me->is_fighting(target))
        return notify_fail("『一将功成』只能对战斗中的对手使用。\n");
    if (me->query("family/family_name") != "陷空山无底洞")
        return notify_fail("『一将功成』只有无底洞门人才可以用！\n");
    weapon = me->query_temp("weapon");
    if ((string)weapon->query("skill_type") != "blade")
        return notify_fail("你手上无刀，不能使用『一将功成』！\n");
    if ((int)me->query("force") <= 1000)
        return notify_fail("你内力不够，不能使用『一将功成』！\n");

    extra = me->query_skill("kugu-blade", 1) / 4;
    me->add_temp("apply/attack", extra);
    me->add_temp("apply/damage", extra);
    msg = HIR "$N使出［枯骨刀法］的『一将功成』，手中的"+ weapon->name() +"斜斜劈出，$n顿觉呼吸一窒！" NOR;
    message_vision(msg, me, target);
    COMBAT_D->do_attack(me, target, weapon, TYPE_REGULAR);
    msg = HIW "一将功成万骨枯！！！\n" NOR;
    message_vision(msg, me, target);
    lvl = extra/10;
    if (lvl>8) lvl = 8;
    for (i=0; i<=lvl; i++) {
        if (!target) return 1;
        msg = HIY "$N劈出一刀！\n" NOR;
        COMBAT_D->do_attack(me, target, weapon, TYPE_REGULAR);
        message_vision(msg, me, target);
    }
    me->add_temp("apply/attack", -extra);
    me->add_temp("apply/damage", -extra);
    me->add("force", -1*random(300));
    me->start_busy(2);
    return 1;
}
