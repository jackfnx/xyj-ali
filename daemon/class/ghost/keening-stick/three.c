// three.c
#include <ansi.h>

inherit F_SSERVER;

int restore_env(object me, object target, int i, int j);

int perform(object me, object target)
{
    int i, j;

    if (!target) target = offensive_target(me);
    if (!target
    ||  !target->is_character()
    ||  target->is_corpse()
    ||  target==me)
        return notify_fail("你要对谁施展这一招「神·人·鬼」？\n");
    if (!me->is_fighting())
        return notify_fail("「神·人·鬼」只能在战斗中使用！\n");
    if ((int)me->query("force") < 1000)
        return notify_fail("你的内力不够！\n");
    if ((int)me->query("kee") < 300)
        return notify_fail("你的气血不足，没法子施用外功！\n");
    if ((int)me->query_skill("killer-sword", 1) < 50)
        return notify_fail("你的追魂剑级别还不够，使用这一招会有困难！\n");
    if ((int)me->query_skill("keening-stick", 1) < 50)
        return notify_fail("你的苦丧棒级别还不够，使用这一招会有困难！\n");
    if ((int)me->query_skill("hellfire-whip", 1) < 50)
        return notify_fail("你的烈火鞭级别还不够，使用这一招会有困难！\n");

    i = me->query("env/brief_message");
    j = target->query("env/brief_message");
    me->delete("env/brief_message");
    target->delete("env/brief_message");

    message_vision("\n$N双手划一大圆，猛然托天而举，伴着天上雷鸣电闪，祭出了「神·人·鬼」三招。\n", me);

    if (!present(target, environment(me))) return restore_env(me, target, i, j);
    me->set("HellZhen", 7);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

    if (!present(target, environment(me))) return restore_env(me, target, i, j);
    me->set("HellZhen", 6);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

    if (!present(target, environment(me))) return restore_env(me, target, i, j);
    me->set("HellZhen", 1);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

    restore_env(me, target, i, j);

    me->receive_damage("kee", 100);
    me->add("force", -100);

    if (!target->is_fighting(me)) {
        if (living(target)) {
            if (userp(target)) target->fight_ob(me);
            else target->kill_ob(me);
        }
    }

    me->start_busy(3);
    return 1;
}

int restore_env(object me, object target, int i, int j)
{
    if (i) me->set("env/brief_message", 1);
    if (j) target->set("env/brief_message", 1);
    me->delete("HellZhen");
    return 1;
}
