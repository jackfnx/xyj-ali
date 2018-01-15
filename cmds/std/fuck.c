// ALI by NewX

// fuck.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object obj, old_target;

    if ( !wizardp(me) && environment(me)->query("no_fight") )
        return notify_fail("这里禁止战斗。\n");

    if (!arg || !objectp(obj = present(arg, environment(me))))
        return notify_fail("你想XX谁？\n");

    if ( !obj->is_character() )
        return notify_fail("看清楚一点，那并不是生物。\n");

    if ( obj->is_fucking(me) )
        return notify_fail("加油！加油！加油！\n");

    if (obj==me)
        return notify_fail("你不能fuck自己。\n");

    if (me->is_busy())
        return notify_fail("你现在正忙着呢。\n");

    if (!obj->query("can_speak"))
        return notify_fail("兽交？目前还不提供这种服务。\n");

    if (userp(obj))
        return notify_fail("想跟玩家xx？那是不可能的。\n");

    message_vision("\n$N对$n说道："
            + RANK_D->query_self(me)
            + me->name() + "，愿与"
            + RANK_D->query_respect(obj) + "同登极乐，不知"
            + RANK_D->query_respect(obj) + "是否愿意！\n\n", me, obj);

    if (!userp(obj)) {
        if (obj->query("sexuality") == "virgin") {
            if (obj->query("class") == "yaomo") {
                message_vision("$N哼了一声，对$n说："
                        + RANK_D->query_rude(me) + "！分明是想盗取"
                        + RANK_D->query_self_rude(obj) + "的"
                        + (obj->query("gender")=="男性" ? "真阳！" : "真阴！")
                        + RANK_D->query_self_rude(obj) + "饶不了你！\n",
                        obj, me);
            } else {
                message_vision("$N脸色大变，怒喝道："
                        + RANK_D->query_rude(me) + "！"
                        + RANK_D->query_self_rude(obj)
                        + "面前竟然说出如此下流言语，我看你活得不耐烦了！\n",
                        obj, me);
            }
            me->fuck_ob(obj);
            obj->kill_ob(me);
        } else if (obj->query("sexuality") == "carnality") {
            message_vision("$N笑道："
                    + RANK_D->query_self(obj)
                    + "求之不得！\n", obj);
            me->fuck_ob(obj);
            obj->fuck_ob(me);
        //} else if (obj->query("sexuality") == "pudency") {
        } else {
            message_vision("$N顿时脸上一红，不知该如何是好。\n", obj);
            tell_object(obj, HIM + me->name() + "盯着你发出一阵淫笑，显然没安什么好心！\n" NOR);
            me->fuck_ob(obj);
            obj->fight_ob(me);
        }
    }

    return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : fuck <人物>

HELP
    );
    return 1;
}
 
