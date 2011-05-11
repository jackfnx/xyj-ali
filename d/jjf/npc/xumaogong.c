
inherit NPC;

void create()
{
    set_name("徐茂功", ({"xu maogong", "xu", "xumaogong", "master"}));
    set("long", @LONG

徐茂功是秦琼的义兄，是一众兄弟中唯一的文官。众兄弟降唐后，
徐茂功与众兄弟的关系曾一度疏远，当时有人对此颇有微言。可是
秦琼获罪之后，徐茂功却毅然辞官不做，与秦琼一同归隐。让一众
兄弟打从心里佩服。
LONG);

    set("title", "神算军师");
    set("gender", "男性");
    set("rank_info/self", "贫道");
    set("age", 55);
    set("str", 15);
    set("per", 25);
    set("int", 40);
    set("combat_exp", 40000);
    set_skill("literate", 200);
    set_skill("spells", 150);
    set_skill("baguazhou", 100);
    set_skill("force", 30);
    set_skill("lengquan-force", 30);
    set_skill("dodge", 30);
    set_skill("yanxing-steps", 30);
    set_skill("parry", 30);
    set_skill("unarmed", 30);
    set_skill("changquan", 30);
    set_skill("sword", 40);
    map_skill("spells", "baguazhou");
    map_skill("force", "lengquan-force");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "yanxing-steps");
    set("max_sen", 1000);
    set("max_kee", 300);
    set("force", 200);
    set("max_force", 200);
    set("force_factor", 10);
    set("mana", 700);
    set("max_mana", 700);
    set("mana_factor", 70);

    create_family("将军府", 2, "军师");
    setup();

    carry_object("/d/obj/cloth/daopao")->wear();
}

int accept_fight(object me)
{
    command("say 老夫手重，若是伤人反而不美了。\n");
    return 0;
}

void attempt_apprentice(object me)
{
    command("hehe");
    command("say 贫道来者不拒，不过学不学得成，就是你的造化了。");
    command("recruit " + me->query("id"));
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "fighter");
}