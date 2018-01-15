// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Changed by sjmao  09-11-97

inherit NPC;
string expell_me(object me);

void create()
{
    set_name("龙女", ({"long nu","gongzhu","long","princess"}));

    set("long","紫云宫主人，敖广的女儿．\n看上去就是一个娇滴滴的大小姐．\n");
    set("gender", "女性");
    set("age", 20);
    set("int", 25+random(5));
    set("title", "紫云公主");
    set("attitude", "peaceful");
    set("combat_exp", 350000);
    set("rank_info/respect", "公主殿下");
    set("class","dragon");
    set("per", 30);
    set("max_kee", 900);
    set("max_sen", 700);
    set("force", 800);
    set("max_force", 800);
    set("force_factor", 40);
    set("max_mana", 500);
    set("mana", 400);
    set("mana_factor", 30);
    set_skill("literate", 40);
    set_skill("unarmed", 30);
    set_skill("dodge", 50);
    set_skill("force", 30);
    set_skill("parry", 40);
    set_skill("fork", 40);
    set_skill("spells", 50);
    set_skill("seashentong", 50);
    set_skill("dragonfight", 30);
    set_skill("dragonforce", 30);
    set_skill("fengbo-cha", 40);
    set_skill("dragonstep", 50);
    map_skill("spells", "seashentong");
    map_skill("unarmed", "dragonfight");
    map_skill("force", "dragonforce");
    map_skill("fork", "fengbo-cha");
    map_skill("parry", "fengbo-cha");
    map_skill("dodge", "dragonstep");

    set("inquiry", ([
            "敖鸾": "敖鸾那个贱人？你问她干什么？\n",
            "离宫": (: expell_me :),
            "leave": (: expell_me :),
    ]) );

    create_family("东海龙宫", 3, "水族");
    setup();

    carry_object("/d/obj/cloth/pinkskirt")->wear();
    carry_object("/d/sea/obj/yincha")->wield();
}

void attempt_apprentice(object ob)
{
    command("jump");
    command("say 我又多了一个弟子耶！\n");
    command("recruit " + ob->query("id") );
    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "dragon");
}
string expell_me(object me)
{
    me = this_player();
    if ((string)me->query("family/family_name")=="东海龙宫") {
        message_vision("紫云公主斜眼望着$N，一副不耐烦的神色。\n", me);
        return ("你去问我父王吧。\n");
    }
    return ("去问问别人吧！我怎么会知道！n");
}
