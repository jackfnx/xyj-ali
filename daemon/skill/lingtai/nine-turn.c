// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// nine-turn.c
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
    return notify_fail("九转玄功只能用学的，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
    return CLASS_D("puti") + "/nine-turn/" + func;
}

int help(object me)
{
    write(@HELP
【九转玄功】
九转玄功，乃修身功法之极致，夺天地之造化，妙用无穷。

〖应用法门〗
① 自疗    exert heal
HELP);
    return 1;
}