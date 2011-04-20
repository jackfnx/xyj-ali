// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// taiyi.c 【太乙仙法】
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("spells", 1) < 10 
    ||  (int)me->query_skill("spells", 1) <= (int)me->query_skill("taiyi", 1))
        return notify_fail("你的法术修为还不够高深，无法学习太乙仙法。\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("daxian") + "/taiyi/" + spell;
}

int help(object me)
{
    write(@HELP
【太乙仙法】
太乙仙法，乃镇元大仙与一群朋友共创而成，在三界内流传甚广。

〖应用法门〗
①  乾坤大袖     cast qiankun
②  太乙真火     cast zhenhuo
HELP);
    return 1;
}
