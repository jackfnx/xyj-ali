inherit F_CLEAN_UP;

#include <ansi.h>

mapping obstacles = ([
    "levels" : ([
        "wuzhuang"   : "  1. 五庄观／人参果",
        "baoxiang"   : "  2. 宝象国／碗子山",
        "pingding"   : "  3. 平顶山／莲花洞／压龙山／压龙洞",
        "wuji"       : "  4. 乌鸡国／宝林寺",
        "chechi"     : "  5. 车迟国／三清观",
        "tongtian"   : "  6. 通天河／陈家庄",
        "jindou"     : "  7. 金兜山／金兜洞",
        "nuerguo"    : "  8. 女儿国／解阳山",
        "dudi"       : "  9. 毒敌山／琵琶洞",
        "firemount"  : " 10. 火焰山／翠云山",
        "jilei"      : " 11. 积雷山／摩云洞",
        "jisaiguo"   : " 12. 祭赛国／碧波潭",
        "jingjiling" : " 13. 荆棘岭／木仙庵",
        "xiaoxitian" : " 14. 小西天／小雷音寺",
        "zhuzi"      : " 15. 朱紫国／麒麟山／獬豸洞",
        "pansi"      : " 16. 盘丝岭／盘丝洞／黄花观／紫云山",
        "biqiu"      : " 17. 比丘国／清华庄／清华洞",
        "wudidong"   : " 18. 无底洞／黑松林",
        "qinfa"      : " 19. 钦法国",
        "yinwu"      : " 20. 隐雾山／连环洞",
        "fengxian"   : " 21. 凤仙郡",
        "yuhua"      : " 22. 玉华县／豹头山／虎口洞／竹节山／九曲盘桓洞",
        "jinping"    : " 23. 金平府／青龙山／玄英洞",
        "tianzhu"    : " 24. 天竺国／毛颖山／三连穴",
    ]),
    "rec" : "obstacle",
    "zero_msg" : "尚未西行求取真经。",
    "done_fmt" : "%s西行求取真经已过了%s关：",
    "todo_fmt" : "%s西行求取真经还须过%s关：",
    "over_msg" : "西行求取真经已历尽了所有的难关。",
]);

mapping dntg = ([
    "levels" : ([
        "huaguo" : " 1. 福地洞天称王，四海千山拱伏",
        "donghai": " 2. 东海龙宫探宝，力挚如意金箍",
        "hell"   : " 3. 大闹阎罗地府，九幽十类除名",
        "bmw"    : " 4. 天庭封官授禄，银河放马逞凶",
        "lijing" : " 5. 大败托塔天王，自封齐天大圣",
        "pantao" : " 6. 偷吃蟠桃蟠果，戏耍仙卿仙女",
        "yaochi" : " 7. 计赚赤脚大仙，搅闹蟠桃盛会",
        "laojun" : " 8. 醉闯三十三天，盗取仙丹灵药",
        "erlang" : " 9. 勇斗二郎真君，力退梅山七圣",
        "bagualu": "10. 八卦炉中逃大圣　翻江倒海闹天宫",
    ]),
    "rec" : "dntg",
    "zero_msg" : "还没有做过大事。",
    "done_fmt" : "%s大闹天宫已过了%s关：",
    "todo_fmt" : "%s大闹天宫还须过%s关：",
    "over_msg" : "大闹天宫已经功德圆满。",
]);

varargs mapping query_obstacle_levels(string opt)
{
    return (mapping)(opt == "dntg" ? dntg["levels"] : obstacles["levels"]);
}

varargs int check_obstacles(object who, string opt)
{
    mapping def = opt == "dntg" ? dntg : obstacles;
    return who->query(def["rec"] + "/number") >= sizeof(obstacles);
}

// mode 0: all
// mode 1: only done
// mode 2: only todo
varargs string check_obstacles_long(object who, int mode, int not_self, string opt)
{
    string name = not_self ? who->query("name") : "你";
    mapping def = opt == "dntg" ? dntg : obstacles;
    int size = sizeof(def["levels"]);
    string *names = keys(def["levels"]);
    string *dones = allocate(size);
    string *todos = allocate(size);
    int nb = 0, sb = 0;
    int i;
    string str = "";

    for (i = 0; i < size; i++) {
        dones[i] = "none";
        todos[i] = "none";
    }

    for (i = 0; i < size; i++) {
        if (who->query(def["rec"] + "/" + names[i]) == "done") {
            dones[nb] = def["levels"][names[i]];
            nb++;
        } else {
            todos[sb] = def["levels"][names[i]];
            sb++;
        }
    }

    if (mode != 2) {
        if (nb == 0)
            str += sprintf("%s%s\n", name, def["zero_msg"]);
        else {
            str += sprintf(def["done_fmt"] + "\n", name, chinese_number(nb));
            who->set(def["rec"] + "/number", nb);
            dones = (string *)sort_array(dones, 1);
            for (i = 0; i < nb; i++)
                str += sprintf("    %s\n", dones[i]);
        }
    }
    if (mode != 1) {
        if (sb == 0)
            str += sprintf("%s%s\n", name, def["over_msg"]);
        else {
            str += sprintf(def["todo_fmt"] + "\n", name, chinese_number(sb));
            todos = (string *)sort_array (todos, 1);
            for (i = 0; i < sb; i++)
                str += sprintf("    %s\n", todos[i]);
        }
    }
    return str;
}

varargs string check_obstacles_short(object who, string opt)
{
    mapping def = opt == "dntg" ? dntg : obstacles;
    int size = sizeof(def["levels"]);
    string *names = keys(def["levels"]);
    int nb = 0, sb = 0;
    int i;
    string str = "";

    for (i = 0; i < size; i++) {
        if (who->query(def["rec"] + "/" + names[i]) == "done") nb++;
        else sb++;
    }

    if (nb == 0) return def["zero_msg"];
    else if (sb == 0) return def["over_msg"];
    else return sprintf(def["done_fmt"], "", chinese_number(nb));
}

int xiudao_accelerate(object me, int pot_gain)
{
    return pot_gain + (int)me->query("obstacle/number") * pot_gain / 2 / sizeof(obstacles["levels"]);
}
