// ALI by NewX

// score.c

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string *sex_ranking_male = ({"初尝禁果", "欢场老手", "御女无数"});
string *sex_ranking_female = ({"初尝禁果", "床第高手", "旷世淫娃"});

string display_attr(int gift, int value);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
    object ob;
    mapping my;
    string line, str;

    seteuid(getuid(me));

    if (!arg)
        ob = me;
    else if (wizardp(me)) {
        ob = present(arg, environment(me));
        if (!ob) ob = find_player(arg);
        if (!ob) ob = find_living(arg);
        if (!ob) return notify_fail("你要察看谁的状态？\n");
    } else
        return notify_fail("只有巫师能察看别人的状态。\n");

    my = ob->query_entire_dbase();

    write(NOR YEL"\n≡≡≡≡≡≡≡≡≡≡"HIG"个"NOR YEL"≡≡"HIG"人"NOR YEL"≡≡"HIG"档"NOR YEL"≡≡"HIG"案"NOR YEL"≡≡≡≡≡≡≡≡≡≡\n"NOR);
    line = sprintf(BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(ob), ob->short(1));

    if (my["always_young"])
        line += sprintf(" 性别："HIG"%-4s"NOR"  年龄："HIY"%-4s岁"NOR"  寿元："CYN"%-6s岁"NOR" \n\n",
            my["gender"], chinese_number(my["fake_age"]), chinese_number(my["age"]));
    else
        line += sprintf(" 性别："HIG"%-4s"NOR"  年龄："HIY"%-4s岁"NOR" \n\n",
            my["gender"], chinese_number(my["age"]));

    line += sprintf(
            " 力量：[%s]  | 定力：[%s]  | 胆识：[%s]  | 容貌：[%s]\n",
            display_attr(my["str"], ob->query_str()),
            display_attr(my["cps"], ob->query_cps()),
            display_attr(my["cor"], ob->query_cor()),
            display_attr(my["per"], ob->query_per()),
            );
    line += sprintf(
            " 悟性：[%s]  | 灵性：[%s]  | 根骨：[%s]  | 福缘：[%s]\n\n",
            display_attr(my["int"], ob->query_int()),
            display_attr(my["spi"], ob->query_spi()),
            display_attr(my["con"], ob->query_con()),
            display_attr(my["kar"], ob->query_kar()),
            );

    if (mapp(my["family"]))
        line += sprintf(" 门  派：" HIC "%-6s" NOR, my["family"]["family_name"]);
    else
        line += sprintf(" 门  派：" HIC "无" NOR);
    if (mapp(my["family"]) && my["family"]["master_name"])
        line += sprintf("  师  父：" YEL "%s" NOR, my["family"]["master_name"]);
    else
        line += sprintf("  师  父：" YEL "无" NOR);
    if (stringp(my["secret_master_name"]))
        line += sprintf("  秘密师父：" MAG "%s\n" NOR, my["secret_master_name"]);
    else
        line += "\n";

    line += sprintf(" 战  绩：杀 %d 人，其中NPC %d 人，其他玩家 %d 人\n",
        my["MKS"] + my["PKS"], my["MKS"], my["PKS"]);

    line += " 性经验：";
    if (mapp(my["sex"]) && mapp(my["sex"]["lovers"])) {
        if (my["gender"] == "男性") {
            line += HIY + sex_ranking_male[sizeof(my["sex"]["lovers"])/10] + NOR;
            if (!my["sex"]["first_semen_lost"])
                line += "，但仍保持" HIB "童子之身" NOR;
        } else if (my["gender"] == "女性") {
            line += HIY + sex_ranking_female[sizeof(my["sex"]["lovers"])/10] + NOR;
            if (!my["sex"]["hymen_broken"])
            line += "，但仍保持" HIB "处子之身" NOR;
        }
    }
    else
        line += HIB + (my["gender"]=="男性"?"童":"处") + "子之身" NOR;
    
    if (undefinedp(my["sex_leaning"]))
        line += "\n";
    else if (my["sex_leaning"] == "both")
        line += " 性倾向：" HIY "男性" NOR "／" HIY "女性" NOR "\n";
    else if (my["sex_leaning"]=="same") {
        if (my["gender"]=="女性")
            line += " 性倾向：" HIY "女性" NOR "\n";
        else
            line += " 性倾向：" HIY "男性" NOR "\n";
    } else if (my["sex_leaning"]=="diff") {
        if (my["gender"]=="女性")
            line += " 性倾向：" HIY "男性" NOR "\n";
        else
            line += " 性倾向：" HIY "女性" NOR "\n";
    } else
        line += "\n";

    if (ob->query("balance"))
        line += " 存  款：" + MONEY_D->money_str((int)ob->query("balance"))+"存款\n\n";
    else
        line += " 存  款：" HIW "没有任何存款" NOR "\n\n";

    line += RED " 西天取经" NOR "：" + OBSTACLES_D->check_obstacles_short(ob) + "\n";
    line += RED " 大闹天宫" NOR "：" + OBSTACLES_D->check_obstacles_short(ob, "dntg") + "\n\n";

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
    
        line += sprintf(" 攻击评价：%s%-10d%s(%s%+5d%s)  防御评价：%s%-10d%s(%s%+5d%s)\n",
            HIW, attack_points/100 + 1, NOR,
            HIR, ob->query_temp("apply/damage"), NOR,
            HIW, (dodge_points + (weapon? parry_points:(parry_points/10)))/100 + 1, NOR,
            HIY, ob->query_temp("apply/armor"), NOR);
    }

    line += sprintf(" 道行境界：%s           武学境界：%s\n",
                RANK_D->describe_exp(ob->query("combat_exp")),
                RANK_D->describe_skills(ob->query_skills()));
    line += sprintf(" 法力修为：%s           内力修为：%s\n",
                RANK_D->describe_mana(ob->query("max_mana")),
                RANK_D->describe_force(ob->query("max_force")));

    line += sprintf("\n %s在 ["YEL"西游记"NOR"·"HIG"阿里世界"NOR"] 中已经历了 %s 的岁月 \n",
        ob == me ? "你" : ob->name(1),
        HIR + FINGER_D->age_string( (int)ob->query("mud_age")) + NOR);
    line += NOR YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"NOR;

    write(line);
    return 1;
}

string display_attr(int gift, int value)
{
    if (value > gift) return sprintf( HIY "%3d" NOR, value );
    else if (value < gift) return sprintf( CYN "%3d" NOR, value );
    else return sprintf("%3d", value);
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

