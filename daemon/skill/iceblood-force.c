
// iceblood-force.c  ¡¾±ù¹ÈÄıÑª¹¦¡¿
inherit FORCE;

string name() { return "±ù¹ÈÄıÑª¹¦"; }

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

string exert_function_file(string func)
{
    return CLASS_D("dapeng") + "/iceblood-force/" + func;
}

