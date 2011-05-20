// patrol.c

inherit NPC;

mixed ask_for_weapon();
int patrol_move();

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

    set("chat_chance", 50);
    set("chat_msg", ({
        (: patrol_move :),
    }));

    set("combat_chat_chance", 3);
    set("combat_chat_msg", ({
        (: perform_action, "fork", "fengbo" :),
    }));

    set("inquiry", ([
        "兵器": (: ask_for_weapon :),
        "weapon": (: ask_for_weapon :),
        "bingqi": (: ask_for_weapon :),
    ]));

    setup();

    carry_object("/d/obj/armor/tenjia")->wear();
    carry_object("/d/obj/armor/niupi")->wear();
    carry_object("/d/obj/weapon/fork/fork")->wield();
}

void init()
{
    object who = this_player();

    if (who == query("target") && !query("lost")) {
        remove_call_out("greeting");
        call_out("greeting", 1, who);
    }
}

void greeting(object who)
{
    object me = this_object();

    if (who && environment(who) == environment()) {
        message_vision("$N对$n大喝一声：呔！来者何人？东海龙宫岂可乱闯？\n", me, who);
        me->kill_ob(who);
    }
}

int accept_fight(object ob)
{
    if (ob != query("target")) {
        command("say 去去去，一边去，我们这巡逻呢，倒什么乱？");
        return 0;
    }
    
    command("say 呀哈？早看你形迹可疑，居然还自己送上门了。");
    this_object()->kill_ob(ob);
    return 1;
}

void unconcious()
{
    object me = this_object();
    object ob = query("target");
    object killer = query_temp("last_damage_from");
    object pai;
    
    if (killer != ob) {
        message_vision("$N捂着伤口逃走了，临走还留下一句话：『大胆狂徒，居然到到东海龙宫撒野！』\n", me);
        destruct(me);
        tell_object(killer, "\n糟了！你忽然意识到，可能坏了什么人的好事！\n");
    }
    
    set("lost", 1);
    command("say " + RANK_D->query_respect(ob) + "饶命！" + RANK_D->query_respect(ob) + "饶命！");
    message_vision("$N急忙拜倒在地，磕头不已。\n", me);
    command("say 夜叉有眼不识泰山，妄乞赎罪。");
    if (!query("asked")) {
        command("say 不知" + RANK_D->query_respect(ob) + "来我龙宫所为何事？");
        command("say 夜叉愿为您效劳。");
    } else {
        command("say 夜叉愿为" + RANK_D->query_respect(ob) + "您效劳！请随我来，我为您引荐龙王。");
        command("say 这是龙宫的腰牌，您拿好。");
        pai = new("/d/sea/obj/pai");
        pai->move(ob);
        message_vision("$N给你一块水晶腰牌。\n", me);
        pai = new("/d/sea/obj/pai");
        pai->move(me);
        set("chat_msg", 0);
        call_out("lead_the_way", 5, 0);
    }
    
    set("gin", 1);
    set("kee", 1);
    set("sen", 1);
    set("eff_gin", 1);
    set("eff_kee", 1);
    set("eff_sen", 1);
    remove_all_enemy();
}

void die()
{
    unconcious();
}

mixed ask_for_weapon()
{
    object me = this_object();
    object ob = this_player();
    object pai;
    
    if (ob != query("target")) return "我的兵器跟你又有什么关系？";

    set("asked", 1);
    if (!query("lost")) return "兵器？好，我今天就让你尝尝我手中的兵器。";
    else {
        command("say 原来" + RANK_D->query_respect(ob) + "来我龙宫是为了寻一件兵器啊！");
        command("say 请随我来，我为您引荐龙王。");
        command("say 这是龙宫的腰牌，您拿好。");
        pai = new("/d/sea/obj/pai");
        pai->move(ob);
        message_vision("$N给你一块水晶腰牌。\n", me);
        pai = new("/d/sea/obj/pai");
        pai->move(me);
        set("chat_msg", 0);
        call_out("lead_the_way", 5, 0);
        return 1;
    }
}

int patrol_move()
{
    object env = environment();
    string *dirs = ({ "east", "west", "south", "north", "southeast", "northeast", "southwest", "northwest" });
    string dir = dirs[random(sizeof(dirs))];

    if (env->query("exits/" + dir)) { command("go " + dir); return 1; }
    return 0;
}

void navigator_move()
{
    object env = environment();

    if (env->query("exits/east")) { command("go east"); return; }
    if (env->query("exits/eastup")) { command("go eastup"); return; }
    if (env->query("exits/northeast")) { command("go northeast"); return; }
    if (env->query("exits/southeast")) { command("go southeast"); return; }
    message_vision("$N原地转了几个圈，却没动地方，可能是迷路了。\n", this_object());
}

void start_testing(object ob)
{
    object puller;

    puller = new(__DIR__"wire-puller");
    puller->set("owner", ob);
    ob->move(environment());
    ob->start_testing();

    message_vision("$N缓缓退下。\n", this_object());
    destruct(this_object());
}

void lead_the_way(int step)
{
    object me = this_object();
    object ob = query("target");
    object helper = ob->query_temp("dntg_helper");
    object ao;
    
    if (!ob || environment(ob) != environment()) {
        destruct(this_object());
        return;
    }
    
    if (!helper) {
        message_vision("$N忽然身形一晃，消失了。\n", me);
        destruct(me);
        return;
    }
    
    remove_call_out("lead_the_way");
    
    navigator_move();
    if (ao = present("ao guang", environment())) {
        command("say 这就是我们龙王。");
        message_vision("$N给$n的耳边说了些什么。\n", me, ao);
        message_vision("$N缓缓退下。\n", me);
        start_testing(ob);
        return;
    }
    if (step > 20) {
        message_vision("$N看$n七拐八拐，始终不到地方，忽然意识到自己好像被耍了。\n", ob, me);
        message_vision("$N喝到：呔！大胆妖孽！我看你是在耍"+ RANK_D->query_rude_self(ob) +"吧。\n", ob, me);
        message_vision("$N见自己的小聪明被识破，吓得面如土色，再也不敢耍花样了。\n", me);
        command("say " +RANK_D->query_respect(ob)+ "息怒，夜叉再也不敢耍花样了。");
        call_out("goto_aoguang", 2, ob);
        return;
    }

    call_out("lead_the_way", 2, step + 1);
}

void goto_aoguang(object ob)
{
    object me = this_object();
    object helper = ob->query_temp("dntg_helper");

    if (!ob || environment(ob) != environment() || !helper) {
        destruct(me);
        return;
    }
    
    tell_object(ob, "你眼前一晃，来到了一座宫殿之中。\n");
    ob->move(helper->get_palace_room());
    tell_room(environment(me), "周围的水波一阵扭曲，" + ob->name() + "和" + name() + "不见了。\n");
    me->move(helper->get_palace_room());
    tell_room(environment(me), "周围的水波一阵扭曲，" + name() + "领着" + ob->name() + "出现在这里。\n", ({ ob, me }));
    start_testing(ob);
}
