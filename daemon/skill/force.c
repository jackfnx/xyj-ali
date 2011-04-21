// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// force.c

#include <ansi.h>

inherit SKILL;

string name() { return "内功心法"; }

int valid_learn(object me) { return 1; }

string exert_function_file(string func)
{
        return "/daemon/class/force/" + func;
}


