// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// ludongbin.c...weiqi, 98.02.24.

string give_book();
string ask_jinguzhou();

inherit NPC;
void create()
{
    set_name("吕洞宾", ({"lu dongbin", "lu", "dongbin"}));
    set("title", "八仙之");
    set("nickname", "纯阳子");
    set("gender", "男性" );
    set("age", 35);
    set("per", 30);
    set("long", "吕洞宾在神仙中虽然算不得强者，但是在民间的名气却实在大的不得了，文采风流，色胆包天。\n");
    set("class", "xian");
    set("combat_exp", 120000);
    set("attitude", "peaceful");
    set_skill("unarmed", 60);
    set_skill("wuxing-quan", 60);
    set_skill("dodge", 80);
    set_skill("bagua-zhen", 80);
    set_skill("parry", 80);
    set_skill("sword", 90);
    set_skill("xiaofeng-sword", 100);
    set_skill("force", 70);   
    set_skill("zhenyuan-force", 70);
    set_skill("literate", 120);
    set_skill("spells", 80);
    set_skill("taiyi", 80);
    map_skill("spells", "taiyi");
    map_skill("force", "zhenyuan-force");
    map_skill("unarmed", "wuxing-quan");
    map_skill("sword", "xiaofeng-sword");
    map_skill("dodge", "bagua-zhen");

    set("max_kee", 500);
    set("max_sen", 500);
    set("force", 1000);
    set("max_force", 800);
    set("mana", 1600);
    set("max_mana", 800);   
    set("force_factor", 40);
    set("mana_factor", 40);

    set("inquiry", ([
        "name" : "五庄观纯阳子是也。\n",
        "here" : "身在何处？心老普陀。\n",
        "rumors": (: ask_jinguzhou :),
        "心得" : (: give_book :),      
        "纯阳心得" : (: give_book :),
    ]) );

    set("no_book", 0);

    setup();
    carry_object("/d/obj/cloth/xianpao")->wear();
    carry_object("/d/obj/weapon/sword/changjian")->wield();
}

string give_book()
{
    object me = this_player();

    if (query("no_book") == 0)
    {
        carry_object("/d/obj/book/chunyang");
        command("give xinde to " + me->query("id"));
        set("no_book", 1);
        return "吕洞宾说道：好！既然是有心人，那我就给你吧。\n";
    }
    else
    {
        return "吕洞宾说道：太不巧了，我已经送人了。\n";
    }
}

string ask_jinguzhou()
{
    if (this_player() -> query_temp("aware_of_jinguzhou")) 
        return "不都对你说了吗，怎么又来问？\n";
    this_player() -> set_temp("aware_of_jinguzhou", 1);
    command("whisper " + this_player() -> query("id") 
        + " 听说紫竹林里藏有如来所赐的紧箍咒。");
    return "有缘者得之，无缘者弃之。就看您的福气了。\n";
}
