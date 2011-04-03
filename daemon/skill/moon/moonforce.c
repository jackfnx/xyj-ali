// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// moonforce.c  【太阴心经】
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
    return notify_fail("太阴心经只能向师父学，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
    return CLASS_D("girl") + "/moonforce/" + func;
}

int help(object me)
{
    write(@HELP
【太阴心经】
月亮，又名太阴星，乃太阴之气凝聚而成，无时无刻不在散发着太阴
月华。月宫一切武学法术的基础，便是这太阴月华。
月宫原本的内功心法名为『圆月心法』，只是一套采集月华，固本培
元的心诀，颇为粗鄙。
与妲己一战后，西王母将『圆月心法』大幅改良成了『太阴心经』，
顿时威力大增。
太阴心经的原理，乃是培植女性丹田之内的真阴内元。以体内的太阴
精华，激发体外的太阴精华。修炼有成后，可以在丹田中凝结成一颗
『太阴月轮』，使得体内产生生生不息的内力。

〖特殊法门〗
①  自疗  exert heal
②  采月  exert moon(未实现)
③  映日  exert sun
HELP);
    return 1;
}

