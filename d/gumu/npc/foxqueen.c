// ALi by NewX
 
// foxqueen.c 妲己

/************************************************************/

// declarations and variables

#include <ansi.h>
inherit NPC;

/************************************************************/
void create()
{
    set_name("妲己", ({"daji","fox", "fox queen"}));
    set("gender", "女性");
    set("age", 16);
    set("long", @LONG
她就是千年狐狸精妲己。自从殷商灭亡后，她便在轩辕古墓中隐居。她
乃是名垂千古的绝世美人，一颦一笑，如海棠醉日，梨花带雨。
LONG);
    set("title", "九尾天狐");
    set("class", "yaomo");
    set("combat_exp", 1000000);
    set("attitude", "heroic");
    set("per", 50);
    set("int", 30+random(10));
    set("cor", 25+random(5));
    set_skill("unarmed", 100);
    set_skill("dodge", 150);
    set_skill("parry", 150);
    set_skill("spells", 150);
    set_skill("force", 150);
    set_skill("foxforce", 120);
    set_skill("foxphantom", 130);
    set_skill("sword", 150);
    set_skill("firesword", 100);
    set_skill("whip", 150);
    set_skill("lovefire-whip", 150);
    set_skill("moondance", 175);
    set_skill("jingang-quan", 100);
    set_skill("moonforce", 150);
    set_skill("moonshentong", 150);
    set_skill("archery", 150);
    set_skill("xuanyuan-archery", 100);
    set_skill("charm", 200);
    map_skill("force", "foxforce");
    map_skill("spells", "foxphantom");
    map_skill("unarmed", "jingang-quan");
    map_skill("sword", "firesword");
    map_skill("parry", "firesword");
    map_skill("whip", "lovefire-whip");
    map_skill("archery", "xuanyuan-archery");
    map_skill("dodge", "moondance");
    map_skill("charm", "moondance");
    set("max_kee", 1050);
    set("max_sen", 1200);
    set("force", 2000);
    set("max_force", 2000);
    set("force_factor", 150);
    set("mana", 2500);
    set("max_mana", 2500);
    set("mana_factor", 250);
    set("inquiry", ([
        "name": "本座乃大商王后！",
        "here": "这里就是轩辕古墓！",
        "rumors": "这群酒囊饭袋居然把大王骨灰弄丢了！若让老娘查出来，哼哼...",
        "痴梦": "痴梦那小丫头自以为识破了本座的计谋，其实一切尽在本座的掌握。",
        "嫦娥": "嫦娥？呵呵，她现在已经是本座的性奴了...",
        "西王母": "西王母已经被本座亲手轰杀！",
        "月宫": "如今的月宫已完全落入吾手，若有月宫弟子愿意投入本座的门下，本座也愿意收徒。",
       ]));
    create_family("轩辕古墓", 1, "女王");
    set("secret_family_name", "月宫");
    setup();
    carry_object("/d/obj/weapon/sword/fire_sword")->wield();
    carry_object("/d/obj/cloth/huqiu")->wear();
    carry_object("/d/obj/cloth/jingang")->wear();
}

/**************************************************************/
void attempt_apprentice(object me)
{
    string myname = RANK_D->query_rude(me);
    string myid = me->query("id");
    command("look " + myid);
    command("consider");

    if (me->query("gender") != "女性") {
        command("say 臭男人！滚一边去！");
        return;
    }

    if (me->query("family/family_name") != "轩辕古墓" && me->query("family/family_name") != "月宫") {
        command("look " + myid);
        command("say 你是谁啊？");
        return;
    }

    if (me->query("combat_exp") < 200000) {
        command("touch " + myid);
        command("say 小妹妹，你还嫩了点，想拜本座为师还得再修炼哦！");
        return;
    }

    if (me->query("per") < 25) {
        command("say 小妹妹，女人最重要的就是这肉体的姿色，长成你这副德性...");
        command("grin");
        command("say 还是赶紧投胎转世吧！");
        command("kill " + myid);
        return;
    }

    command("grin");
    command("say 做得好，以后多多引诱男人。");
    command("recruit " +myid);
    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "yaomo");
}

/************************************************************/
int prevent_learn(object me, string skill)
{
    if (me->query("family/family_name") == "月宫") {
        if (skill == "fox-force") {
            command("shake");
            command("say 你非狐类，学不了天狐心法。");
            return 1;
        }
    }
    else if (me->query("family/family_name") == "轩辕古墓") {
        if (skill == "moonforce" || skill == "moonshentong") {
            command("shake");
            command("say 本座的天狐心法不比月宫的粗浅功夫强多了，为何要学月宫的武功？");
            return 1;
        }
    }

    return 0;
}

/*********************************************************************/

