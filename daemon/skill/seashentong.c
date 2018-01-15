// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// seashentong.c 【碧海神通】
inherit SPELLS;

string name() { return "碧海神通"; }

int query_basic_limit() { return 10; }

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
    if (me->query("class") != "dragon")
        return notify_fail("你非龙族怎能学碧海神通？\n");
    return ::valid_learn(me);
}

string cast_spell_file(string spell)
{
    return CLASS_D("dragon") + "/seashentong/" + spell;
}

