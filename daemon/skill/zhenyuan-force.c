// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// zhenyuan-force.c  【镇元神功】
inherit FORCE;

string name() { return "镇元神功"; }

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) 
{
    if ((int)me->query_skill("force", 1) < 10)
//     || (int)me->query_skill("force", 1) <= (int)me->query_skill("zhenyuan-force", 1) )
        return notify_fail("你的内功修为还不够高深，无法学习镇元神功。\n");
    return 1;
}

string exert_function_file(string func)
{
    return CLASS_D("daxian") + "/zhenyuan-force/" + func;
}

