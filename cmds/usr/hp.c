// ALI by NewX

#include <ansi.h>
#include <sex.h>

inherit F_CLEAN_UP;

string status_color(int current, int max);
string sex_status_color(int current, int max);
#if 0
string bar_string = "                    ";
string rect_string = "■■■■■■■■■■";
string star_string = "※※※※※※※※※※";
string blank_string = "□□□□□□□□□□";

string tribar_graph1(int val, int eff, int max);
string tribar_graph2(int val, int max);
string tribar_graph3(int val, int max, string color);
string fgbg_replace(string fgcolor);
#endif

int main(object me, string arg)
{
    object ob;
    mapping my;
    
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

    printf(" 真元： %s%4d/ %4d %s(%3d%%)" NOR "    灵力： %s%4d / %4d (+%d)\n" NOR,
        status_color(my["gin"], my["eff_gin"]),   my["gin"],   my["eff_gin"],
        status_color(my["eff_gin"], my["max_gin"]),   my["eff_gin"] * 100 / my["max_gin"],
        status_color(my["atman"], my["max_atman"]),   my["atman"], my["max_atman"],
        my["atman_factor"] );
    printf(" 气血： %s%4d/ %4d %s(%3d%%)" NOR "    内力： %s%4d / %4d (+%d)\n" NOR,
        status_color(my["kee"], my["eff_kee"]),   my["kee"], my["eff_kee"],
        status_color(my["eff_kee"], my["max_kee"]),   my["eff_kee"] * 100 / my["max_kee"],
        status_color(my["force"], my["max_force"]),   my["force"], my["max_force"],
        my["force_factor"] );
    printf(" 精神： %s%4d/ %4d %s(%3d%%)" NOR "    法力： %s%4d / %4d (+%d)\n" NOR,
        status_color(my["sen"], my["eff_sen"]),   my["sen"], my["eff_sen"],
        status_color(my["eff_sen"], my["max_sen"]),   my["eff_sen"] * 100 / my["max_sen"],
        status_color(my["mana"], my["max_mana"]), my["mana"], my["max_mana"],
        my["mana_factor"] );

    printf(" 食物： %s%4d/ %4d      " NOR "     潜能： %s%d\n" NOR,
        status_color(my["food"], ob->max_food_capacity()),
        my["food"], ob->max_food_capacity(),
        HIY,
        (int)ob->query("potential") - (int)ob->query("learned_points"));

    printf(" 饮水： %s%4d/ %4d      " NOR,
        status_color(my["water"], ob->max_water_capacity()),
        my["water"], ob->max_water_capacity());
    {
        int year, day, hour;
        year = my["combat_exp"] / 1000; 
        day = (my["combat_exp"] % 1000) / 4;
        hour = (my["combat_exp"] % 4) * 3; 
        printf("     道行： " HIM);
        if(year) printf("%s年", chinese_number(year));
        if(day) printf("%s天", chinese_number(day));
        if(hour) printf("%s时辰", chinese_number(hour));
        if(!year && !day && !hour)  printf("你还没有道行。");
        printf("\n"NOR);
    }

    printf(" ≡─────────────────────────≡\n");
    printf(" 欲火： %s%4d/ %4d " NOR "%s(%3d%%)\n" NOR,
            my["lust"] < EFF_LUST ? HIG : HIR, my["lust"], EFF_LUST,
            sex_status_color(my["lust"], MAX_LUST), my["lust"] * 100 / MAX_LUST
            );
    return 1;
}

string status_color(int current, int max)
{
   int percent;

   if (max > 0) percent = current * 100 / max;
   else percent = 100;
   if (percent > 100) return HIC;
   if (percent >= 90) return HIG;
   if (percent >= 60) return HIY;
   if (percent >= 30) return YEL;
   if (percent >= 10) return HIR;
   return RED;
}

string sex_status_color(int current, int max)
{
   int percent;

   if (max > 0) percent = current * 100 / max;
   else percent = 100;
   if (percent >= 100) return HIR;
   if (percent >= 90) return RED;
   if (percent >= 75) return HIC;
   if (percent >= 60) return HIG;
   if (percent >= 30) return HIY;
   if (percent >= 10) return GRN;
   return CYN;
}

#if 0
string tribar_graph1(int val, int eff, int max)
{
    string bar;

    if (val < eff) {
        bar = RED + rect_string[0..val*20/max-1] + NOR;
        bar += YEL + blank_string[val*20/max..eff*20/max-1] + NOR;
        bar += bar_string[eff*20/max..max];
    } else if (val == eff) {
        bar = RED + rect_string[0..val*20/max-1] + NOR;
        bar += bar_string[val*20/max..max];
    } else if (val > eff) {
        bar = RED + rect_string[0..eff*20/max-1] + NOR;
        bar += HIY + star_string[eff*20/max..val*20/max-1] + NOR;
        bar += bar_string[val*20/max..max];
    }

    return bar;
}

string tribar_graph2(int val, int max)
{
    string bar;
    bar = status_color(val, max);
    bar += rect_string[0..val*20/max-1];
    bar += blank_string[val*20/max..max];
    bar += NOR;
    return bar;
}

string tribar_graph3(int val, int max, string color)
{
    string bar;
    bar = fgbg_replace(color);
    bar += bar_string[0..val*20/max-1];
    bar += NOR;
    bar += bar_string[val*20/max-1..max];
    return bar;
}

string fgbg_replace(string fgcolor)
{
    string bgcolor = fgcolor;
    bgcolor = replace_string(bgcolor, BLK, BBLK);
    bgcolor = replace_string(bgcolor, RED, BRED);
    bgcolor = replace_string(bgcolor, GRN, BGRN);
    bgcolor = replace_string(bgcolor, YEL, BYEL);
    bgcolor = replace_string(bgcolor, BLU, BBLU);
    bgcolor = replace_string(bgcolor, MAG, BMAG);
    bgcolor = replace_string(bgcolor, CYN, BCYN);
    return bgcolor;
}
#endif

int help(object me)
{
    write(@HELP
指令格式 : hp
           hp <对象名称>                   (巫师专用)

这个指令可以显示你或指定对象(含怪物)的精, 气, 神数值。

see also : score
HELP
    );
    return 1;
}
