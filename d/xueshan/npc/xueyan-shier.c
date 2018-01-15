//xueyan-shier.c
//hehe, this npc is interesting:D...weiqi, 97.09.15

inherit NPC;
void create()
{
    set_name("雪雁侍儿", ({"xueyan shier", "shier", "xueyan"}));
    set("gender", "女性");
    set("title", "丫鬟");
    set("age", 16);
    set("long", "孔雀公主的贴身丫鬟，与孔雀公主关系亲密，雪山上下都要让她三分。\n");
    set("class", "yaomo");
    set("combat_exp", 25000);
    set("attitude", "peaceful");
    create_family("大雪山", 4, "弟子");
    set_skill("unarmed", 30);
    set_skill("dodge", 30);
    set_skill("parry", 30);
    set_skill("blade", 30);
    set_skill("ice-blade", 30);
    set_skill("peripateticism", 30);
    set_skill("force", 30);   
    set_skill("iceblood-force", 30);
    map_skill("force", "iceblood-force");
    map_skill("blade", "ice-blade");
    map_skill("dodge", "peripateticism");

    set("per", 21);
    set("max_kee", 300);
    set("max_sen", 300);
    set("force", 300);
    set("max_force", 250);
    set("force_factor", 5);
    setup();

    set("eff_dx", -8000);
    set("nkgain", 60);

    carry_object("/d/obj/cloth/skirt")->wear();
    carry_object("/d/obj/cloth/shoes")->wear();
    carry_object("/d/obj/weapon/blade/iceblade")->wield();
}
void init()
{
    object ob=this_player();
    object me=this_object();

    ::init();

    if ((string)ob->query("gender")=="男性"
    &&  (int)me->visible(ob)
    &&  (string)environment(me)->query("short")=="女弟子卧房") {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }
}
void greeting(object ob)
{
    if (!ob || environment(ob) != environment()) return;

    switch (random(1)) {
        case 0:
            command("chat* 只听雪雁高声叫道：" + ob->query("name") + "，你这个臭流氓！居然闯到女弟子卧房来了！\n");
            command("kick " + ob->query("id"));
            break;
    }
}
