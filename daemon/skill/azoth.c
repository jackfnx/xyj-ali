// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// azoth.c
inherit FORCE;

string name() { return "内丹术"; }

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

string exert_function_file(string func)
{
    return CLASS_D("xian") + "/azoth/" + func;
}

