// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// nine-turn.c
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me)
{
    string mark;
    if (!stringp(mark = me->query("mark/nine-turn"))) {
        if (random(me->query_kar()) > 20)
            mark = "true";
        else
            mark = "false";
        me->set("mark/nine-turn", mark);
    }
    if (mark == "true") return 1;
    else return notify_fail("修习九转玄功须有缘分，你与此术无缘，还是算了吧。\n");
}

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
九转玄功，乃三界第一妙术，夺天地之造化，妙用无穷。此术来历极
神秘，有说来自如来佛祖，有说来自太上老君，还有说此术就是菩提
祖师所创，莫衷一是。
修习此术须有缘分，若是无缘休想修得。

〖应用法门〗
① 自疗          exert heal
② 七十二变      exert seven-two(未实现)
HELP);
    return 1;
}