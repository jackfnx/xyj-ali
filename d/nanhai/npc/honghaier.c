// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// honghaier.c 红孩儿
// By Dream Dec. 20, 1996

inherit NPC;

void create()
{
    set_name("红孩儿", ({ "honghaier", "hong" }));
    set("title", "圣婴大王");
    set("long", @LONG
他本是牛魔王之子，生性好斗；后被南海观音擒到这普陀山上做了个
善财童子。可他仍然桀骜不驯，时刻想着反咬一口，幸好观音给他带
上了金箍咒，才让他乖巧了许多。
LONG);
    set("gender", "男性");
    set("age", 15);
    set("attitude", "heroism");
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
    set_skill("literate", 80);
    set_skill("spells", 100);
    set_skill("taiyi", 100);
    set_skill("unarmed", 100);
    set_skill("moyun-shou", 100);
    set_skill("dodge", 100);
    set_skill("moshenbu", 100);
    set_skill("parry", 100);
    set_skill("force", 100);
    set_skill("lengquan-force", 100);
    set_skill("spear", 120);
    set_skill("huoyun-qiang", 150);
    map_skill("spells", "taiyi");
    map_skill("unarmed", "moyun-shou");
    map_skill("dodge", "moshenbu");
    map_skill("force", "lengquan-force");
    map_skill("parry", "huoyun-qiang");
    map_skill("spear", "huoyun-qiang");
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: cast_spell, "qiankun" :),
        (: cast_spell, "zhenhuo" :),
    }) );

    create_family("火焰山", 2, "弟子");

    setup();
    carry_object("/obj/money/gold");
    carry_object("/obj/money/gold");
    carry_object("/obj/cloth")->wear();
    carry_object("/d/nanhai/obj/jingu2");
    carry_object("/d/nanhai/obj/huojianqiang")->wield();
}

void attempt_apprentice(object ob)
{
    command("smile");
    command("say 很好，本大王就收下你，希望你多加努力，能给本大王分忧。\n");
    command("recruit " + ob->query("id") );
    return;
}

