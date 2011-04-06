// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// rootshentong.c 【天地灵根大法】
// 镇元子的本命神通，非天地灵根不能修炼

inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    return notify_fail("你没有天地灵根的本质，无法修炼『天地灵根大法』。\n");
}

string cast_spell_file(string spell)
{
    return CLASS_D("zhenyuan") + "/rootshentong/" + spell;
}

int help(object me)
{
    write(@HELP
〖天地灵根大法〗
镇元子的本命神通，非天地灵根不能修炼

〖特殊法门〗
①  乾坤大袖：      cast qiankun
HELP);
    return 1;
}
