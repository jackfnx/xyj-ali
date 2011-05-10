inherit NPC;

void create()
{
    set_name("崩将军", ({"beng jiangjun","beng","monkey"}));
    set("title","花果山大将");
    set("gender", "男性" );
    set("age", 35);
    set("class", "monkey");
    set("long", "一只成了精的通背猿。\n");
    set("combat_exp", 60000);

    set("attitude", "peaceful");
    set("str",40);
    set_skill("unarmed", 80);
    set_skill("dodge", 110);
    set_skill("parry", 80);
    set_skill("force", 50);
    set("per", 10);
    set("max_kee", 600);
    set("max_gin", 100);
    set("max_sen", 300);
    set("max_force", 400);
    set("force",400);
    set("max_mana",200);
    set("mana",200);
    set("force_factor", 20);

    set("chat_chance", 3);
    set("chat_msg", ({
        "崩将军令旗一摆，群猴顿时操练了起来。\n",
        "崩将军说道：弟兄们，先把战阵操练好，兵器的事大伙不要操心，自有大王解决！\n",
        "崩将军自言自语的说：嗯，把战阵练好，等到大王弄回了兵器，我花果山就是铜墙铁壁了。\n",
    }));

    set("inquiry", ([
        "name" : "我就是花果山水帘洞大将崩将军。\n",
        "here" : "这就是花果山。\n",
        "大王" : "嘿！我家大王就是花果山水帘洞洞主。\n",
        "weapon" : "我们花果山正缺这玩艺，要能搞点来多好！\n",
        "bingqi" : "我们花果山正缺这玩艺，要能搞点来多好！\n",
        "兵器" : "我们花果山正缺这玩艺，要能搞点来多好！\n",
    ]));

    setup();
}

int accept_object(object who, object ob)
{
    object me = this_object();

    if ((string)ob->query("id") != "bing qi") {
        command("say 这玩艺有什么用？");
        command("shake");
        return 0;
    } else if (who->query("dntg/donghai") == "begin"
            ||  who->query("dntg/donghai") == "allow"
            ||  who->query("dntg/donghai") == "done") {
        command("say 兵器已经够用了，不劳大王操心了。\n");
        return 0;
    } else if (random(10) != 1) {
        message_vision("\n$N兴奋的叫道：太好了！要是再多一点儿就更好了。\n",me);
        call_out("destruct_ob", 1, ob);
        return 1;
    } else {
        command("jump");
        command("say 大王，我们的兵器是够用了，您自己也挑一样称手的家伙吧！\n");
        who->set("dntg/donghai", "begin");
        call_out("destruct_ob", 1, ob);
        return 1;
    }
}

void destruct_ob(object ob)
{
    if (ob) destruct(ob);
}
