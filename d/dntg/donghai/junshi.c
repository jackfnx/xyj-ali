inherit NPC;

void create()
{
    set_name("武士",({"wu shi","shi"}));
    set("gender", "男性");
    set("title", "傲来国");
    set("age", 25);
    set("long", "一名傲来国的武士，正在认真的操练。\n");

    set("attitude", "heroism");
    set("combat_exp", 25000);

    set("kee", 400);
    set("max_kee", 400);
    set("sen", 420);
    set("max_sen", 420);
    set("force", 350);
    set("max_force", 350);
    set("mana", 100);
    set("max_mana", 100);
    set("force_factor", 15);
    set("mana_factor", 0);

    set_skill("dodge", 50);
    set_skill("spells", 30);
    set_skill("unarmed", 50);
    set_skill("parry", 50);
    set_skill("spear", 30);

    set("chat_chance", 5);
    set("chat_msg", ({
        "一名武士在场地中央把大枪耍得花里胡哨，引来周围一片喝彩。",
        "武士们聚精会神的操练着队列，可惜始终对不成直线。",
        "两名武士在场地中央叮叮当当的对打，兵器虽然不中，却累得满头大汗。",
    }));

    setup();

    carry_object("/d/obj/weapon/spear/tieqiang")->wield();
    carry_object("/d/obj/cloth/bingfu")->wear();
}
