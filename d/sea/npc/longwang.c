// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//Changed by sjmao, 09-10-97
#include <skill.h>

inherit NPC;

string expell_me(object me);

void create()
{
    set_name("敖广", ({"ao guang", "ao","guang","longwang","wang"}));

    set("long",@LONG
敖广是东海的龙王，其兄弟分别掌管东，西，南，北四海。
旗下水族众多，声势浩大，俨然独霸一方。
LONG);
    set("gender", "男性");
    set("age", 66);
    set("title", "东海龙王");
    set("class","dragon");
    set("attitude", "peaceful");
    set("shen_type", 1);
    set("combat_exp", 1260000);
    set("rank_info/respect", "陛下");
    set("rank_info/rude", "老泥鳅");
    set("per", 20);
    set("str", 30);
    set("max_kee", 3000);
    set("max_gin", 400);
    set("max_sen", 800);
    set("force", 3000);
    set("max_force", 1500);
    set("force_factor", 120);
    set("max_mana", 800);
    set("mana", 1600);
    set("mana_factor", 40);
    //set("chat_msg", ({
    //    "敖广气愤地说道：该死的孙猴子，把我们东海龙宫的定海神针给抢走了。\n",
    //    "敖广长叹一声：不知何时才能将镇宫之宝收回啊！\n",
    //    "敖广悄悄对你说：听说孙猴子把它藏在花果山的石洞里，不知是否属实。\n",
    //    "敖广叹道：若有人能将其送还，龙宫上下定将感激不尽！\n",
    //}));
    //set("chat_chance", 5);

    set("combat_exp", 500000);
    set_skill("unarmed", 100);
    set_skill("dodge", 120);
    set_skill("force", 120);
    set_skill("parry", 100);
    set_skill("fork", 110);
    set_skill("spells", 100);
    set_skill("seashentong", 100);
    set_skill("dragonfight", 100);
    set_skill("dragonforce", 120);
    set_skill("fengbo-cha", 110);
    set_skill("dragonstep", 120);
    map_skill("spells", "seashentong");
    map_skill("unarmed", "dragonfight");
    map_skill("force", "dragonforce");
    map_skill("fork", "fengbo-cha");
    map_skill("parry", "fengbo-cha");
    map_skill("dodge", "dragonstep");

    set("inquiry", ([
        "祖龙": "老祖宗受伤很重，目前正在疗伤，地点不便透露。\n",
        "敖鸾": "敖鸾？敖鸾是谁？没听说过。\n",
        "离宫": (: expell_me :),
        "leave": (: expell_me :),
        ]));

    create_family("东海龙宫", 2, "水族");
    set_temp("apply/armor",50);
    set_temp("apply/damage",25);
    setup();

    carry_object("/d/sea/obj/longpao")->wear();
}

void init()
{
    ::init();
    add_action("do_agree", "agree");
}

int accept_object(object who, object ob)
{
    if ((string)ob->query("id") == "jingu bang" ) {
        command("sigh");
        call_out("destroy", 1200, ob);
        if (who->query("combat_exp") < 400000 || who->query_skill("unarmed", 1) <150) {
            command("say 一根破棍子，哪比得我东海龙宫的镇宫之宝啊！\n");
            command("say 他日" + RANK_D->query_respect(who) + "若能找回真的定海神针，小王定要重谢。\n");
            return 1;
        }
        command("say 虽然不是真的宝物，" + RANK_D->query_respect(who) + "也算是有心人了。\n");
        command("say 我可以传授一些基本拳脚功夫，" + RANK_D->query_respect(who) + "还要抓紧学才是！\n");
        who->set_temp("temp/learn", 1);
        call_out("unsetlearn", 1200, who);
        return 1;
    }
    else return notify_fail("龙王摇摇头，好象不屑一顾的样子。\n");
}

void destroy(object ob)
{
    destruct(ob);
    return;
}

void unsetlearn(object ob)
{
    if (find_player(ob->query("id"))) {
        ob->set_temp("temp/learn", 0);
        ob->save();
    }
}

int recognize_apprentice(object me)
{
    string *reject_msg = ({
        "说道：您太客气了，这怎么敢当？\n",
        "像是受宠若惊一样，说道：请教？这怎么敢当？\n",
        "笑著说道：您见笑了，我这点雕虫小技怎够资格「指点」您什么？\n",
    });

    if (me->query_temp("temp/learn"))
        return 1;
    return notify_fail(name() + reject_msg[random(sizeof(reject_msg))]);
}

int prevent_learn(object me, string skill)
{
    if (me->query("family/family_name") != "东海龙宫" && skill != "unarmed") {
        command("shake");
        command("say 不是说好了只能指点一些基本拳脚吗？");
        return 1;
    }
    return 0;
}

void attempt_apprentice(object ob)
{   
    if (((int)ob->query("combat_exp") < 100000)) {
        command("say " + RANK_D->query_respect(ob) +
            "还是先到小儿或小女处把基础打好了再来我这儿吧。\n");
        return;
    }
    command("smile");
    command("say 难得" + RANK_D->query_respect(ob) +
        "有此心志，还望日后多加努力，为我东海龙宫争光。\n");
    command("recruit " + ob->query("id") );
    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "dragon");
}

string expell_me(object me)
{
    me = this_player();
    if ((string)me->query("family/family_name")=="东海龙宫") {
        me->set_temp("betray", 1);
        command("sigh");
        return ("你要离开我也不能强留。只是按我东海规矩，却须受罚。\n"
"恐怕既是身非龙类，这龙神心法与博击并不能如前般运转，你可愿意(agree)?\n");
    }
    return ("去问问袁先生吧，或许他知道！\n");
}

int do_agree(string arg)
{
    object me;
    me = this_player();
    if (me->query_temp("betray")) {
        message_vision("$N答道：弟子愿意。\n\n", me);
        command("say 人各有志，既是" + RANK_D->query_respect(me)
            + "不愿留在东海，就请出宫去吧。只是江湖险恶，" + RANK_D->query_respect(me)
            + "当好自为之。。。\n");
        me->set_skill("dragonforce", (int)me->query_skill("dragonforce",1)/2);
        me->set_skill("dragonfight", (int)me->query_skill("dragonfight",1)/2);
        me->set("combat_exp", me->query("combat_exp")*95/100);
        me->delete("family");
        me->delete("class");
        me->set("title", "普通百姓");
        me->set_temp("betray", 0);
        me->add("betray/count", 1);
        me->add("betray/longgong", 1);
        me->save();
        return 1;
    }
    return 0;
}

