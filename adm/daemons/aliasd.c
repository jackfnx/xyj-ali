
// aliasd.c

mapping global_alias = ([
    "l":   "look",
    "n":   "go north",
    "e":   "go east",
    "w":   "go west",
    "s":   "go south",
    "nu":   "go northup",
    "eu":   "go eastup",
    "wu":   "go westup",
    "su":   "go southup",
    "nd":   "go northdown",
    "ed":   "go eastdown",
    "wd":   "go westdown",
    "sd":   "go southdown",
    "ne":   "go northeast",
    "se":   "go southeast",
    "nw":   "go northwest",
    "sw":   "go southwest",
    "u":   "go up",
    "d":   "go down",
    "i":   "inventory",
    "bai":   "apprentice", // 拜
    "shou":   "recruit", // 收
    "zhu":   "expell", // 逐
    "xue":   "learn", // 学
    "fangqi":   "abandon", // 放弃
    "jineng":   "skills", // 技能
    "jifa":   "enable", // 技法
    "jiali":   "enforce", // 加力
    "lianxi":   "practice", // 练习
    "dazuo":   "exercise", // 打坐
    "mingsi":   "meditate", // 冥思
    "tuna" :   "respirate", // 吐纳
    "qujing" :   "obstacles",
    "dntg" : "obstacles -dntg",
]);

string process_global_alias(string arg)
{
    string *word;

    if (arg[0]=='\'') return "say " + arg[1..strlen(arg)-1];

    word = explode(arg, " ");
    if (sizeof(word) && !undefinedp(global_alias[word[0]])) {
        word[0] = global_alias[word[0]];
        return implode(word, " ");
    }

    return arg;
}
