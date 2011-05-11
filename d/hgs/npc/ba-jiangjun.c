inherit NPC;

void create()
{
    set_name("芭将军", ({"ba jiangjun","ba","monkey"}));
    set("title", "花果山大将");
    set("gender", "男性");
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
        "芭将军说道：我家大王神勇异常，须用上好的兵器。\n",
        "芭将军自言自语的说：我倒知道个地方可搞些兵器来。\n",
    }));

    set("inquiry", ([
        "name" : "我就是花果山水帘洞大将芭将军。\n",
        "here" : "这就是花果山。\n",
        "大王" : "嘿！我家大王就是花果山水帘洞洞主。\n",
        "weapon" : "大家的兵器，可去傲来国偷些，我家大王的兵器嘛，看来要找些阔气的邻居讨了。\n",
        "bingqi" : "大家的兵器，可去傲来国偷些，我家大王的兵器嘛，看来要找些阔气的邻居讨了。\n",
        "兵器" : "大家的兵器，可去傲来国偷些，我家大王的兵器嘛，看来要找些阔气的邻居讨了。\n",
    ]));

    setup();
}
