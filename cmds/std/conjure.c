// conjure.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string magic, mgc, trg;
    object target;

    seteuid(getuid());

    if (me->is_busy())
        return notify_fail("( 你上一个动作还没有完成，不能施展神通。)\n");

    if (!wizardp(me) && environment(me)->query("no_magic"))
        return notify_fail("这里无法使用神通。\n");

    if (!arg) return notify_fail("指令格式：conjure <神通> [on <目标>]\n");
    if (sscanf(arg, "%s on %s", mgc, trg) == 2) {
        target = present(trg, environment(me));
        if (!target) target = present(trg, me);
        if (!target) return notify_fail("这里没有 " + trg + "。\n");
        
        if (!"/adm/daemons/tempd"->valid_kill(me, target)) return 0;
        if (userp(me) && userp(target) && target->query_temp("netdead"))
            return notify_fail("对方正在断线中，不能对其施法。\n");
    } else {
        mgc = arg;
        target = 0;
    }

    mgc = replace_string(mgc, " ", "_");

    if (stringp(magic = me->query_skill_mapped("magic"))) {
        notify_fail("你所学的神通中没有这种功能。\n");
        if (!(int)SKILL_D(magic)->conjure_magic(me, mgc, target))
            return (int)SKILL_D("magic")->conjure_magic(me, mgc, target);
        return 1;
    }

    return notify_fail("你请先用 enable 指令选择你要使用的神通系。\n");
}

int help (object me)
{
    write(@HELP
指令格式：conjure <神通名称> [on <施展对象>]

施展神通，你必需要指定<神通名称>，<施展对象>则可有可无。
在你使用某一个神通之前，你必须先用 enable 指令来指定你要使用的神通系。

注：如果你改变自己的神通系，你原本蓄积的真元并不能直接转换过去，必须
    从 0 开始。
HELP
    );
    return 1;
}
