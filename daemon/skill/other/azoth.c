// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// azoth.c
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
    return notify_fail("金丹大道只能用学的，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
    return CLASS_D("other") + "/azoth/" + func;
}

int help(object me)
{
    write(@HELP
【金丹大道】
丹道，乃道家修身之基础，为时间显传，三界之内修习者无数。

〖应用法门〗
① 自疗    exert heal
HELP);
    return 1;
}