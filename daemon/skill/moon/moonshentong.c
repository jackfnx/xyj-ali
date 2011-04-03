// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// moonshentong.c 【太阴仙诀】
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("spells", 1) < 10
        || (int)me->query_skill("spells", 1) <=
            (int)me->query_skill("moonshentong", 1))
        return notify_fail("你的法术修为还不够高深，无法学习太阴仙诀。\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("girl") + "/moonshentong/" + spell;
}

int help(object me)
{
    write(@HELP
【太阴仙诀】
法术本就是月宫的特色，『月宫仙法』多是接引月华中的太阴之力伤
敌，令人防不胜防。
与妲己一战后，西王母更在『月宫仙法』中大量的引入了古墓因素，
使得月宫的法术水平更上了一层楼，将『月宫仙法』演变成了『太阴
仙诀』。
『太阴仙诀』的原理，同样也是更加强调施法者体内的真阴内元，靠
体内的阴元调动体外的太阴之力，从而使得法术更精准，更诡谲。
不过，引入古墓因素的代价就是使得原本强调神圣纯洁的月宫法术，
染上了一层古墓的淫媚色彩。对此，有些弟子颇有异议，可是在西王
母的强制推行下，月宫法术的改良还是推行了下去。

〖特殊法门〗
①  冷月神弓     cast bow
②  落日神箭     cast arrow on <object>
③  天兵护法     cast invocation on <object>
④  迷魂         cast mihun on <object>
⑤  回梦         cast huimeng on <object>
⑥  蚀月         cast shiyue on <object>
HELP);
    return 1;
}

