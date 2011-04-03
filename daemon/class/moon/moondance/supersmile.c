
#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
    object *ob;
    int i, skill, damage;
    if (me->query("gender")=="男性")
        return notify_fail("不是女人就不要瞎掺乎了。\n");
    if (!me->is_fighting())
        return notify_fail("不是在战斗中不要乱笑，小心误伤他人。\n");
    if ((int)me->query_skill("moondance", 1) < 60)
        return notify_fail("你的冷月凝香舞火候不够。\n");
    if ((int)me->query("sen") < 100)
        return notify_fail("你的精神太差，无法展现足够的魅力。\n");

    skill = me->query_skill("moondance",1)*2+me->query_per()*2;

    me->receive_damage("sen", 10);

    me->start_busy(random(4));
    tell_object(me, "你聚精会神开始施展『销魂一笑』。。。\n");
    message_vision(HIM "$N轻启朱唇，曼转秋波，嫣然一笑。。。。。\n" NOR, me);

    ob = all_inventory(environment(me));
    for (i=0; i<sizeof(ob); i++) {
        if (!living(ob[i]) || ob[i]==me 
        || ob[i]->query("race")!="人类" 
        || ob[i]->query("gender")=="女性")
            continue;
        if (skill/2 + random(skill/2) < (int)ob[i]->query_cps() * 2) {
            message_vision("$N无动于衷。。。\n",ob[i]);
            continue;
        }
        damage = skill - ((int)ob[i]->query_cps() * 2);
        if (damage > 0) {
            if (damage > ob[i]->query("sen")) {
                tell_object(ob[i], "你觉得心中一乱。。。。\n");
                tell_room(environment(me),ob[i]->query("name") +
                        "满脸通红，摇摇晃晃地向"+me->query("name") +
                        "走了几步，嘴唇动了动，却又不知说什么好。。。\n",
                    ob[i], ob[i]);
            }
            else {
                tell_object(ob[i], "你觉得脸上一热，心中小鹿乱撞，脑中一片空白，元神不稳。。\n");
                tell_room(environment(me),ob[i]->query("name") +
                        "满脸通红，有点神不守舍的样子。\n",
                    ob[i], ob[i]);  
            }
            ob[i]->receive_damage("sen", damage);
            if ((int)ob[i]->query_cps() * 2 < skill)
                ob[i]->receive_wound("sen", damage/2);
        }

        if (userp(ob[i])) ob[i]->fight_ob(me);
        else if(!ob[i]->is_killing(me)) ob[i]->kill_ob(me);
    }

    return 1;
}
