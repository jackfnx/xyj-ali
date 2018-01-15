// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// styx_water.c 冥河水

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
    int limit;

    limit = (me->query("con") + (int)me->query("max_force") / 50) * 2;

    if (living(me)) {
        if (duration > limit) {
            me->unconcious();
            return 0;
        }
        else {
            tell_object(me, "你觉得一阵眩晕，坏了，不该喝冥河水的！\n");
            message("vision", me->name() + "脸色苍白，似乎情况极为不妥。\n",
                environment(me), me);
            me->receive_damage("gin", 10);
        }
    }

    me->apply_condition("styx_water", duration - 1);
    if (!duration) return 0;
    return 1;
}
