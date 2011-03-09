// ALi by NewX

void greeting_for_obstacle(object who)
{
    object me = this_object();
    
    if (!me->visible(who))
        return;
    if (me->is_fighting())
        return;
    
    if (who->query("obstacle/number") > 0) {
        remove_call_out("greeting_for_obstacle_callout");
        call_out("greeting_for_obstacle_callout", 1, me, who);
    }
}

void greeting_for_obstacle_callout(object me, object who)
{
    string str;
    object weapon = me->query_temp("weapon");
    
    if (environment(me)!=environment(who))
        return;

    if (weapon)
        str = "$N举起手中的"+weapon->query("name")+"向$n行礼：";
    else
        str = "$N举手向$n行礼：";
    str += RANK_D->query_respect(who)+"西行取经，威名亘古！\n";

    message_vision(str, me, who);
}

void greeting_for_quest(object who)
{
    object me = this_object();
    
    if (!me->visible(who))
        return;
    if (me->is_fighting())
        return;
    
    if (who->query("quest/reward") > 0) {
        remove_call_out("greeting_for_quest_callout");
        call_out("greeting_for_quest_callout", 1, me, who);
    }
}

void greeting_for_quest_callout(object me, object who)
{
    string str;
    
    if (environment(me)!=environment(who))
        return;

    str = "$N向$n一躬："+RANK_D->query_respect(who)+
        "仙体祥云笼罩，请速去拜见吾王太宗！\n";
    message_vision(str, me, who);
}