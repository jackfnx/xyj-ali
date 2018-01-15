// hou.c

inherit NPC;

void random_move();

void create()
{
    set_name("猴子", ({ "hou zi","monkey","hou" }));
    set("race", "野兽");
    set("age", 8);
    set("long", "一只顽皮的小猴子。\n");

    set("str", 30);
    set("cor", 26);
    set("combat_exp", 50);

    set_skill("dodge", 20);
    set_skill("unarmed", 10);
    set("limbs", ({ "头部", "身体", "前爪", "后脚", "尾巴" }));
    set("verbs", ({ "bite", "claw" }));
    setup();
}

void init()
{
    object king = query("king");
    
    set("chat_chance", 10);
    if (present("jing", environment()) || present("mowang", environment())) {
        set("chat_msg", ({
            (: random_move :),
            "\n小猴子吓得到处乱跑。\n",
            "\n猴子们大叫道：＂不好了！不好了！有妖怪啊！＂\n",
            "\n猴子们一边大叫一遍到处乱跑：＂不好了！不好了！狼虫虎豹来捣乱了！怎么办啊！＂\n",
            "\n猴子们大叫道：＂" + (objectp(king) ? "大王，大王，救命啊！" : "不好了！不好了！有妖怪啊！") + "＂\n"
        }));
    } else {
        set("chat_msg", ({
            (: random_move :),
            "小猴子高兴得直翻筋斗。\n",
            "猴子们大叫道：＂要是能在这里安家就好了。＂\n",
            "猴子们交头接耳道：＂就怕其他狼虫虎豹来此作乱。＂\n",
            "猴子们兴奋的大叫道：＂大王，大王，" + (objectp(king) ? king->name()+"是我们的大王" : "谁能做我们的大王啊") + "！＂\n"
        }));
    }
}

void random_move()
{
    object king = query("king");
    object another;
    
    if (objectp(king) && environment(king) == environment()) {
        if ((present("jing", environment()) && random(5) > 4)
        ||  present("mowang", environment())) {
            message_vision("\n猴子们大叫道：＂不好了！不好了！有妖怪啊！＂\n", this_object());
            return;
        }
        another = new(__FILE__);
        another->set("king", king);
        another->move(environment(king));
        king->set_temp("people/" + king->add_temp("people_num", 1), another);
    }
    ::random_move();
}
