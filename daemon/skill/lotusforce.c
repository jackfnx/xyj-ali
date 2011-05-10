// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// lotusforce.c

inherit FORCE;

string name() { return "莲台心法"; }

int valid_enable(string usage) { return usage=="force"; }
int valid_learn(object me) { return 1;}

string exert_function_file(string func)
{
    return CLASS_D("bonze") + "/lotusforce/" + func;
}

