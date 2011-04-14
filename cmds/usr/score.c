// ALI by NewX

// score.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *sex_ranking = ({"初尝禁果", "初尝禁果", "床第高手", "欢场高手", "旷世淫娃", "御女无数"});

string display_attr(int gift, int value);

string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor);

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

    write(NOR YEL"≡≡≡≡≡≡≡≡≡≡"HIG"个"NOR YEL"≡≡"HIG"人"NOR YEL"≡≡"HIG"档"NOR YEL"≡≡"HIG"案"NOR YEL"≡≡≡≡≡≡≡≡≡≡\n"NOR);
    line = sprintf(BOLD "%s" NOR "%s\n", RANK_D->query_rank(ob), ob->short(1));
    line += NOR YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"NOR;

    line += sprintf(" 性别：%s%-4s%s  年龄：%s%-4s岁%s%-6s       门派：%s%-6s%s\n\n",
            HIG, my["gender"], NOR,
            HIY, my["always_young"] ? chinese_number(my["fake_age"]) : chinese_number(my["age"]), NOR,
            my["always_young"] ? "("CYN+chinese_number(my["age"])+"岁"NOR")" : "      ",
            HIC, mapp(my["family"]) ? my["family"]["family_name"] : "无", NOR,
            );

    line += sprintf(
            " 力量：[%s]  | 敏捷：[%s]  | 定力：[%s]  | 胆识：[%s]\n\n",
            display_attr(my["str"], ob->query_str()),
            display_attr(my["dex"], ob->query_dex()),
            display_attr(my["cps"], ob->query_cps()),
            display_attr(my["cor"], ob->query_cor()),
            );
    
    if (my["eff_gin"] < my["max_gin"]) str = HIR + "生病";
    else if (my["gin"]*100 / my["max_gin"]>=70) str = HIG + "充盈";
    else if (my["gin"]*100 / my["max_gin"]>=40) str = HIR + "虚耗";
    else str = HIB + "大损";
    line += sprintf(" 智力：[%s%3s%s]  | 〖%s精元%s〗 %s [%4s%s]\n",
                NOR, display_attr(my["int"], ob->query_int()), NOR,
                HIR, NOR, tribar_graph(my["gin"], my["eff_gin"], my["max_gin"], NOR, HIR, HIW),
                str, NOR);

    if (my["eff_kee"] < my["max_kee"]) str = HIR + "伤残";
    else if (my["kee"]*100 / my["max_kee"]>=70) str = HIG + "充沛";
    else if (my["kee"]*100 / my["max_kee"]>=40) str = HIR + "受伤";
    else str = HIB + "重伤";
    line += sprintf(" 根骨：[%s%3s%s]  | 〖%s气血%s〗 %s [%4s%s]\n",
                NOR, display_attr(my["con"], ob->query_con()), NOR,
                HIR, NOR, tribar_graph(my["kee"], my["eff_kee"], my["max_kee"], NOR, HIR, HIW),
                str, NOR);

    if (my["eff_sen"] < my["max_sen"]) str = HIR + "失魂";
    else if (my["sen"]*100 / my["max_sen"]>=70) str = HIG + "饱满";
    else if (my["sen"]*100 / my["max_sen"]>=40) str = HIR + "疲倦";
    else str = HIB + "很累";
    line += sprintf(" 灵性：[%s%3s%s]  | 〖%s精神%s〗 %s [%4s%s]\n",
                NOR, display_attr(my["spi"], ob->query_spi()), NOR,
                HIR, NOR, tribar_graph(my["sen"], my["eff_sen"], my["max_sen"], NOR, HIR, HIW),
                str, NOR);

    if (my["food"] * 100 / ob->max_food_capacity() >= 80) str = HIG + "吃饱";
    else if (my["food"] * 100 / ob->max_food_capacity() >= 50) str = HIC + "正常";
    else if (my["food"] * 100 / ob->max_food_capacity() >= 20) str = HIR + "缺食";
    else str = HIB + "饥饿";
    line += sprintf(" 容貌：[%s%3s%s]  | 〖%s食物%s〗 %s [%4s%s]\n",
                NOR, display_attr(my["per"], ob->query_per()), NOR,
                HIC, NOR, tribar_graph(my["food"], ob->max_food_capacity(), ob->max_food_capacity(), NOR, HIC, HIR),
                str, NOR);

    if (my["water"] * 100 / ob->max_water_capacity() >= 80) str = HIG + "喝足";
    else if (my["water"] * 100 / ob->max_water_capacity() > 60) str = HIG + "正常";
    else if (my["water"] * 100 / ob->max_water_capacity() > 30) str = HIR + "缺水";
    else str = HIB + "饥渴";
    line += sprintf(" 福缘：[%s%3s%s]  | 〖%s饮水%s〗 %s [%4s%s]\n",
                NOR, display_attr(my["kar"], ob->query_kar()), NOR,
                HIC, NOR, tribar_graph(my["water"], ob->max_water_capacity(), ob->max_water_capacity(), NOR, HIC, HIR),
                str, NOR);

    line += "\n";

    if (mapp(my["family"]) && my["family"]["master_name"])
        line += sprintf(" 师  父：" YEL "%s\n" NOR, my["family"]["master_name"]);
    else
        line += sprintf(" 师  父：" YEL "无\n" NOR);

    line += sprintf(" 战  绩：杀 %d 人，其中NPC %d 人，其他玩家 %d 人\n",
        my["MKS"] + my["PKS"], my["MKS"], my["PKS"]);

    if (mapp(my["makelove"]) && sizeof(my["makelove"]) > 0) {
        int gender = my["gender"] == "男性";
        int lover = sizeof(my["makelove"]);
        lover = lover > 30 ? 30 : lover;
        line += " 性经验：" HIY + sex_ranking[(lover/10)*2+gender] + NOR;
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

    if (ob->query("balance"))
        line += " 财  富：" + MONEY_D->money_str((int)ob->query("balance"))+"\n\n";
    else
        line+=" 财  富："HIW"没有任何存款"NOR"\n\n";

    if (ob->query("obstacle/number"))
        line += sprintf(RED" 西天取经"NOR"：你已经历了"RED"%s"NOR"道劫难。\n",
            chinese_number(ob->query("obstacle/number")));
    else
        line += RED" 西天取经"NOR"：你还未曾踏上取经之路\n";

    line += "\n";
    
    line += sprintf(" 道行境界：%s           武学境界：%s\n",
                RANK_D->describe_exp(ob->query("combat_exp")),
                RANK_D->describe_skills(ob->query_skills()));
    line += sprintf(" 法力修为：%s           内力修为：%s\n",
                RANK_D->describe_mana(ob->query("max_mana")),
                RANK_D->describe_force(ob->query("max_force")));

    line += YEL"≡≡≡≡≡≡≡≡≡≡ "GRN"西游记"HIY"·"HIG"阿里世界"NOR YEL" ≡≡≡≡≡≡≡≡≡≡≡\n"NOR;
    line += sprintf(" 为了三界和平%s已经历了 %s 的岁月 \n\n",
        ob == me ? "你" : ob->name(1),
        HIR + FINGER_D->age_string( (int)ob->query("mud_age")) + NOR);
    write(line);
    return 1;
}

string display_attr(int gift, int value)
{
    if (value > gift) return sprintf( HIY "%3d" NOR, value );
    else if (value < gift) return sprintf( CYN "%3d" NOR, value );
    else return sprintf("%3d", value);
}

string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor)
{
    string ret;
    int i, n, eff_n, max_n = 12;

    if (max == 0) max = 1;
    n = val * 100 / max / 10;
    eff_n = eff * 100 / max / 10;

    if (n < 0) n = 0;
    if (eff_n < 0) eff_n = 0;
    if (n > max_n) n = max_n;
    if (eff_n > max_n) eff_n = max_n;

    ret = NOR  + bcolor + fcolor ;
    for (i = 0 ; i < max_n; i++) {
        if (i > eff_n) ret += dcolor;
        if (i < n)  ret += "━";
        else ret += HIW"━"NOR;
    }
    ret += fcolor + NOR ;
    return ret;
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

