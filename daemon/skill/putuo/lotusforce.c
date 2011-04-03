// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// lotusforce.c

inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }
int valid_learn(object me) { return 1;}

int practice_skill(object me)
{
    return notify_fail("莲台心法只能用学的，或是从运用(exert)中增加熟练度。\n");
}

string exert_function_file(string func)
{
    return CLASS_D("bonze") + "/lotusforce/" + func;
}

int help(object me)
{
    write(@HELP
【莲台心法】
佛家的内功心法

〖应用法门〗
①自疗：exert heal
②疗人：exert lifeheal on <target>

HELP);
    return 1;
}
