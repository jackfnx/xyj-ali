// ALi by NewX

#include <ansi.h>

inherit NPC;

string give_smelter();

void create()
{
    set_name("袁天罡", ({"yuan tiangang", "yuan"}));
    set("gender", "男性" );
    set("age", 33);
    set("long", "袁天罡是天监台总管，听说他法术高深。\n"
                "他为人正直仗义，脸上总是一股忧国忧民的神情。\n");
    set("int", 30);
    set("per", 25);
    set("combat_exp", 50000);
    set("attitude", "friendly");
    set("title", "天监台正先生");
    set_skill("unarmed", 60);
    set_skill("dodge", 50);
    set_skill("parry", 50);
    set_skill("spells", 100);
    set_skill("baguazhou", 100);
    set_skill("literate", 50);
    set_skill("sword", 60);  
    set_skill("changquan", 50);  

    map_skill("spells", "baguazhou");
    map_skill("unarmed", "changquan");

    set("per", 30);
    set("max_kee", 400);
    set("max_gin", 400);
    set("max_sen", 400);
    set("force", 450);
    set("max_force", 300);
    set("force_factor", 10);
    set("mana", 450);
    set("max_mana", 300);
    set("mana_factor", 5);

    set("inquiry", ([
        "fabao": (: give_smelter :),
        "make_fabao": (: give_smelter :),
        "法宝": (: give_smelter :),
        "炼制法宝": (: give_smelter :)
        ]));

    setup();
    add_money("silver", 5);
    carry_object("/d/obj/cloth/baguapao")->wear();
    carry_object("/d/obj/weapon/sword/taomujian")->wield();
}

int accept_fight(object me)
{
    write("袁天罡凛然道：学武乃是为了强身，不是打打杀杀！\n");
    return 0;
}

int recognize_apprentice(object me)
{
    if ((int)me->query("yuan-learn"))
        return 1;
    return notify_fail("袁天罡说道：您太客气了，这怎么敢当？\n");
}

int accept_object(object who,object ob)
{
    if (ob->query("id")=="fan he") {
        if (((string)who->query("family/family_name")=="将军府")) {
            who->set("yuan-learn", 1);
            write("袁天罡笑道：将军看起来一表人才，以后定是人前出头之辈！\n");
            write("袁天罡略为沉思，又道：若将军有何问题，可随时和我商讨，天罡若是知晓，定会答复．\n");
            call_out("destroy", 1, ob);
            return 1;
        }
        else {
            command("say 多谢多谢，我正饿着哪！");
            command("give 1 silver to " + who->query("id"));        
            call_out("destroy", 1, ob);
            return 1;
        }
    }
    else return 0;
}

void destroy(object ob)
{
    destruct(ob);
    return;
}

string give_smelter()
{
    object me = this_player();
    object smelter;
    
    if (me->query("combat_exp") <= 20000)
        return ("你问这干嘛，年轻人要脚踏实地，不要好高骛远。");

    command("say 炼制法宝需要法宝炼制炉。");
    command("say 要说这炉子嘛。。。");
    message_vision(CYN"$N对着$n上上下下，左左右右，好好的打量了一番。\n"NOR,
        this_object(), me);
    smelter = me->query_temp("smelter");
    if (objectp(smelter)) {
        if (environment(smelter) == me)
            return ("不就在你怀里吗？还问？");
        smelter->move(me);
        command("hehe");
        tell_object(me, "你的法宝炼制炉突然出现在怀里。\n");
        return ("喏，那不就是吗？");
    }
    else {
        smelter = new("/obj/smelter");
        smelter->set_owner(me);
        smelter->move(me);
        message_vision("$N在身后的箱子翻啊翻啊，终于翻出了一个小巧的熔炉，交给了$n。\n",
            this_object(), me);
        return ("拿去吧，免费发送。");
    }
}