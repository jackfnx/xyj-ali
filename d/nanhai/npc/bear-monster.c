// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// bear-monster.c 黑熊怪
// By Dream Dec. 20, 1996

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("黑熊怪", ({ "bear monster", "bear", "monster" }));
    set("title", "守山大神");   
    set("long", @LONG

黑熊怪本是山野间的一位妖王，因为得罪了心猿悟空差点被打死。
幸好，观音菩萨慈悲为怀救下了他。
他感激菩萨救命之恩，做了普陀山的守山大神。
LONG);
    set("gender", "男性");
    set("age", 30);
    set("attitude", "heroism");
    set("per", 9);
    set("rank_info/self", "黑熊");
    set("rank_info/rude", "熊怪");
    set("max_kee", 1000);
    set("max_gin", 600);
    set("max_sen", 1000);
    set("force", 2000);
    set("max_force", 1000);
    set("force_factor", 75);
    set("max_mana", 1000);
    set("mana", 2000);
    set("mana_factor", 55);
    set("combat_exp", 750000);
    set_skill("literate", 50);
    set_skill("spells", 120);
    set_skill("buddhism", 100);
    set_skill("unarmed", 120);
    set_skill("jienan-zhi", 125);
    set_skill("dodge", 120);
    set_skill("lotusstep", 100);
    set_skill("parry", 125);
    set_skill("force", 105);
    set_skill("lotusforce", 105);
    set_skill("staff", 120);
    set_skill("lunhui-zhang", 130);

    map_skill("spells", "buddhism");
    map_skill("unarmed", "jienan-zhi");
    map_skill("dodge", "lotusstep");
    map_skill("force", "lotusforce");
    map_skill("parry", "lunhui-zhang");
    map_skill("staff", "lunhui-zhang");

    set("chat_chance_combat", 80);
    set("chat_msg_combat", ({
        (: cast_spell, "bighammer" :),
        (: cast_spell, "jingang" :),
    }) );
    create_family("南海普陀山", 2, "弟子");

    setup();
    carry_object("/obj/cloth")->wear();
    carry_object("/d/nanhai/obj/jingu3");
//   carry_object("/d/nanhai/obj/jingu3");
}

void attempt_apprentice(object ob)
{
    if ((string)ob->query("family/family_name")=="南海普陀山") {
        command("smile");
        command("say 很好，我就收下你，希望你多加努力，早成正果。\n");
        command("recruit " + ob->query("id") );
        return;
    }

    command("shake");
    command("say " + "菩萨不让我随便收外人为徒。\n");
    return;
}

