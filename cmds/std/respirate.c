// respirate.c

#include <skill.h>

inherit F_CLEAN_UP;

int finish(object me, int gin_cost);

int main(object me, string arg)
{
    int gin_cost, busy_time;

    seteuid(getuid());

    if (environment(me)->query("no_fight")
    ||  environment(me)->query("no_magic"))
        return notify_fail("安全区内禁止练功。\n");
    if (me->is_busy() || me->query_temp("pending/exercising"))
        return notify_fail("你上一个动作还没有完成，不能修行。\n");
    if (me->is_fighting())
        return notify_fail("战斗也是一种修行，但不能和真元的积累同时进行。\n");
    if (!arg || !sscanf(arg, "%d", gin_cost))
        return notify_fail("你要转化多少精元？\n");
    if (gin_cost < 10) return notify_fail("你最少要花 10 点「精」才能吐纳。\n");
    if ((int)me->query("gin") < gin_cost)
        return notify_fail("你的精元不足，如果强行转化真元，会一命呜呼的！\n");
    if ((int)me->query("kee") * 100 / (int)me->query("max_kee") < 70)
        return notify_fail("你现在身体状况太差了，无法集中精神！\n");
    if ((int)me->query("sen") * 100 / (int)me->query("max_sen") < 70)
        return notify_fail("你现在精神状况太差了，无法控制自己的心灵！\n");

    write("你闭上眼睛，平心静气，试图将体内的精元转化为真元。\n");
    me->receive_damage("gin", gin_cost);

    busy_time = random(1 + gin_cost / 20) + 3;
    me->start_busy(busy_time);

    call_out("finish", busy_time+1, me, gin_cost);
    return 1;
}

int finish(object me, int gin_cost)
{
    int atman_gain;

    // This function ranged from 1 to 15 when gin_cost = 30
    atman_gain = gin_cost * ((int)me->query_skill("magic") / 10
        + (int)me->query_spi()/2 + (int)me->query_con()/2) / 30;
    atman_gain = atman_gain + random(atman_gain);

    if (atman_gain < 1) {
        tell_object(me, "但是你一不小心竟然睡着了。\n");
        me->start_busy(1);
        return 1;
    }

    me->add("atman", atman_gain);
    tell_object(me, "你吐纳完毕，睁开眼，缓缓站了起来。\n");

    if ((int)me->query("atman") > (int)me->query("max_atman") * 2) {
        if ((int)me->query("max_atman") >= (int)me->query_skill("magic") * 10) {
            tell_object(me, "你忽然觉得一阵气闷恶心，仿佛要吐出来一样，似乎真元的积累已经遇到了瓶颈。\n");
        } else {
            tell_object(me, "你的真元提高了！\n");
            me->add("max_atman", 1);
        }
        me->set("atman", me->query("max_atman"));
    }

    me->start_busy(1);
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : respirate|tuna [<耗费「精」的量，预设值 30>]

吐纳修行，利用「炼精化气，炼气化神，炼神还虚」的方法将你的精元
转变成真元。

请参考 help stats
HELP
    );
    return 1;
}
