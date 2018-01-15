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
