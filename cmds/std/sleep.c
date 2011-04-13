// sleep.c

#include <ansi.h>

int main(object me, string arg)
{
    object obj, old_target;
    int i;
    object *inv;   
    object where = environment(me);

    //mon 12/18/97, allow forced sleep by "keshui chong".
    if (!where->query("sleep_room") && !me->query_temp("force_sleep"))
        return notify_fail("这里不是睡觉的地方。\n");
    if (me->is_busy())
        return notify_fail("你正忙着呢！\n");
    if (me->is_fighting())
        return notify_fail("战斗中不能睡觉！\n");   
    if ((time() - me->query("last_sleep")) < 90)
        return notify_fail("你刚睡过一觉, 先活动活动吧。\n");

    if (where->query("if_bed")) {
        write("你往被中一钻，开始睡觉。\n");
        write("不一会儿，你就进入了梦乡。\n");
        me->set("last_sleep",time());
        me->set_temp("block_msg/all",1);
        message_vision(HIY "$N往被中一钻，不一会便鼾声大作，进入了梦乡。\n" NOR,me);
    }
    else { 
        write("你就地一躺，开始睡觉。\n");
        write("不一会儿，你就进入了梦乡。\n");
        me->set("last_sleep",time());
        me->set_temp("block_msg/all",1);
        message_vision(HIY "$N就地一躺，不一会便鼾声大作，进入了梦乡。\n" NOR,me);
    }

    if (me->query_temp("ridee"))
        me->query_temp("ridee")->set_temp("rider", 0);
    me->set_temp("ridee",0);
    me->add_temp("apply/dodge", -me->query_temp("ride/dodge"));
    me->set_temp("ride/dodge", 0);
    me->disable_player("<睡梦中>");

    call_out("wakeup", random(45 - me->query("con")) + 10, me, where);
    return 1;
}

void wakeup(object me,object where)
{
    if (!me) return;

    me->set("sen", (int)me->query("max_sen"));
    if ((int)me->query("mana") < (int)me->query("max_mana"))
        me->set("mana", (int)me->query("max_mana"));

    me->enable_player();

    while (environment(me)->is_character())
        me->move(environment(environment(me)));

    if (random(5) == 1 && interactive(me)){
        me->set("dream_place", (string)environment(me));
        me->set_temp("block_msg/all", 0);
        me->move("/d/ourhome/honglou/kat");
    }
    else{
        message_vision(HIY "$N一觉醒来，精力充沛地活动了一下筋骨。\n" NOR,me);
        me->set_temp("block_msg/all", 0);
        write("你一觉醒来，只觉精力充沛。该活动一下了。\n");
    }
}

int help(object me)
{
    write(@HELP
指令格式 : sleep
 
顾名思义，这个指令是用来睡觉的。
HELP
    );
    return 1;
}
