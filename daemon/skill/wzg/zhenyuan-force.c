// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// zhenyuan-force.c  【镇元神功】
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) 
{
    if ((int)me->query_skill("force", 1) < 10)
//     || (int)me->query_skill("force", 1) <= (int)me->query_skill("zhenyuan-force", 1) )
        return notify_fail("你的内功修为还不够高深，无法学习镇元神功。\n");
    return 1;
}

int practice_skill(object me)
{
    return notify_fail("镇元神功只能向师父学，或是从运用(exert)中增加熟练度。\n");
}

string exert_function_file(string func)
{
    return CLASS_D("zhenyuan") + "/zhenyuan-force/" + func;
}

int help(object me)
{
    write(@HELP
〖镇元神功〗
道家的修身功夫乃传统的内丹之术，此术乃世间显传，各门各派都有
修习。然镇元子所传之内功心法却颇有独到之处，该法为五庄观弟子
独有，就连退出门派三星与八仙也承诺绝不对外泄露此术。该法本无
名，后以镇元子名讳记之，曰镇元神功。

① 自疗
　指令：exert heal
HELP);
    return 1;
}
