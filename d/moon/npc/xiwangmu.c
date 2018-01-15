// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//xiwangmu.c
inherit NPC;

void create()
{
    set_name("西王母", ({"xi wangmu", "xi", "wangmu","master"}));
    set("long", @LONG

一个充满成熟女人韵味的女子。
可是，如今的她却被狰狞的锁链死死的锁着，悬挂在空中。她的身上
挂满了淫具：
她的乳房上固定着一对欲火钳，漆黑的金属夹子恶毒的撕咬着娇嫩的
乳蒂，不时还有闪电闪耀着，击打在她的乳峰顶端，一道道乳汁不由
自主的喷射出来，被一副榨乳器收集起来，已经集了好几大瓶，显然
她已经被囚禁很久了；
她的下体中责备插入了一根按摩棒，疯狂的在她的玉门中肆虐着，给
她带来了巨大的快感，让她的阴精不停的喷射着，同样被榨汁器收集
起来，也已经集了好几大瓶。
她所遭受的淫刑让你深深震撼，不过更然你震撼的是这个女子的身体
中隐隐透出的力量，那仿佛是毁灭一切的力量。
你不禁感到诧异，这样强大的的女子又怎么会被俘虏呢？
LONG);
    set("title", "被擒的");
    set("gender", "女性");
    set("age", 30);
    set("class","xian");
    set("attitude", "friendly");
    set("rank_info/respect", "夫人");
    set("cor", 30);
    set("per", 30);
    set("looking", "神色困顿，无精打采。");
    set("max_kee", 4500);
    set("max_gin", 800);
    set("max_sen", 4500);
    set("force", 4000);
    set("max_force", 2000);
    set("force_factor", 125);
    set("max_mana", 2000);
    set("mana", 4000);
    set("mana_factor", 100);
    set("combat_exp", 2000000);
    set_skill("literate", 150);
    set_skill("unarmed", 150);
    set_skill("dodge", 150);
    set_skill("force", 180);
    set_skill("parry", 150);
    set_skill("sword", 150);
    set_skill("spells", 180);
    set_skill("moonshentong", 180);
    set_skill("flower-hand", 180);
    set_skill("moonforce", 180);
    set_skill("snowsword", 200);
    set_skill("moondance", 150);
    map_skill("spells", "moonshentong");
    map_skill("unarmed", "flower-hand");
    map_skill("force", "moonforce");
    map_skill("sword", "snowsword");
    map_skill("parry", "snowsword");
    map_skill("dodge", "moondance");
    set("inquiry", ([
        "name": "我。。。我就是月宫祖师西王母。。。",
        "here": "本座也不知这是哪里啊。。。",
    ]));

    set("no_get", "西王母被锁链牢牢的固定着，根本解不下来。\n");
    set_temp("no_move", 1);
    
    create_family("月宫", 1, "红");
    setup();
}

void attempt_apprentice(object ob)
{
    command("sigh");
    command("say 本座如今已经落入这步田地了，哪里还有心思收徒？\n");
}

int accept_fight(object me)
{
    command("sigh");
    command("say " + RANK_D->query_respect(me)
        + "可真能开玩笑，本座已经落入这步田地了，哪里还能与人交手？\n");
    return 0;
}

mixed set_temp(string prop, mixed data)
{
    if (prop == "no_move") return ::set_temp("no_move", 1);
    else return ::set_temp(prop, data);
}

int delete_temp(string prop)
{
    if (prop == "no_move") return ::set_temp("no_move", 1);
    else return ::delete_temp(prop);
}
