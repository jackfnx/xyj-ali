//sgzl

inherit NPC;

void create()
{
    set_name("小金鱼", ({"xiao jin yu", "xiao yu", "fish", "yu"}));
    set("long", "一条小金鱼，正在海中自由自在的游着。\n");

    set("title", "引路使者");
    set("age", 2);
    set("race", "野兽");

    set_skill("dodge", 60);
    set("combat_exp", 10);
    set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }));
    set("verbs", ({ "bite" }));

    setup();
}

void init()
{
    object me = this_object();

    ::init();
    remove_call_out("yinlu");
    call_out("yinlu", 10);
}

void yinlu()
{
    command("west");
    call_out("yinlu1", 10);
}

void yinlu1()
{
    command("east");
    call_out("yinlu2", 10);
}

void yinlu2()
{
    command("north");
    call_out("yinlu3", 10);
}

void yinlu3()
{
    command("east");
    call_out("yinlu4", 10);
}

void yinlu4()
{
    command("south");
    call_out("yinlu5", 10);
}

void yinlu5()
{
    command("west");
    call_out("yinlu6", 10);
}

void yinlu6()
{
    command("south");
    message_vision("$N一摆尾巴不知游到哪里去了。\n", this_object());
    move(__DIR__"mazee");
}


