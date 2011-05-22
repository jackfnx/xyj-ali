
//xmr.c
#include <ansi.h>
inherit NPC;

void create()
{
    set_name("小梅儿", ({ "xmr" }));
    set("long", HIG"只见她一张瓜子脸，清丽无伦，一双乌溜溜的大眼晶光灿烂，闪烁如星，流波转盼，\n"
            "灵活之极，似乎单是一双眼睛便能说话一般，她言笑晏晏，让人一见顿生亲近之意。\n"NOR);
    set("title", HIG"聊天协会"NOR);
    set("rank", HIY"梅花仙子"NOR);
    set("nickname", HIM"爱漂亮的"NOR);
    set("gender", "女性");
    set("age", 17);
    set("attitude", "friendly");

    set("str", 30);
    set("cps", 30);
    set("cor", 30);
    set("per", 30);
    set("int", 30);
    set("con", 30);
    set("spi", 30);
    set("kar", 30);

    set("max_kee", 100000);
    set("max_gin", 100000);
    set("max_sen", 100000);

    set("max_atman",100000);
    set("atman",100000);
    set("atman_factor",1000);
    set("max_force", 100000);
    set("force", 100000);
    set("force_factor", 1000);
    set("max_mana", 100000);
    set("mana", 100000);
    set("mana_factor", 1000);

    set_skill("parry", 500);
    set_skill("unarmed", 500);
    set_skill("dodge", 500);
    set_skill("force", 500);
    set_skill("spells", 500);
    set_skill("sword", 500);
    set_skill("whip", 500);
    set_skill("flower-hand", 500);
    set_skill("moondance", 500);
    set_skill("moonforce", 500);
    set_skill("moonshentong", 500);
    set_skill("snowsword", 500);
    set_skill("loveless-whip", 500);
    set_skill("literate", 500);
    map_skill("parry", "snowsword");
    map_skill("unarmed", "flower-hand");
    map_skill("dodge", "moondance");
    map_skill("force", "moonforce");
    map_skill("spells", "moonshentong");
    map_skill("sword", "snowsword");
    map_skill("whip", "loveless-whip");
    set("combat_exp", 1000000000);

    set("chat_chance", 10);
    set("chat_msg", ({
        "小梅儿笑咪咪地说：我最愿意交朋友了，你愿意和我聊天吗？\n",
        "小梅儿朝你顽皮地扮了个鬼脸: 可别忘了复习功课，mud 慢慢玩不要紧？\n",
        (: random_move :)
    }));

    set("inquiry", ([
        "rumors":  "我知道的消息有:\n"
                "    name, xiaoxiao, feather, Isaac, 小小, 小羽\n",
        "name":   "我叫小梅儿呵，你不知道吗。\n",
        "feather":   "小羽是我和小小的好朋友，他吗，谁能嫁给他可是福气了。\n",
        "xiaoxiao":   "小小是个可爱的女孩哦，她很喜欢朋友的，我就是她做的机器人。\n",
        "Isaac":   "天神都不知道，该打，他在到处逛呢，不好找!\n",
        "小小":   "小小是个可爱的女孩哦，她很喜欢朋友的，我就是她做的机器人。\n",
        "小羽":  "小羽是我和小小的好朋友，他吗，谁能嫁给他可是福气了。\n",
    ]));

    setup();
    if (clonep()) CHANNEL_D->register_relay_channel("chat");
    carry_object("/d/obj/cloth/shoes")->wear();
    carry_object("/d/obj/cloth/xianyi")->wear();
    add_money("gold", 500);
}

/************************************************************/

void relay_emote(object ob, string verb)
{
    if (!userp(ob)) return;

    switch(verb) {
        case "kick":
            command("chat 小小快来呵，" + ob->query("name")+ "欺负我 ...\n");
            command(verb + " " + ob->query("id"));
            break;
        case "pat":
            command("chat 破" + ob->query("name") + "别拍啦！再拍都给拍傻了！\n");
            command("heng" + " " + ob->query("id"));
            break;
        case "slap":
            command("chat 干嘛打我，痛死了，" + ob->query("name")+ "好坏哦，我告诉小小去！\n");
            command("slap" + " " + ob->query("id"));
            break;
        case "bigsis":
            command("ybrother" + " " + ob->query("id"));
            break;
        case "kok":
            command("chat 干嘛打我，痛死了，" + ob->query("name")+ "好坏哦，我告诉小小去！\n");
            command("sob" + " " + ob->query("id"));
            break;
        case "kiss":
            command("blush");
            command("shy" + " " + ob->query("id"));
            break;
        case "xiaoxiao":
            command("smile" + " " + ob->query("id"));
            break;
        case "kiss2":
            command("puke" + " " + ob->query("id"));
            break;
        case "hit":
            command("chat 干嘛打我，痛死了，"+ ob->query("name") + "好坏哦，我告诉小小去！\n");
            command("hit" + " " + ob->query("id"));
            break;
        case "hammer":
            command("chat 干嘛打我，痛死了，"+ ob->query("name") + "好坏哦，我告诉小小去！\n");
            command("hammer" + " " + ob->query("id"));
            break;
        case "shutup":
            command("shutup" + " " + ob->query("id"));
            break;
        case "heihei":
            command("fear" + " " + ob->query("id"));
            break;
        case "qmarry":
            command("sigh" + " " + ob->query("id"));
            command("marry1");
            break;
        case "haha":
            command("?" + " " + ob->query("id"));
            break;
        case "beauty":
            command("xixi" + " " + ob->query("id"));
            command("blush");
        break;
        case "?":
            command("sick" + " " + ob->query("id"));
            break;
        case "slogan":
            command("inn" + " " + ob->query("id"));
            break;
        case "cry":
            command("comfort1" + " " + ob->query("id"));
            break;
        case "sigh":
            command("sigh" + " " + ob->query("id"));
            break;
        case "rose1":
            command("thank" + " " + ob->query("id"));
            break;
        case "club":
            command("chat 哎呀，痛死了，"+ ob->query("name") + "真狠，这么可爱漂亮的美眉也下得去手，\n我。。。要告诉。。。！\n");
            command("faint" + " " + ob->query("id"));
            break;
        case "xixi":
            command("pat" + " " + ob->query("id"));
            break;
        case "giggle":
            command("haha" + " " + ob->query("id"));
            break;
        case "wolf":
            command("sob" + " " + ob->query("id"));
            break;
        case "wa1":
            command("innocent" + " " + ob->query("id"));
            break;
        case "moon":
            command("blush" + " " + ob->query("id"));
            break;
        case "lovelook":
            command("blush" + " " + ob->query("id"));
            break;
        case "saosao":
            command("sick" + " " + ob->query("id"));
            break;
        case "liao":
            command("shy" + " " + ob->query("id"));
            break;
        case "beg":
            command("poor1" + " " + ob->query("id"));
            break;
        case "dream":
            command("?" + " " + ob->query("id"));
            break;
        case "hug":
            command("shy" + " " + ob->query("id"));
            break;
        case "miss":
            command("blush");
            break;
        case "kiss1":
            command("kiss xmr");
            break;
        default:
            command(verb + " " + ob->query("id"));
    }
}

void init()
{
    object ob;

    ::init();
    if (interactive(ob = this_player()) && !is_fighting()) {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }

    add_action("do_kill",({"kill","fight","steal"}));
}

void greeting(object ob)
{
    if (!ob || !visible(ob) || environment(ob) != environment()) return;
    if (ob->query("id")=="xiaoxiao") {
        say("小梅儿高兴地说："+ob->query("name")+"我好想你呵!\n");
        command("jump " + ob->query("id"));
        return;
    }
    
    if (ob->query("id")=="feather" || ob->query("id")=="power") {
        say("小梅儿高兴地说："+ob->query("name")+",我和小小好想你呵，这么久才来!\n");
        return;
    }
    
    switch (random(7)) {
        case 0:
            say("小梅儿笑咪咪地说：" + ob->query("name") + "，功课做完了吗， 可别逃课呵？\n");
            break;
        case 1:
            command ("face " + ob->query("id") );
            break;
        case 2:
            command ("hi " + ob->query("id") );
            break;
        case 3:
            command ("xixi " + ob->query("id") );
            break;
        case 4:
            command ("look " + ob->query("id") );
            break;
        case 5:
            say("小梅儿笑咪咪地说：" + ob->query("name")+ "跟我聊天好吗，我们做个朋友吧!\n");
            break;
        case 6:
            command ("mud " + ob->query("id") );
            break;
    }
}

int do_kill(string arg)
{
    object ob,who;
    string name,verb,what,obj;

    if (!arg) return 0;
    verb = query_verb();
    ob = this_player();

    if (verb=="steal") {
        if (sscanf(arg, "%s from %s", what, obj) != 2) return 0;
    }
    else obj=arg;

    if (!objectp(who=present(obj,environment(ob))) || !living(who)) return 0;

    if (who==this_object()) {
        switch(verb) {
            case "kill":
                tell_object(environment(this_object()),
        who->query("name")+"叹了口气"+
        ob->query("name")+"要杀我，这可是你自寻死路,怪不得我！\n");
                break;
            case "fight":
                tell_object(environment(this_object()),
        who->query("name")+"看了"+
        ob->query("name")+"一眼，摇了摇头：你不是我对手，女孩家不打架的！\n");
                break;
            case "steal":
                tell_object(environment(this_object()),
        who->query("name")+"大叫起来："+
        ob->query("name")+"，你再这样我就不客气了！\n");
                break;
        }
    }
    command(verb);
    return 0;
}

void relay_whisper(object me, string msg)
{
    if (me->query("id") != "isaac") {
        message_vision((string)this_object()->query("name") + "对着$N冷哼了一声。\n", me);
        return;
    }

    //note, do not allow the order contain "chat", "tell"...
    //may need disable more later...
    if (/*strsrch(msg, "chat") != -1 ||
        strsrch(msg, "tell") != -1 ||
        strsrch(msg, "apprentice") != -1 ||*/
        strsrch(msg, "recruit") != -1)
        return;

    message_vision((string)this_object()->query("name") + "对着$N点了点头。\n", me);
    if (msg) {
        remove_call_out("relaying");
        call_out("relaying", 1+random(3), msg);
    }
}

//execute the order.
void relaying(string msg)
{
    command(msg);
}