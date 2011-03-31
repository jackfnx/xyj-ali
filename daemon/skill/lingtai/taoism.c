// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// taoism
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("spells", 1) < 20)
        return notify_fail("道可道，非常道，你的法术修为还不够高深。\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("puti") + "/taoism/" + spell;
}

int help(object me)
{
    write(@HELP
【道】
道可道，非常道。
太上曾有五千言传世，菩提祖师所传之道即以此为基础。

〖特殊攻击〗
①  五雷咒       cast thunder on <object>
②  苍灵箭       cast light on <object>
③  分身术       cast fenshen
④  定身法       cast dingshen on <object>
⑤  天兵护法     cast invocation
HELP);
    return 1;
}