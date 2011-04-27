// feedback.c
// 返本归元

inherit F_SSERVER;

int conjure(object me, object target)
{
    int diff, zyneed;

    if (target && target != me)
        return notify_fail("你只能操纵自己返本归元。\n");

    if ((int)me->query("atman") < 20)
        return notify_fail("你的真元不够。\n");
    if ((int)me->query_skill("magic") < 10)
        return notify_fail("你还没有掌握这种本命神通。\n"); 
    diff = me->query("eff_gin") - me->query("gin");
    zyneed = diff * 50 / (int)me->query_skill("magic");
    if (zyneed < 1)
        return notify_fail("你现在精元充足，没必要返本归元。\n");
    
    if (zyneed > me->query("atman")) zyneed = me->query("atman");
    diff = zyneed * (int)me->query_skill("magic") / 50;
    
    me->receive_heal("gin", diff);
    me->add("atman", -zyneed);

    message_vision("$N的身上隐约传来力量的波动，脸色顿时变得红润起来。\n", me);

    if (me->is_fighting()) me->start_busy(1);

    return 1;
}
