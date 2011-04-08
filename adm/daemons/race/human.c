// ALI by NewX

// human.c

// A normal human is at least 40 kg weight
#define BASE_WEIGHT 40000

inherit F_DBASE;

mapping *combat_action = ({
    ([   "action":     "$N挥拳攻击$n的$l",
     "damage_type":   "瘀伤",
     ]),
    ([   "action":     "$N往$n的$l一抓",
     "damage_type":   "抓伤",
     ]),
    ([   "action":     "$N往$n的$l狠狠地踢了一脚",
     "damage_type":   "瘀伤",
     ]),
    ([   "action":     "$N提起拳头往$n的$l捶去",
     "damage_type":   "砸伤",
     ]),
    ([   "action":     "$N对准$n的$l用力挥出一拳",
     "damage_type":   "瘀伤",
     ]),
});

mapping *sex_action = ({
    ([
     "action": "$N轻轻抚摸$n的$s。",
     "limb": "all",
     "enjoy": 2,
     "self_enjoy": 1,
     "cost": 1,
     ]),
    ([
     "action": "$N轻轻舔了一口$n的$s。",
     "limb": "all",
     "enjoy": 2,
     "self_enjoy": 1,
     "cost": 1,
     ]),
    ([
     "action": "$N伸出手指，抹向了$n的$l。",
     "limb": "pussy",
     "min_enjoy": 50,
     "effect": "抹到了满手的蜜汁。",
     "enjoy": 4,
     "self_enjoy": 2,
     "cost": 1,
     ]),
    ([
     "action": "$N一把抓住了$n的$b。",
     "limb": "breast",
     "min_enjoy": 80,
     "effect": "竟挤出了大量香甜的乳汁。",
     "enjoy": 8,
     "self_enjoy": 5,
     "cost": 2,
     ]),
});

mapping *sex_fuck_action = ({
    ([
     "action": "$N用出九浅一深之法，将$L在$n的$l里慢慢的磨蹭，直将$n痒得心浮气躁，淫水狂喷。\n",
     "enjoy": 30,
     "self_enjoy": 3,
     ]),
    ([
     "action": "$N屏住一口气，将$L抵在$n的花心上，疯狂的狂抽猛插，插得$n直翻白眼，爽得飞到了天上去了。\n",
     "enjoy": 50,
     "self_enjoy": 10,
     ]),
});

void create()
{
    seteuid(getuid());
}

void setup_human(object ob)
{
    mapping my;

    my = ob->query_entire_dbase();

    ob->set("default_actions", (: call_other, __FILE__, "query_action" :));
    ob->set("default_sex_actions", (: call_other, __FILE__, "query_sex_action" :));
    ob->set("default_fuck_actions", (: call_other, __FILE__, "query_fuck_action" :));

    if ( undefinedp(my["age"]) ) my["age"] = random(30) + 15;

    if ( undefinedp(my["str"]) ) my["str"] = random(21) + 10;
    if ( undefinedp(my["dex"]) ) my["dex"] = random(21) + 10;
    if ( undefinedp(my["int"]) ) my["int"] = random(21) + 10;
    if ( undefinedp(my["spi"]) ) my["spi"] = random(21) + 10;
    if ( undefinedp(my["cps"]) ) my["cps"] = random(21) + 10;
    if ( undefinedp(my["per"]) ) my["per"] = random(21) + 10;
    if ( undefinedp(my["con"]) ) my["con"] = random(21) + 10;
    if ( undefinedp(my["kar"]) ) my["kar"] = random(21) + 10;
    if ( undefinedp(my["rig"]) ) my["rig"] = random(21) + 10;
    if ( undefinedp(my["sns"]) ) my["sns"] = random(21) + 10;
    if ( undefinedp(my["cor"]) ) my["cor"] = random(21) + 10;
    if ( undefinedp(my["met"]) ) my["met"] = random(21) + 10;

    if ( userp(ob) || undefinedp(my["max_kee"]) ) {
        if ( my["age"] <= 14 ) my["max_kee"] = 100;
        else if ( my["age"] <= 30 )
            my["max_kee"] = 100 + (my["age"] - 14) * my["con"];
        else my["max_kee"] = 100 + 16 * my["con"];

        if ( my["max_force"] > 0 ) my["max_kee"] += my["max_force"] / 4;

        if ( my["max_kee"] < 1 ) my["max_kee"] = 1; //mon 1/28/98
    }

    if ( userp(ob) || undefinedp(my["max_sen"]) ) {
        if ( my["age"] <= 14 ) my["max_sen"] = 100;
        else if ( my["age"] <= 30 )
            my["max_sen"] = 100 + (my["age"] - 14) * my["spi"];
        else if ( my["age"] <= 40 ) my["max_sen"] = 100 + 16 * my["spi"];
        else {
            //when age>40, max_sen will drop...but if you have
            //"always_young"(defined in "look.c"), only drop 
            //to atmost your "faked_age"...weiqi,062897.
            if ( my["always_young"] ) {
                if ( my["fake_age"] <= 40 )
                    my["max_sen"] = 100 + 16 * my["spi"];
                else
                    my["max_sen"] = 100 +16 * my["spi"] - (my["fake_age"] - 40) * 5;
            } else
                my["max_sen"] = 100 +16 * my["spi"] - (my["age"] - 40) * 5;
        }

        if ( my["max_mana"] > 0 ) my["max_sen"] += my["max_mana"]*2 / 5;
        //here we make mana very useful, so set divided by 2.5, instead of 4.
        if ( my["max_sen"] < 1 ) my["max_sen"] = 1; //mon 1/28/98
    }

    if ( userp(ob) || undefinedp(my["max_gin"]) ) {
        if ( my["age"] <= 14 ) my["max_gin"] = 100;
        else if ( my["age"] <= 30 )
            my["max_gin"] = 100 + (my["age"] - 14) * my["spi"];
        else if ( my["age"] <= 50 ) my["max_gin"] = 100 + 16 * my["spi"];
        else my["max_gin"] = 100 + 16 * my["spi"]  - (my["age"] - 50) * 5;

        if ( my["max_atman"] > 1000 ) my["max_gin"] += 250;
        else if ( my["max_atman"] > 0 ) my["max_gin"] += my["max_atman"] / 4;

        if ( my["max_gin"] < 1 ) my["max_gin"] = 1; //mon 1/28/98
   }

    if ( undefinedp(my["unit"])) my["unit"]="位";
    if ( undefinedp(my["gender"])) my["gender"]="男性";
    if ( undefinedp(my["can_speak"])) my["can_speak"]=1;
    if ( undefinedp(my["attitude"])) my["attitude"]="peaceful";
    if ( undefinedp(my["sexuality"])) my["sexuality"]="pudency";
    if ( undefinedp(my["limbs"])) my["limbs"]=({
        "头部",   "颈部",   "胸口",   "后心",   "左肩",   "右肩",   "左臂",
        "右臂",   "左手",   "右手",   "腰间",   "小腹",   "左腿",   "右腿",
        "左脚",   "右脚"
        }) ;

//   ob->set_default_object(__FILE__);
    if ( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action()
{
    return combat_action[random(sizeof(combat_action))];
}

mapping query_sex_action(object me)
{
    object ob;
    int female = 0;
    mapping act;
    if (objectp(me->query_temp("sex/fuck_ob"))) {
        ob = me->query_temp("sex/fuck_ob");
        female = ob->query("gender") == "女性";
    }
    else if (objectp(me->query_temp("sex/makelove_ob"))) {
        ob = me->query_temp("sex/makelove_ob");
        female = ob->query("gender") == "女性";
    }
    for (act = sex_action[random(sizeof(sex_action))];
        !female && (act["limb"]=="pussy"||act["limb"]=="breast");
        act = sex_action[random(sizeof(sex_action))])
        ;
    return act;
}

mapping query_fuck_action(object me)
{
    if (random(2)) return query_sex_action(me);
    else return sex_fuck_action[random(sizeof(sex_fuck_action))];
}
