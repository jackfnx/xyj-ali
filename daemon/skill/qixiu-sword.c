// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// qixiu-sword.c, 【七修剑】
// edited 4-16-97 pickle

/*
七修剑    dodge  5    parry  -10    damage  25
七修剑为拼命剑法，只求伤敌，不顾自身安危，故其
突防之力颇强。然则往往乱打一气，敌已逃而不觉。
*/

// 五马分尸，六亲不认，七窍生烟，
// 八方风雨，九死一生，十面埋伏

inherit SKILL;

void set_busy();

string name() { return "七修剑"; }

mapping *action = ({
    ([
      "action":
"$N手腕一抖，$w剑尖化为五道白光，分别向$n的咽喉、左右肩、和左右脚腕疾刺",
      "dodge":     0,
      "parry":           0,
      "damage":     20,
      "damage_type":   "刺伤",
      "name":     "「五马分尸」",
      ]),
    ([
      "action":
"$N关节僵硬，手中$w如一根树干一般横竖乱扫。\n"
"$n识得这招「六亲不认」的威力，连忙躲避不迭",
      "dodge":     10,
      "parry":     -20,
      "damage":     30,
      "damage_type":   "割伤",
      "name":     "「六亲不认」",
      ]),
    ([
      "action":
"$N纵身跃起，手中$w带起万道银光，向$n的面门点去。\n"
"这招「七窍生烟」果然把$n逼得手忙脚乱",
      "dodge":     5,
      "parry":          -10,
      "damage":     20,
      "damage_type":   "刺伤",
      "name":      "「七窍生烟」",
//      "post_action":   (:set_busy:),
      ]),
   
    ([
      "action":
"$N奋不顾身，手中$w如狂风暴雨般向$n乱劈！\n"
"这招「八方风雨」虽然露出若干空门，但$n也不敢不顾自身安危而贸然进攻",
      "dodge":     5,
      "parry":           -5,
      "damage":     30,
      "damage_type":   "刺伤",
      "name":      "「八方风雨」",
//      "post_action":   (:set_busy:),
      ]),
    ([
      "action":
"$N连人带剑猛扑向$n的$l。若是这招「九死一生」\n"
"击不中$n，$N本人就空门大开，任人宰割了",
      "dodge":     10,
      "parry":           -10,
      "damage":     35,
      "damage_type":   "刺伤",
      "name":      "「九死一生」",
//      "post_action":   (:set_busy:),
      ]),
    ([
      "action":
"$N身随剑走，迅速无伦地在$n周围兜圈。\n"
"$n只见周围无数人影，随时都有可能有一柄$w从意想不到的\n"
"位置刺来，实在是危机重重",
      "dodge":          0,
      "parry":     -15,
      "damage":     15,
      "damage_type":   "刺伤",
      "name":      "「十面埋伏」",
      ]),
  ([
     "action":
MAG"$N身化万千,手中的$w"+MAG"亦幻出千条黑影,直罩$n全身,使$n难辨直假!!\n"
"$n正手忙脚乱间,一道墨光无声无息地直取脑后玉枕穴,$n却木然不觉!"NOR,
     "dodge":   -100,
     "parry":   -100,
     "damage":  120,
     "force":   250,
     "damage_type": "刺伤",
     "name": "「妖雾冲天」",
      ]),
});

int valid_learn(object me)
{
    object ob;
    
    if (me->query("family/family_name") != "陷空山无底洞")
        return notify_fail("你还未习惯血腥，无法学七修剑。\n");
    if ((int)me->query("max_force") < 100)
        return notify_fail("你的真气不足，难以领悟剑法的精妙之处。\n");
    if (!(ob = me->query_temp("weapon"))
    ||  (string)ob->query("skill_type") != "sword")
        return notify_fail("你必须先找一把剑才能练剑法。\n");
    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    int i = me->query_temp("QXJ_perform");
    if (i) return action[i - 1];
    return action[random(sizeof(action) - 1)];
}

int practice_skill(object me)
{
    if (me->query("family/family_name") != "陷空山无底洞")
        return notify_fail("你还未习惯血腥，无法练七修剑。\n");
    if ((int)me->query("kee") < 30)
        return notify_fail("你的气太低，再练下去会有危险的！\n");
    if ((int)me->query("force") < 5)
        return notify_fail("你的内力不够，没有办法运用七修剑。\n");
    me->receive_damage("kee", 30);
    me->add("force", -5);
    write("你按著所学练了一遍七修剑。\n");
    return 1;
}
void set_busy()
{
    object me=this_player();
    me->start_busy(1);
}

string perform_action_file(string action)
{
    return CLASS_D("yushu") + "/qixiu-sword/" + action;
}
