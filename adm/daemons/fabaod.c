// ALI by NewX

// /adm/daemons/fabaod.c

#include <weapon.h>
#include <armor.h>
#include <ansi.h>
#include <login.h>

inherit F_DBASE;

#define MAX_WEAPON  1
#define MAX_ARMOR   4

mapping upgrades = ([
    "weapon" : ([
        "damage" : ({
            ([ "val" : 4, "min_exp" : 100000, "min_force": 500, "force" : 10, "exp" : 200 ]),
            ([ "val" : 6, "min_exp" : 500000, "min_force": 1000, "force" : 20, "exp" : 2000 ]),
            ([ "val" : 6, "min_exp" : 1000000, "min_force": 1500, "force" : 30, "exp" : 4000 ]),
            ([ "val" : 6, "min_exp" : 1500000, "min_force": 2000, "force" : 40, "exp" : 10000 ]),
            ([ "val" : 6, "min_exp" : 3000000, "min_force": 4000, "force" : 50, "exp" : 20000 ]),
            ([ "val" : 0, "min_exp" : 9000000, "min_force": 8000, "force" : 0, "exp" : 0 ])
        })
    ]),
    "armor" : ([
        "armor" : ({
            ([ "val" : 1, "min_exp" : 100000, "min_force": 500, "force" : 10, "exp" : 200 ]),
            ([ "val" : 2, "min_exp" : 500000, "min_force": 1000, "force" : 20, "exp" : 1000 ]),
            ([ "val" : 3, "min_exp" : 1000000, "min_force": 1500, "force" : 30, "exp" : 4000 ]),
            ([ "val" : 4, "min_exp" : 1500000, "min_force": 2000, "force" : 40, "exp" : 10000 ]),
            ([ "val" : 5, "min_exp" : 3000000, "min_force": 4000, "force" : 50, "exp" : 20000 ]),
            ([ "val" : 0, "min_exp" : 9000000, "min_force": 8000, "force" : 0, "exp" : 0 ])
        }),
        "dodge" : ({
            ([ "val" : 1, "min_exp" : 200000, "exp" : 1000 ]),
            ([ "val" : 1, "min_exp" : 500000, "exp" : 4000 ]),
            ([ "val" : 2, "min_exp" : 1000000, "exp" : 10000 ]),
            ([ "val" : 2, "min_exp" : 1500000, "exp" : 20000 ]),
            ([ "val" : 3, "min_exp" : 3000000, "exp" : 40000 ]),
            ([ "val" : 0, "min_exp" : 9000000, "exp" : 0 ])
        }),
        "force" : ({
            ([ "val" : 1, "min_exp" : 200000, "min_force": 500, "force" : 10, "exp" : 1000 ]),
            ([ "val" : 1, "min_exp" : 500000, "min_force": 1000, "force" : 20, "exp" : 4000 ]),
            ([ "val" : 2, "min_exp" : 1000000, "min_force": 1500, "force" : 30, "exp" : 10000 ]),
            ([ "val" : 2, "min_exp" : 1500000, "min_force": 2000, "force" : 40, "exp" : 20000 ]),
            ([ "val" : 3, "min_exp" : 3000000, "min_force": 4000, "force" : 50, "exp" : 40000 ]),
            ([ "val" : 0, "min_exp" : 9000000, "min_force": 8000, "force" : 0, "exp" : 0 ])
        }),
        "armor_vs_force" : ({
            ([ "val" : 10, "min_exp" : 100000, "min_force": 500, "force" : 20 ]),
            ([ "val" : 20, "min_exp" : 500000, "min_force": 1000, "force" : 30 ]),
            ([ "val" : 30, "min_exp" : 1000000, "min_force": 1500, "force" : 50 ]),
            ([ "val" : 40, "min_exp" : 1500000, "min_force": 2000, "force" : 80 ]),
            ([ "val" : 50, "min_exp" : 3000000, "min_force": 4000, "force" : 200 ]),
            ([ "val" : 0, "min_exp" : 9000000, "min_force": 8000, "force" : 0 ])
        }),
        "spells" : ({
            ([ "val" : 1, "min_exp" : 200000, "min_mana": 500, "mana" : 10, "exp" : 1000 ]),
            ([ "val" : 1, "min_exp" : 500000, "min_mana": 1000, "mana" : 20, "exp" : 4000 ]),
            ([ "val" : 2, "min_exp" : 1000000, "min_mana": 1500, "mana" : 30, "exp" : 10000 ]),
            ([ "val" : 2, "min_exp" : 1500000, "min_mana": 2000, "mana" : 40, "exp" : 20000 ]),
            ([ "val" : 3, "min_exp" : 3000000, "min_mana": 4000, "mana" : 50, "exp" : 40000 ]),
            ([ "val" : 0, "min_exp" : 9000000, "min_mana": 8000, "mana" : 0, "exp" : 0 ])
        }),
        "armor_vs_spells" : ({
            ([ "val" : 10, "min_exp" : 200000, "min_mana": 500, "mana" : 10 ]),
            ([ "val" : 20, "min_exp" : 500000, "min_mana": 1000, "mana" : 30 ]),
            ([ "val" : 30, "min_exp" : 1000000, "min_mana": 1500, "mana" : 60 ]),
            ([ "val" : 40, "min_exp" : 1500000, "min_mana": 2000, "mana" : 100 ]),
            ([ "val" : 50, "min_exp" : 3000000, "min_mana": 4000, "mana" : 250 ]),
            ([ "val" : 0, "min_exp" : 9000000, "min_mana": 8000, "mana" : 0 ])
        })
    ])
]);

mapping props = ([
    "weapon" : ({
        ([ "id": "damage", "name" : HIG "伤 害 力" NOR, "init_val" : 10 ])
    }),
    "armor" : ({
        ([ "id" : "armor", "name" : HIG "防 护 力" NOR, "init_val" : 5 ]),
        ([ "id" : "dodge", "name" : HIY "轻功加成" NOR ]),
        ([ "id" : "force", "name" : HIB "内功加成" NOR ]),
        ([ "id" : "armor_vs_force", "name" : HIM "内力防护" NOR ]),
        ([ "id" : "spells", "name" : HIC "法术加成" NOR ]),
        ([ "id" : "armor_vs_spells", "name" : HIW "法力防护" NOR ]),
    })
]);

mapping subtypes = ([
    "weapon" : ({
        ([ "id" : "axe", "name" : "斧", "default_file" : "axe/bigaxe" ]),
        ([ "id" : "blade", "name" : "刀", "default_file" : "blade/blade" ]),
        ([ "id" : "fork", "name" : "叉", "default_file" : "fork/gangcha" ]),
        ([ "id" : "hammer", "name" : "锤", "default_file" : "hammer/hammer" ]),
        ([ "id" : "mace", "name" : "锏", "default_file" : "mace/ironmace" ]),
        ([ "id" : "spear", "name" : "枪", "default_file" : "spear/gangqiang" ]),
        ([ "id" : "staff", "name" : "杖", "default_file" : "staff/muzhang" ]),
        ([ "id" : "stick", "name" : "棍", "default_file" : "stick/qimeigun" ]),
        ([ "id" : "sword", "name" : "剑", "default_file" : "sword/changjian" ]),
        ([ "id" : "whip", "name" : "鞭", "default_file" : "whip/pibian" ])
    }),
    "armor" : ({
        ([ "id" : "armor", "name" : "护甲", "default_file" : "armor/tenjia" ]),
        ([ "id" : "cloth", "name" : "衣服", "default_file" : "cloth/linen" ]),
        ([ "id" : "head", "name" : "帽子", "default_file" : "cloth/hat" ]),
        ([ "id" : "waist", "name" : "腰带", "default_file" : "cloth/belt" ]),
        ([ "id" : "surcoat", "name" : "披风", "default_file" : "cloth/surcoat" ]),
        ([ "id" : "wrists", "name" : "护腕", "default_file" : "cloth/wrists" ]),
        ([ "id" : "hands", "name" : "手套", "default_file" : "cloth/gloves" ]),
        ([ "id" : "boots", "name" : "靴子", "default_file" : "cloth/buxie" ]),
        ([ "id" : "shield", "name" : "盾牌", "default_file" : "armor/niupi" ]),
        ([ "id" : "finger", "name" : "戒指", "default_file" : "cloth/ring" ]),
        ([ "id" : "neck", "name" : "项链", "default_file" : "cloth/necklece" ]),
    })
]);

mapping minerals = ([ "wuse tu" : "五色土", "jiuyin xuantie" : "九阴玄铁", "wuse tu" : "六阳钨钢" ]);

mapping elements = ([ "gold" : "金", "wood" : "木", "water" : "水", "fire" : "火", "soil" : "土" ]);

mapping formulas = ([
    "" : ([
        "" : ([ "wuse tu" : 1, "jiuyin xuantie": 1, "liuyang wugang" : 1 ]),
    ]),
    "weapon" : ([
        "damage" : ([ ])
    ]),
    "armor" : ([
        "armor" : ([ ]),
        "dodge" : ([ ]),
        "force" : ([ ]),
        "armor_vs_force" : ([ ]),
        "spells" : ([ ]),
        "armor_vs_spells" : ([ ])
    ])
]);

string display_stars(int stars);

void get_fabao_type(object ob, object smelter, string arg);
void get_fabao_subtype(object ob, object smelter, string arg);
void get_fabao_id(object ob, object smelter, string arg);
void get_fabao_name(object ob, object smelter, string arg);
void get_fabao_desc(object ob, object smelter, string arg);
void get_fabao_unit(object ob, object smelter, string arg);

object new_fabao_ob(object ob);

void build_weapon(object ob);
void build_armor(object ob);
void setup_prop(object ob, string type);

int count_fabao(object me, string type);
int max_series_no(object me);

mixed query_prop(string fabao_type, string prop);
string show_subtypes(string fabao_type);

void create()
{
    seteuid(getuid());
    set("channel_id", "法宝精灵");
    set("id", "fabaod");
}

void show_upgrade_cost(object ob, object me)
{
    string fabao_type;
    string str;
    
    if (!objectp(ob)) {
        write("『法宝炼制指南』\n");
        write("\n");
        write("初始炼制：\n");
        write("材料：五色土，九阴玄铁，六阳钨钢\n");
        write("要求：道行大于20年，内力法力大于300\n");
        write("花费：内力50点，法力50点\n");
        return;
    }
    
    fabao_type = ob->query("fabao_type");
    
    str = ob->name() + "\n" + ob->long() + "\n";
    foreach (mapping prop in props[fabao_type]) {
        int stars = ob->query("stars/" + prop["id"]);
        int upgraded = ob->query("upgraded/" + prop["id"]);
        if (stars == 5)
            str += (prop["name"] + "(" + prop["id"] + ")升级条件：\n"HIC"    已经达到了顶级。\n"NOR);
        else {
            mapping *costs = upgrades[fabao_type][prop["id"]];
            int min_exp = costs[stars]["min_exp"]
                    + (costs[stars + 1]["min_exp"] - costs[stars]["min_exp"]) * upgraded / 5;
            int min_force = costs[stars]["min_force"];
            int min_mana = costs[stars]["min_mana"];
            int force = costs[stars]["force"];
            int mana = costs[stars]["mana"];
            int exp = costs[stars]["exp"];
            
            str += (prop["name"] + "(" + prop["id"] + ")升级条件：");
            if (min_exp <= me->query("combat_exp")
            &&  min_force <= me->query("max_force")
            &&  min_mana <= me->query("max_mana"))
                str += (HIY"『可以升级』"NOR);
            str += ("\n");
            if (min_exp > 0) str += ("    道行" + COMBAT_D->chinese_daoxing(min_exp) + "以上\n");
            if (min_force > 0) str += ("    内力" + chinese_number(min_force) + "以上\n");
            if (min_mana > 0) str += ("    法力" + chinese_number(min_mana) + "以上\n");
            if (force > 0) str += ("    消耗最大内力" + chinese_number(force) + "点\n");
            if (mana > 0) str += ("    消耗最大法力" + chinese_number(mana) + "点\n");
            if (exp > 0) str += ("    消耗道行" + COMBAT_D->chinese_daoxing(exp) + "\n");
        }
    }
    {
        int f_stars = ob->query("stars/" + props[fabao_type][0]["id"]);
        string *comp = ({}), *zero = ({});
        foreach (string elem in keys(elements)) {
            int points = ob->query(ob->query("fabao_type") + "_prop/" + elem);
            if (points >= 100)
                comp += ({ elem });
            else if (points <= 0)
                zero += ({ elem });
        }
        str += ("五行属性：\n");
        foreach (string elem in keys(elements)) {
            str += ("    " + elements[elem] + "： ");
            if (member_array(elem, comp) != -1)
                str += (HIY"圆满"NOR);
            else if (member_array(elem, zero) != -1) {
                if (sizeof(comp) < f_stars
                &&  (sizeof(comp) + sizeof(zero)) == 5)
                    str += (HIG"可升级"NOR);
                else
                    str += (CYN"无"NOR);
            }
            else
                str += (HIR"升级中"NOR);
            str += ("\n");
        }
        str += "\n";
        str += "关于五行属性的强化(enhance)，需要加入五行之精。\n";
        str += "五行之精包括：\n";
        str += "    离火之精，坎水之精，白金雷魄，青木风魂，戊土之灵。\n";
    }
    me->start_more(str);
}

string show_fabao_status(object ob)
{
    string str = "";
    string fabao_type = ob->query("fabao_type");
    mapping *my_props;
    
    if (!arrayp(my_props = props[fabao_type]))
        return "";

    for (int i = 0; i < sizeof(my_props); i++) {
        mapping prop = my_props[i];
        int stars = ob->query("stars/" + prop["id"]);
        str += prop["name"] + "       ";
        str += display_stars(stars) + "    ";
        if (i % 2 != 0) str += "\n";
    }
    
    if (fabao_type == "weapon")
        str += NOR"属性伤害       ";
    else if (fabao_type == "armor")
        str += NOR"属性防护       ";
    str += sprintf("%s金%s木%s水%s火%s土%s\n",
        ob->query(fabao_type + "_prop/gold") ? HIW : WHT,
        ob->query(fabao_type + "_prop/wood") ? HIG : GRN,
        ob->query(fabao_type + "_prop/water") ? HIB : BLU,
        ob->query(fabao_type + "_prop/fire") ? HIR : RED,
        ob->query(fabao_type + "_prop/soil") ? HIY : YEL,
        NOR);
    
    if (fabao_type == "weapon") {
        int subtype_zero, subtype;
        
        subtype_zero = ob->query("fabao_subtype/0");
        str += HIB "型    态       " NOR;
        for (int j = 1; subtype = ob->query("fabao_subtype/" + j); j++) {
            if (subtype == subtype_zero) str += HIY;
            else str += YEL;
            str += subtypes["weapon"][subtype - 1]["name"] + " " NOR;
        }
        str += NOR "\n";
    }
    return str;
}

string display_stars(int stars)
{
    return sprintf("%s%s%s%s%s%s%s", HIR,
                stars > 0 ? "★" : "　",
                stars > 1 ? "★" : "　",
                stars > 2 ? "★" : "　",
                stars > 3 ? "★" : "　",
                stars > 4 ? "★" : "　",
                NOR);
}

int varify_formula(string formula_type, object smelter)
{
    object fabao_ob;
    mapping minerals_ob = ([]), elements_ob = ([]);

    foreach (object ob in all_inventory(smelter)) {
        if (ob->query("owner_id") && ob->query("series_no")) {
            if (objectp(fabao_ob))
                return notify_fail("你到底想强化哪一件法宝？\n");
            fabao_ob = ob;
        }
        else if (!ob->query("is_mineral"))
            return notify_fail("有其他杂质，炼化无法进行。\n");
        else {
            mapping element_prop;
            if (!mapp(element_prop = ob->query("elements")))
                minerals_ob += ([ ob->query("id") : ob ]);
            else {
                foreach (string elem in keys(element_prop)) {
                    if (undefinedp(elements_ob[elem]))
                        elements_ob[elem] = ({});
                    elements_ob[elem] += ({ ob });
                }
            }
        }
    }
    
    if (formula_type != "" && !objectp(fabao_ob))
        return notify_fail("你没有放入法宝。\n");
    
    if (formula_type == "enhance") {
        string half, *zero = ({}), enhance_type;
        string fabao_type = fabao_ob->query("fabao_type");
        int stars, comp = 0, enhance_point = 0;
        
        if (sizeof(minerals_ob))
            return notify_fail("有其他杂质，炼化无法进行。\n");
        if (!sizeof(elements_ob))
            return notify_fail("请放入至少一种五行之精，如果法宝恰好处于某一级的开始阶段"
                        "（还没有确定发展方向），则只能放入一种五行之精。\n");
        
        foreach (string elem in keys(elements)) {
            int elem_prop = fabao_ob->query(fabao_type + "_prop/" + elem);
            if (elem_prop >= 100)
                comp++;
            if (elem_prop > 0 && elem_prop < 100)
                half = elem;
            if (elem_prop == 0 && !undefinedp(elements_ob[elem]))
                zero += ({ elem });
        }

        stars = fabao_ob->query("stars/" + props[fabao_type][0]["id"]);
        if (stringp(half)) {
            if (sizeof(zero))
                return notify_fail(fabao_ob->name() + "的『"
                            + elements[half] + "』属性还没有升级完，不要放入其他杂质。\n");
        }
        else if (sizeof(zero) > 1)
            return notify_fail(fabao_ob->name() + "的发展方向还没有确定，请放入单一种类的五行之精。\n");
        else if (sizeof(zero) < 1)
            return notify_fail(fabao_ob->name() + "的这些属性都已经升满了。\n");
        else {
            if (comp + 1 > stars)
                return notify_fail(fabao_ob->name() + "的等级不够，无法强化新的属性。\n");
            enhance_type = zero[0];
        }
        
        foreach (object elem in elements_ob[enhance_type]) {
            enhance_point += elem->query("elements/" + enhance_type);
        }
        
        smelter->set_temp("fabao_ob", fabao_ob);
        smelter->set_temp("enhance/type", enhance_type);
        smelter->set_temp("enhance/point", enhance_point);
        smelter->set_temp("enhance/name", elements[enhance_type]);
        return 1;
    }
    else {
        string fabao_type = "";
        
        if (objectp(fabao_ob))
            fabao_type = fabao_ob->query("fabao_type");
        
        if (undefinedp(formulas[fabao_type][formula_type]))
            return notify_fail("法宝没有这一项可升级属性。\n");
        
        foreach (string m in keys(formulas[fabao_type][formula_type])) {
            if (undefinedp(minerals_ob[m]))
                return notify_fail("缺少材料『" + minerals[m] + "』。\n");
            if (minerals_ob[m]->query_amount() < formulas[fabao_type][formula_type][m])
                return notify_fail("材料『" + minerals[m] + "』不足。\n");
        }
        
        foreach (string m in keys(minerals_ob)) {
            if (undefinedp(formulas[fabao_type][formula_type]))
                return notify_fail("有其他杂质，炼化无法进行。\n");
        }
        
        if (objectp(fabao_ob)) {
            int comp = 0;
            foreach (string elem in keys(elements)) {
                if (fabao_ob->query(fabao_type + "_prop/" + elem) >= 100)
                    comp++;
            }
            smelter->set_temp("elem_comp", comp);
            smelter->set_temp("fabao_ob", fabao_ob);
        }
    }

    return 1;
}

varargs int varify_player(string prop, object me, object smelter)
{
    object fabao_ob;
    mapping p_info, *costs;
    string fabao_type;
    int stars, upgraded, elem_comp, min_exp, min_force, min_mana;

    fabao_ob = smelter->query_temp("fabao_ob");
    if (!objectp(fabao_ob)) {
        if (me->query("combat_exp") < 20000)
            return notify_fail("你的道行太浅，无法理解炼制法宝的玄妙。\n");
        if (me->query("max_force") < 300)
            return notify_fail("你的内力不够，无法支持炼制法宝的巨大消耗。\n");
        if (me->query("max_mana") < 300)
            return notify_fail("你的法力不够，无法支持炼制法宝的巨大消耗。\n");
        if (me->query("force") < (me->query("max_force") + 100))
            return notify_fail("炼制法宝时，你必须处于真气充盈的状态。\n");
        if (me->query("mana") < (me->query("max_mana") + 100))
            return notify_fail("炼制法宝时，你必须处于灵气充盈的状态。\n");
        if (count_fabao(me, "weapon") >= MAX_WEAPON
        &&  count_fabao(me, "armor") >= MAX_ARMOR)
            return notify_fail("你的法宝数已经达到了极限，再多也没法控制了。\n");

        me->delete_temp("fabaod");
        me->set_temp("fabaod/max_force", 50);
        me->set_temp("fabaod/max_mana", 50);
        me->set_temp("fabaod/force", 200);
        me->set_temp("fabaod/mana", 200);
        return 1;
    }

    if (prop == "enhance")
        return 1;

    fabao_type = fabao_ob->query("fabao_type");
    if (!mapp(p_info = query_prop(fabao_type, prop)))
        return notify_fail("没有这项属性。\n");

    stars = fabao_ob->query("stars/" + prop);
    upgraded = fabao_ob->query("upgraded/" + prop);
    if (stars >= 5)
        return notify_fail("特性『" + p_info["name"] + "』已经不能升级了！\n");

    costs = upgrades[fabao_type][prop];
    min_exp = costs[stars]["min_exp"];
    min_exp += (costs[stars + 1]["min_exp"] - costs[stars]["min_exp"]) * upgraded / 5;
    min_force = costs[stars]["min_force"];
    min_mana = costs[stars]["min_mana"];
    if (min_exp > me->query("combat_exp")
    ||  min_force > me->query("max_force")
    ||  min_mana > me->query("max_mana"))
        return notify_fail("能力不足，无法继续升级法宝。（请用cost指令查询升级条件。）\n");

    elem_comp = smelter->query_temp("elem_comp");
    if (elem_comp < stars)
        return notify_fail(fabao_ob->name() + "的第" + chinese_number(elem_comp + 1)
                    + "种五行属性尚没有圆满，无法继续升级。\n");
    me->delete_temp("fabaod");
    me->set_temp("fabaod/max_force", costs[stars]["force"]);
    me->set_temp("fabaod/max_mana", costs[stars]["mana"]);
    me->set_temp("fabaod/combat_exp", costs[stars]["exp"]);
    smelter->set_temp("upgraded_prop", p_info["name"]);
    return 1;
}

mixed query_prop(string fabao_type, string prop)
{
    foreach (mapping m in props[fabao_type]) {
        if (m["id"] == prop)
            return m;
    }
    return 0;
}

void start_make_fabao(object ob, object smelter)
{
    write("您要炼造哪类法宝：\n");
    if (count_fabao(ob, "weapon") < MAX_WEAPON)
        write("w. 武器\n");
    if (count_fabao(ob, "armor") < MAX_ARMOR)
        write("a. 防具\n");
    write("o. 其他(暂缺)\n");
    // Other kinds of fabao can be added too.. if there is somefile
    // we can use as a default object.
    write("请选择：(q 键取消)");

    seteuid(getuid());
    input_to( (: get_fabao_type, ob, smelter :) );
}

void get_fabao_type(object ob, object smelter, string arg)
{
    string fabao_type;
    
    if (arg == "q" || arg == "Q")
        return;
    
    if ((arg != "w" || count_fabao(ob, "weapon") >= MAX_WEAPON)
    &&  (arg != "a" || count_fabao(ob, "armor") >= MAX_ARMOR)) {
        write("您要炼造哪类法宝：\n");
        if (count_fabao(ob, "weapon") < MAX_WEAPON)
            write("w. 武器\n");
        if (count_fabao(ob, "armor") < MAX_ARMOR)
            write("a. 防具\n");
        write("o. 其他(暂缺)\n");
        write("请选择：(q 键取消)");
        input_to( (: get_fabao_type, ob, smelter :) );
        return;
    }
    
    if (arg == "w") {
        fabao_type = "weapon";
        write("\n");
        write("可选择武器种类：\n");
        write(show_subtypes("weapon"));
        write("请选择：(q 键取消)");
    }
    else if (arg == "a") {
        fabao_type = "armor";
        write("\n");
        write("可选择防具种类：\n");
        write(show_subtypes("armor"));
        write("请选择：(q 键取消)");
    }
    ob->set_temp("fabao_type", fabao_type);
    ob->set_temp("fabao_new", fabao_type + (count_fabao(ob, fabao_type) + 1));
    input_to( (: get_fabao_subtype, ob, smelter :) );
}

void get_fabao_subtype(object ob, object smelter, string arg)
{
    int  order;
    string fabao_type = ob->query_temp("fabao_type");
    
    if (arg == "q" || arg == "Q") return;
    
    order = atoi(arg);

    if ((fabao_type == "weapon" && order <= 0 && order > 10)
    ||  (fabao_type == "armor" && order <= 0 && order > 13)) {
        if (arg == "w")    {
            fabao_type = "weapon";
            write("\n");
            write("可选择武器种类：\n");
            write(show_subtypes("weapon"));
            write("请选择：(q 键取消)");
        }
        else if (arg == "a")   {
            fabao_type = "armor";   
            write("\n");
            write("可选择防具种类：\n");
            write(show_subtypes("armor"));
            write("请选择：(q 键取消)");
        }
        ob->set_temp("fabao_type", fabao_type);
        input_to( (: get_fabao_subtype, ob, smelter :) );
        return;
    }
    
    ob->set_temp("fabao_subtype", order);
    
    write("\n");
    write("请设定英文 id ：");
    input_to( (: get_fabao_id, ob, smelter :) );
}

void get_fabao_id(object ob, object smelter, string arg)
{
    arg = lower_case(arg);
    if (!LOGIN_D->check_legal_id(arg)) {
        write("请设定英文 id ：");
        input_to( (: get_fabao_id, ob, smelter :) ); 
        return;
    }
    
    arg = replace_string(arg, " ", "_");
    ob->set_temp("fabao_id", arg);
    
    write("\n");
    write("请设定中文名：(可加颜色)");
    input_to( (: get_fabao_name, ob, smelter :) );
}

void get_fabao_name(object ob, object smelter, string arg)
{
    string arg_old;
    
    arg += "$NOR$";
    arg_old = arg;
    arg = replace_string(arg, "$BLK$", "");
    arg = replace_string(arg, "$RED$", "");
    arg = replace_string(arg, "$GRN$", "");
    arg = replace_string(arg, "$YEL$", "");
    arg = replace_string(arg, "$BLU$", "");
    arg = replace_string(arg, "$MAG$", "");
    arg = replace_string(arg, "$CYN$", "");
    arg = replace_string(arg, "$WHT$", "");
    arg = replace_string(arg, "$HIR$", "");
    arg = replace_string(arg, "$HIG$", "");
    arg = replace_string(arg, "$HIY$", "");
    arg = replace_string(arg, "$HIB$", "");
    arg = replace_string(arg, "$HIM$", "");
    arg = replace_string(arg, "$HIC$", "");
    arg = replace_string(arg, "$HIW$", "");
    arg = replace_string(arg, "$NOR$", "");
    
    if (!LOGIN_D->check_legal_name(arg, 12)) {
        write("请设定中文名：(可加颜色)");
        input_to( (: get_fabao_name, ob, smelter :) );
        return;
    }
    
    arg = arg_old;
    
    arg = replace_string(arg, "$BLK$", BLK);
    arg = replace_string(arg, "$RED$", RED);
    arg = replace_string(arg, "$GRN$", GRN);
    arg = replace_string(arg, "$YEL$", YEL);
    arg = replace_string(arg, "$BLU$", BLU);
    arg = replace_string(arg, "$MAG$", MAG);
    arg = replace_string(arg, "$CYN$", CYN);
    arg = replace_string(arg, "$WHT$", WHT);
    arg = replace_string(arg, "$HIR$", HIR);
    arg = replace_string(arg, "$HIG$", HIG);
    arg = replace_string(arg, "$HIY$", HIY);
    arg = replace_string(arg, "$HIB$", HIB);
    arg = replace_string(arg, "$HIM$", HIM);
    arg = replace_string(arg, "$HIC$", HIC);
    arg = replace_string(arg, "$HIW$", HIW);
    arg = replace_string(arg, "$NOR$", NOR);
    
    ob->set_temp("fabao_name", arg);
    
    write("\n");
    write("请描述法宝：");
    input_to( (: get_fabao_desc, ob, smelter :) );
}

void get_fabao_desc(object ob, object smelter, string arg)
{
    ob->set_temp("fabao_desc", arg);
    
    write("\n");
    write("法宝用量词：(Return for default)");
    input_to( (: get_fabao_unit, ob, smelter :) );
}

void get_fabao_unit(object ob, object smelter, string arg)
{
    string fabao_unit;

    if (arg == "")
        fabao_unit = "";
    else if (!LOGIN_D->check_legal_name(arg, 2)) {
        write("法宝用量词：(Return for defult)");
        input_to( (: get_fabao_unit, ob, smelter :) );
        return;
    }
    else
        fabao_unit = arg;

    ob->set_temp("fabao_unit", fabao_unit);
    
    write("信息确认完毕，开始炼制法宝。\n\n\n");
    smelter->complete_make_fabao(ob);
}

object new_fabao_ob(object ob)
{
    object newob;
    int rev;
    string fabao_type = ob->query_temp("fabao_type");
    int    fabao_subtype = ob->query_temp("fabao_subtype");
    string fabao_id = ob->query_temp("fabao_id");
    string fabao_name = ob->query_temp("fabao_name");
    string fabao_desc = ob->query_temp("fabao_desc");
    string fabao_unit = ob->query_temp("fabao_unit");
    
    newob = new("/obj/fabao");
    if (!newob)
        return newob;
    seteuid(getuid(ob));
    rev = export_uid(newob);
    seteuid(getuid());
    
    newob->set("fabao_type", fabao_type);
    newob->set("fabao_subtype/0", fabao_subtype);
    newob->set("fabao_subtype/1", fabao_subtype);

    newob->set("id", fabao_id);
    newob->set("name", fabao_name);
    newob->set("long", fabao_desc);
    if (fabao_unit != "")
        newob->set("unit", fabao_unit);

    newob->set("value", 1);
    newob->set("no_sell", 1);

    newob->set("rigidity", 100);
    newob->set("flag", TWO_HANDED);

    // set owner of fabao
    newob->set("owner_id", getuid(ob));
    newob->set("series_no", max_series_no(ob) + 1);

    foreach (mapping prop in props[fabao_type]) {
        newob->set("stars/" + prop["id"], 0);
        newob->set("upgraded/" + prop["id"], 0);
    }
    foreach (string elem in keys(elements)) {
        newob->set(fabao_type + "_prop/" + elem, 0);
    }
    return newob;
}

void build_weapon(object ob)
{
    int subtype = ob->query("fabao_subtype/0");

    string ob_file = "/d/obj/weapon/"
        + subtypes["weapon"][subtype - 1]["default_file"];

    ob->set("default_file", ob_file);
    ob->set_default_object(ob_file);

    setup_prop(ob, "weapon");

    if (ob->query("seal")) {
        ob->set("short", ob->name() + "(" + capitalize(ob->query("id")) + ")" + CYN + "『封印中』" + NOR);
        ob->set("weapon_prop/damage", 1);
    }
    else {
        ob->delete("short");
    }
}

void build_armor(object ob)
{
    int subtype = ob->query("fabao_subtype/0");

    string ob_file = "/d/obj/"
        + subtypes["armor"][subtype - 1]["default_file"];

    ob->set("default_file", ob_file);
    ob->set_default_object(ob_file);

    setup_prop(ob, "armor");
}

void setup_prop(object ob, string type)
{
    foreach (mapping prop in props[type]) {
        string p_name = prop["id"];
        int val = prop["init_val"];
        int stars = ob->query("stars/" + p_name);
        int upgraded = ob->query("upgraded/" + p_name);
        mapping *effs = upgrades[type][p_name];
        
        for (int i = 0; i < stars + 1; i++) {
            if (i != stars)
                val += effs[i]["val"] * 5;
            else
                val += effs[i]["val"] * upgraded;
        }
        ob->set(type + "_prop/" + p_name, val);
    }
}

int count_fabao(object me, string type)
{
    int i;
    for (i = 1; me->query("fabao/" + type + i); i++)
        ;
    return i;
}

int max_series_no(object me)
{
    int i, series, max_series;
    for (i = 0; series = me->query("fabao/weapon" + i); i++)
        if (max_series < series)
            max_series = series;
    for (i = 0; series = me->query("fabao/armor" + i); i++)
        if (max_series < series)
            max_series = series;
    return max_series;
}

string show_subtypes(string fabao_type)
{
    string str = "";
    int i;
    for (i = 0; i < sizeof(subtypes[fabao_type]); i++) {
        mapping subtype = subtypes[fabao_type][i];
        string no = (i + 1) + ".";
        if (strlen(no) < 3) no += " ";
        str += no + subtype["name"] + "\t";
        if ((i + 1) % 5 == 0) str += sprintf("\n");
    }
    if ((i + 1) % 5 != 1) str += sprintf("\n");
    return str;
}
