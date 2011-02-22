// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//xiwangmufake.c
inherit NPC;
inherit F_MASTER;

string miekou();

void create()
{
        set_name("西王母", ({"xi wangmu", "xi", "wangmu","master"}));
        set("long", "西华至妙生伊川，穆王八骑访昆仑。\n");
        set("title", "月宫祖师");
        set("gender", "女性");
        set("age", 100);
        set("class","xian");
        set("attitude", "friendly");
        set("rank_info/respect", "老太太");
        set("cor", 30);
        set("per", 30);
        set("looking", "无精打采，神态木讷。");
        set("max_kee", 4500);
        set("max_gin", 800);
        set("max_sen", 4500);
        set("force", 4000);
        set("max_force", 2000);
        set("force_factor", 125);
        set("max_mana", 2000);
        set("mana", 4000);
        set("mana_factor", 100);
        set("combat_exp", 2000000);
        set_skill("literate", 150);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("force", 180);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("spells", 180);
        set_skill("moonshentong", 180);
        set_skill("baihua-zhang", 180);
        set_skill("moonforce", 180);
        set_skill("snowsword", 200);
        set_skill("moondance", 150);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");
        set("inquiry", ([
            "妲己": (: miekou :),
            "轩辕古墓": (: miekou :),
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
            (: cast_spell, "arrow" :),
        }) );

        create_family("月宫", 1, "红");
        setup();

        carry_object("/d/obj/cloth/tianyi.c")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void attempt_apprentice(object ob)
{
    if (!((string)ob->query("gender") == "女性")) {
        command("shake");
        command("say 我们月宫只收女徒，这位" + RANK_D->query_respect(ob) + "还是另请高就吧。\n");
        return;
    }

    if ((string)ob->query("family/family_name") == "月宫") {
        if (((int)ob->query("combat_exp") < 100000)) {
            command("say " + RANK_D->query_respect(ob) +
                "的道行不够高深，有些绝学秘法恐怕难以领悟。\n");
            return;
        }
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
            "多加努力，把我们月宫发扬光大。\n");
        command("recruit " + ob->query("id") );
        return;
    }
    
    command("shake");
    command("say " + RANK_D->query_respect(ob) +
        "还是先去学些基础功夫吧。\n");
    return;
}

int accept_fight(object me)
{
    return 0;
}

string miekou()
{
    object who, here, there;
    who = this_player();
    here = environment();
    there = load_object("/d/gumu/dajiroom");
    message_vision(this_object()->name() + "顿时脸色一变，挥手招出一团云雾，罩住了$N\n", who);
    who->move(there);
    tell_room(here, "云雾散去，" + who->name() + "不见了。\n而" + this_object()->name() + "却露出神秘的笑容。\n");
    tell_object(who, "云雾散去，你发现自己处于一个陌生的地方。\n");
    tell_room(there, "忽然，一团云雾升起，" + who->name() + "出现在这里。\n", who);
    return "这个孩子啊，这也是你该问的吗？呵呵～～～";
}
