// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat
// quest.c

inherit F_CLEAN_UP;

#include <ansi.h>
#include <dbase.h>
#include <origin.h>

void create()
{
        seteuid(getuid());
}

int quest_give (object me, object who, object ob)
{
   if (me->query("quest/pending/give/name") != who->query("name") ||
            me->query("quest/pending/give/id")   != who->query("id"))
     return 0;

   if (me->query("quest/pending/give/objectname") != ob->query("name") ||
            me->query("quest/pending/give/objectid") != ob->query("id"))
     return 0;

   me->set("quest/pending/give/done",1);
   return 1;
}

string quest_ask (object me, object who, string topic)
{

   if (me->query("quest/pending/ask/name") != who->query("name") ||
            me->query("quest/pending/ask/id")   != who->query("id"))
     return 0;
   
   if (me->query("quest/pending/ask/topic") != topic)
     return 0;

   me->set("quest/pending/ask/done",1);
   return me->query("quest/pending/ask/acknowledge");
}

void quest_kill (object me)
{
   object killer = me->query_temp("last_damage_from");

   if (! killer)
     return;

   if (killer->query("quest/pending/kill/name") != me->query("name") ||
            killer->query("quest/pending/kill/id")   != me->query("id"))
     return 0;
   
   killer->set("quest/pending/kill/done",1);
}

string check_quests_detail(object who, object checker)
{
    string name = checker == who ? "你" : who->query("name");
    string str = "";
    mapping mapp;

    if (who->query("quest") == 0) {
        str += (name+"没有解任何迷。\n");
        return str;
    }

    str += (name+"已经解了"+(who->query("quest/number"))+"个迷。\n");

    str += ("    食物："+"解了"+(who->query("quest/food/times"))+"次，"+
        "获得"+(who->query("quest/food/reward"))+"点品德。\n");
    str += ("    送物："+"解了"+(who->query("quest/give/times"))+"次，"+
        "获得"+(who->query("quest/give/reward"))+"点品德。\n");
    str += ("    拜贤："+"解了"+(who->query("quest/ask/times"))+"次，"+
        "获得"+(who->query("quest/ask/reward"))+"点品德。\n");
    str += ("    灭妖："+"解了"+(who->query("quest/kill/times"))+"次，"+
        "获得"+(who->query("quest/kill/reward"))+"点品德。\n");
    str += ("    武器："+"解了"+(who->query("quest/weapon/times"))+"次，"+
        "获得"+(who->query("quest/weapon/reward"))+"点品德。\n");
    str += ("    盔甲："+"解了"+(who->query("quest/armor/times"))+"次，"+
        "获得"+(who->query("quest/armor/reward"))+"点品德。\n");
    str += ("    衣物："+"解了"+(who->query("quest/cloth/times"))+"次，"+
        "获得"+(who->query("quest/cloth/reward"))+"点品德。\n");
    str += ("    首饰："+"解了"+(who->query("quest/wearing/times"))+"次，"+
        "获得"+(who->query("quest/wearing/reward"))+"点品德。\n");
    str += ("    家什："+"解了"+(who->query("quest/furniture/times"))+"次，"+
        "获得"+(who->query("quest/furniture/reward"))+"点品德。\n");
    str += ("\n");

    str += (name+"共获得：\n");
    str += ("    潜能："+(who->query("quest/gain/potential"))+"点。\n");
    str += ("    道行："+COMBAT_D->chinese_daoxing(who->query("quest/gain/combat_exp"))+"道行。\n");
    str += ("    技能：\n");
    mapp = who->query("quest/gain/skills");
    if (mapp) {
        string *my_keys = keys(mapp);
        int i = sizeof(my_keys);
        while (i--) {
            str += ("      "+SKILL_D(my_keys[i])->name()+(mapp[my_keys[i]])
                +"点。\n");
        }
    }
    str += ("    属性（临时改善）：\n");
    mapp = who->query("quest/gain/apply");
    if (mapp) {
        string *my_keys = keys(mapp);
        int i = sizeof(my_keys);
        while (i--) {
            str += ("      "+(my_keys[i])+(mapp[my_keys[i]])
                +"点。\n");
        }
    }
    str += ("    银子："+(who->query("quest/gain/silver"))+"两。\n");
    str += ("\n");

    str += (name+"刚刚完成的迷是：\n");
    if (who->query("quest/reason")) {
        str += ("  “"+who->query("quest/reason")+"……”");
        if (who->query("quest/reward")) {
            if (wizardp(checker)) 
                str += ("  即将有"+(who->query("quest/reward"))+"点奖励。\n");
            else  
                str += ("  即将有奖励。\n");
            }  
        else
            str += ("\n");
    }
    str += ("\n");

    str += (name+"还有如下几个正在解的迷：\n");
    if (mapp = who->query("quest/pending/food")) {
        str += ("  食物："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/give")) {
        str += ("  送物："+mapp["name"] + " " + mapp["objectname"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/ask")) {
        str += ("  拜贤："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/kill")) {
        str += ("  灭妖："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/weapon")) {
        str += ("  武器："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/armor")) {
        str += ("  盔甲："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/cloth")) {
        str += ("  衣物："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/wearing")) {
        str += ("  首饰："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    if (mapp = who->query("quest/pending/furniture")) {
        str += ("  家什："+mapp["name"]);
        if (wizardp(checker))
            str += (" 参考系数："+mapp["index"]+"/"+mapp["daoxing"]+"。\n");
        else 
            str += ("\n");
    }
    str += ("\n");

    if (!wizardp(checker))
        return str;

    str += (name+"解迷暂存使用统计：\n");
    if (mapp = who->query("quest/cache/food"))
        str += ("  食物："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/give"))
        str += ("  送物："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/ask"))
        str += ("  拜贤："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/kill"))
        str += ("  灭妖："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/weapon"))
        str += ("  武器："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/armor"))
        str += ("  盔甲："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/cloth"))
        str += ("  衣物："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/wearing"))
        str += ("  首饰："+(sizeof(mapp))+"。\n");
    if (mapp = who->query("quest/cache/furniture"))
        str += ("  家什："+(sizeof(mapp))+"。\n");
    str += ("\n");

    return str;
}
