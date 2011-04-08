// ALI by NewX

// score.c

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

//string *gift_ranking = ({"下下之选","下等", "中下", "中等", "中上", "上等", "上上之选"});

string *sex_ranking = ({"初尝禁果", "初尝禁果", "床第高手", "欢场高手", "旷世淫娃", "御女无数"});

string bar_string = "■■■■■■■■■■■■■■■■■■■■■■■■■";
string blank_string ="□□□□□□□□□□□□□□□□□□□□□□□□□";

string display_attr(int gift, int value);
string tribar_graph(int val, int eff, int max, string color);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
    object ob;
    mapping my;
    string line;

    seteuid(getuid(me));

    if(!arg)
        ob = me;
    else if (wizardp(me)) {
        ob = present(arg, environment(me));
        if (!ob) ob = find_player(arg);
        if (!ob) ob = find_living(arg);
        if (!ob) return notify_fail("你要察看谁的状态？\n");
    } else
        return notify_fail("只有巫师能察看别人的状态。\n");

    my = ob->query_entire_dbase();

    line = sprintf( BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(ob),
        ob->short(1) );

    line += sprintf(" 种族：" HIG "%s" NOR
            " 性别：" HIG "%s" NOR
            " 年龄：" HIY "%s岁" NOR
            " 道行：" RED "%s年" NOR "\n\n",
            my["race"], my["gender"], chinese_number(my["age"]),
            my["combat_exp"] > 1000 ? chinese_number(my["combat_exp"]/1000)
                : "不到一"
            );

    line += sprintf(
            " 力量：[%s]  敏捷：[%s]  智力：[%s]  灵性：[%s]\n"
            " 定力：[%s]  胆识：[%s]  魅力：[%s]  根骨：[%s]\n"
            " 硬度: [%s]  敏感：[%s]  心性：[%s]  福缘：[%s]\n\n",
            display_attr(my["str"], ob->query_str()),
            display_attr(my["dex"], ob->query_dex()),
            display_attr(my["int"], ob->query_int()),
            display_attr(my["spi"], ob->query_spi()),
            display_attr(my["cps"], ob->query_cps()),
            display_attr(my["cor"], ob->query_cor()),
            display_attr(my["per"], ob->query_per()),
            display_attr(my["con"], ob->query_con()),
            display_attr(my["rig"], ob->query_rig()),
            display_attr(my["sns"], ob->query_sns()),
            display_attr(my["met"], ob->query_met()),
            display_attr(my["kar"], ob->query_kar()),
            );

#if 0
    if (mapp(my["family"])) {
        if (my["family"]["master_name"])
            line += sprintf(" 师父：" YEL "%s" NOR, my["family"]["master_name"] );
    }
#endif

    if (mapp(my["makelove"]) && sizeof(my["makelove"]) > 0) {
        int gender = my["gender"] == "男性";
        int lover = sizeof(my["makelove"]);
        lover = lover > 30 ? 30 : lover;
        line += " 性经验：" HIY +sex_ranking[(lover/10)*2+gender] + NOR;
    } else {
        string gender = my["gender"];
        line += " 性经验：" HIB "处" + gender[0..1] + NOR;
    }
    
    if (undefinedp(my["sex_leaning"]))
        line += "\n";
    else if (my["sex_leaning"] == "both")
        line += " 性倾向："HIY"男性"NOR"／"HIY"女性"NOR"\n";
    else if (my["sex_leaning"]=="same") {
        if (my["gender"]=="女性")
            line += " 性倾向："HIY"女性"NOR"\n";
        else
            line += " 性倾向："HIY"男性"NOR"\n";
    } else if (my["sex_leaning"]=="diff") {
        if (my["gender"]=="女性")
            line += " 性倾向："HIY"男性"NOR"\n";
        else
            line += " 性倾向："HIY"女性"NOR"\n";
    } else
        line += "\n";

    line += sprintf(" 战  绩：杀 %d 人，其中NPC %d 人，其他玩家 %d 人\n",
        my["MKS"] + my["PKS"], my["MKS"], my["PKS"]);
        
    if (ob->query("kill/pkgain")) { 
        line +=sprintf(" ＰＫ道行增加： %s  \n",
            COMBAT_D->chinese_daoxing(ob->query("kill/pkgain")));
    }
    if (ob->query("kill/pklose")) {
        line +=sprintf(" ＰＫ道行减少： %s\n",
            COMBAT_D->chinese_daoxing(ob->query("kill/pklose")));
    }
    if (ob->query("kill/nkgain")) {
        line +=sprintf(" ＮＫ道行增加： %s\n",
            COMBAT_D->chinese_daoxing(ob->query("kill/nkgain")));
    }

    if (ob->query("obstacle/number"))
        line += sprintf(" 你西行求取真经已过了"RED"%s关"NOR"。\n\n",
                chinese_number(ob->query("obstacle/number")));
    else
        line += sprintf("\n");

    line += " <精>  " + tribar_graph(my["gin"], my["eff_gin"],
        my["max_gin"], HIY) + "\n";
    line += " <气>  " + tribar_graph(my["kee"], my["eff_kee"],
        my["max_kee"], HIR) + "\n";
    line += " <神>  " + tribar_graph(my["sen"], my["eff_sen"],
        my["max_sen"], HIB) + "\n";

#if 0
/*
        line += sprintf(" 气： %s%4d/ %4d %s(%3d%%)" NOR "    内力： %s%4d
/ %4d (+%d)\n" NOR,
                status_color(my["kee"], my["eff_kee"]), my["kee"],
my["eff_kee"],
                status_color(my["eff_kee"], my["max_kee"]),
my["eff_kee"] * 100 / my["max_kee"],
                status_color(my["force"], my["max_force"]),
my["force"], my["max_force"],
                my["force_factor"] );
        line += sprintf(" 神： %s%4d/ %4d %s(%3d%%)" NOR "    法力： %s%4d
/ %4d (+%d)\n" NOR,
                status_color(my["sen"], my["eff_sen"]), my["sen"],
my["eff_sen"],
                status_color(my["eff_sen"], my["max_sen"]),
my["eff_sen"] * 100 / my["max_sen"],
                status_color(my["mana"], my["max_mana"]), my["mana"],
my["max_mana"],
                my["mana_factor"] );
*/
/*
        line += sprintf(" 食物：%d/%d，饮水：%d/%d\n\n",
                my["food"], ob->max_food_capacity(), my["water"],
ob->max_water_capacity());
*/
#endif

    {
    /* ap/dp calc */
    string skill_type;
    object weapon;
    int attack_points, dodge_points, parry_points;

    if (objectp(weapon = ob->query_temp("weapon")))
        skill_type = weapon->query("skill_type");
    else
        skill_type = "unarmed";

    attack_points = COMBAT_D->skill_power(ob, skill_type,
        SKILL_USAGE_ATTACK);
    parry_points = COMBAT_D->skill_power(ob, skill_type,
        SKILL_USAGE_DEFENSE);
    dodge_points = COMBAT_D->skill_power(ob, "dodge",
        SKILL_USAGE_DEFENSE);

    line += sprintf("\n 战斗攻击力 " HIW "%d (+%d)" NOR
        "\t\t战斗防御力 " HIW "%d (+%d)\n\n" NOR,
        attack_points/100 + 1, ob->query_temp("apply/damage"),
        (dodge_points + (weapon? parry_points:
            (parry_points/10)))/100 + 1, ob->query_temp("apply/armor"));
    }

    line += " 食物：" + tribar_graph(my["food"],
        ob->max_food_capacity(), ob->max_food_capacity(), YEL) + "\n";
    line += " 饮水：" + tribar_graph(my["water"],
        ob->max_water_capacity(), ob->max_water_capacity(), CYN) + "\n\n";

    line += sprintf(" 杀  气： " RED "%-9d" NOR "            ",ob->query("bellicosity") );
    line += sprintf(" 潜  能： " HIY "%-9d\n" NOR,(int)ob->query("potential") -(int)ob->query("learned_points") );
    //line += sprintf(" 神  数： " HIM "%-9d" NOR,ob->query("shen") );
    //line += sprintf(" 评  价： " HIC "%-9d\n" NOR,ob->query("score") );

    write(line);
    return 1;
}

string display_attr(int gift, int value)
{
    if (value > gift) return sprintf( HIY "%3d" NOR, value );
    else if (value < gift) return sprintf( CYN "%3d" NOR, value );
    else return sprintf("%3d", value);
}

string tribar_graph(int val, int eff, int max, string color)
{
    return color + bar_string[0..(val*25/max)*2-1]
        + ((eff > val) ? blank_string[(val*25/max)*2..(eff*25/max)*2-1] : "")
        + NOR;
}

int help(object me)
{
    write(@HELP
指令格式 : score
           score <对象名称>                   (巫师专用)

这个指令可以显示你或指定对象(含怪物)的基本资料。
基本资料的设定请参阅 'help setup'。

see also : hp
HELP
    );
    return 1;
}

