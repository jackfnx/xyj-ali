// patrol.c

inherit NPC;

void create()
{
    set_name("巡海夜叉", ({"ye cha","yecha"}));
    set("gender", "男性");
    set("age", 30);
    set("long", "一个巡海的夜叉，长的青面獠牙．\n");

    set("attitude", "peaceful");
    set("class", "dragon");
    set("combat_exp", 30000);
    set("kee", 500);
    set("max_kee", 500);
    set("sen", 600);
    set("max_sen", 600);
    set("force", 700);
    set("max_force", 700);
    set("mana", 800);
    set("max_mana", 800);
    set("force_factor", 20);
    set("mana_factor", 20);
    set("str", 30);

    set_skill("spells", 60);
    set_skill("seashentong", 40);
    set_skill("force", 60);
    set_skill("dragonforce", 60);
    set_skill("fork", 60);
    set_skill("fengbo-cha", 60);
    set_skill("dodge", 100);

    map_skill("spells", "seashentong");
    map_skill("force", "dragonforce");
    map_skill("fork", "fengbo-cha");
    map_skill("parry", "fengbo-cha");

    set("chat_chance", 3);
    set("chat_msg", ({
        (: random_move :),
    }));

    set("combat_chat_chance", 3);
    set("combat_chat_msg", ({
        (: perform_action, "fork", "" :),
    }));

    setup();

    carry_object("/d/obj/armor/tenjia")->wear();
    carry_object("/d/obj/armor/niupi")->wear();
    carry_object("/d/obj/weapon/fork/fork")->wield();
}

