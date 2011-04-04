// 回梦
// requirement: spells 180,moonshentong 120, mana 400, sen 20

inherit SSERVER;
#include <ansi.h>

int cast(object me, object target)
{
    string msg;
    int success, ap, dp, ap2, ap3, ap4, dp2, dp3, dp4,howlong;

    if (!target) target = offensive_target(me);

    if ((int)me->query_skill("spells") < 180
     || (int)me->query_skill("moonshentong",1) < 120)
        return notify_fail("你还没学会回梦咒。。。\n");

    if (!target
     || !target->is_character()
     || target->is_corpse()
     || target==me)
        return notify_fail("你想咒谁入梦？\n");  

    if ((int)me->query("mana") < 400)
        return notify_fail("你的法力不够！\n");
    if ((int)me->query("sen") < 20)
        return notify_fail("你无法集中精力！\n");
    if (!living(target))
        return notify_fail("有这个必要吗？\n");

    me->add("mana", -400);
    me->receive_damage("sen", 20);

    msg = HIM "$N凝视着$n的双眼，温柔地轻抚着$n的面庞，在$n耳边轻声呢喃：『睡吧，睡吧。。。』\n"
            + "$n顿时觉得神倦眼困，全身无力。\n" NOR;

    success=1;
    ap = me->query_skill("spells");
    ap = ap * ap * ap /10 ;
    ap += (int)me->query("combat_exp")/2;
    dp = target->query("combat_exp");

    if (target->is_fighting(me)) dp=dp*2;
    if (random(ap+dp)<dp) success=0;

    ap = (int)me->query("mana");
    dp = (int)target->query("mana");
    if (random(ap + dp)<dp) success = 0;

    if (success == 1){
        msg +=  HIM "$n不知不觉的哈欠连连，眼皮沉重，终于支持不住，合上了双眼。\n" NOR;
        message_vision(msg, me, target);

        target->set_temp("force_sleep",1);
        if (target->is_fighting())
            target->command_function("surrender");
        if (!target->command_function("sleep"))
            message_vision(HIM"\n$N晃了晃脑袋，似乎清醒了不少，又把眼睛睁开了。\n"NOR, target);
        target->delete_temp("force_sleep");
        me->start_busy(1+random(2)); 
    }
    else {
        msg += HIM"$n忽觉不妥，大喝一声，双目一张，精光四射！$N猝不及防，吓了一跳！\n" NOR;	
        message_vision(msg, me, target);
        if (living(target)) target->kill_ob(me);
        me->start_busy(5+random(5));
    
    } 

    return 5+random(5);
}

int help(object me)
{
    write(@HELP
【回梦】
将敌人送入梦乡。

〖指令〗    cast huimeng on <object>
〖要求〗    基本法术１８０级，太阴仙诀１２０级
HELP);
    return 1;
}
