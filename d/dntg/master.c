#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

string ask_for_dntg();
string ask_for_detail();

void create()
{
    set_name(HIY "金箍棒" NOR, ({ "jingu bang", "jingubang", "bang", "ruyi"}));
    set_weight(10);
    set("title", HIY "如意" NOR);
    set("gender", "男性");
    set("long", @LONG
这就是当年齐天大圣孙悟空用的兵器。不知为什么，大圣将他留在了花果山。
因为此棍的威力实在太大，所以竟然以力入道，成为一件通灵的兵器。

LONG );
    set("age", 500);
    set("race", "妖魔");
    set("can_speak", 1);
    set("str", 40);
    set("per", 120);
    set("int", 50);
    set("combat_exp", 10000000);
    set_skill("force",  250); 
    set_skill("spells", 250); 
    set_skill("unarmed",250);
    set_skill("dodge",  250);
    set_skill("parry",  250);
    set_skill("stick",  250);
    set_skill("qianjun-bang",  250);
    map_skill("force", "ningxie-force");
    map_skill("stick", "qianjun-bang");
    map_skill("parry", "qianjun-bang");
    set("max_gin", 1000);
    set("eff_gin", 1000);
    set("gin", 1000);
    set("max_kee", 1000);
    set("eff_kee", 1000);
    set("kee", 1000);
    set("max_sen", 1000);
    set("eff_sen", 1000);
    set("sen", 1000);
    set("force", 1300);
    set("max_force", 1300);
    set("mana", 1400);
    set("max_mana", random(800)+1400);
    set("atman", 1500);
    set("max_atman", random(1200)+1500);
    set("force_factor", 50);

    set("no_get", 1);
    set("no_drop", 1);
    set("unit", "条");
    set("material", "gold");
    set("weapon_prop/damage", 800);
    set("replace_file", "/d/obj/weapon/stick/bintiegun");
    set("wield_msg", "$N一伸手，连喝几声：大！大！大！掌中忽然多了一条$n。\n");
    set("unwield_msg", "$N一吹气，几声轻喝：小！小！小！$n在$N掌中转了几转，忽然不见了。\n");

    setup();
}

void init()
{
    object ob = this_player();
    
    if (environment() == environment(ob)
    &&  !OBSTACLES_D->check_obstacles(ob, "dntg")) {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }

    add_action("do_swear", "swear");
}

void greeting(object ob)
{
    object me = this_object();
    if (environment() != environment(ob)) return;
    
    command("say hi, " + RANK_D->query_respect(ob) + "想不想办两件大事出出名啊？\n");
    set("inquiry", ([
        "大事" : "要说这大事嘛，当然是首推大闹天宫啦！\n",
        "大闹天宫" : (: ask_for_dntg :),
        "dntg" : (: ask_for_dntg :),
        "除非什么" : (: ask_for_detail :),
    ]));
}

string ask_for_dntg()
{
    object ob = this_player();
    if (OBSTACLES_D->check_obstacles(ob, "dntg"))
        return "你不是自己也曾经做过吗，还问我？";
    command("say 要说这大闹天宫，乃是当初齐天大圣孙悟空的壮举。");
    command("say 如今天时地利不再，恐怕没有人能复制");
    ob->set_temp("pending/ask_for_detail", 1);
    return "除非。。。";
}

string ask_for_detail()
{
    object ob = this_player();
    if (!ob->query_temp("pending/ask_for_detail")) {
        command("?");
        return "你这人说话怎么前言不搭后语的？";
    }
    command("say 除非接受大爷我的指点。");
    command("hehe");
    ob->delete_temp("pending/ask_for_detail");
    return RANK_D->query_respect(ob) + "要是愿意，就发一个誓(swear)，说你要大闹天宫。";
}

int accept_fight(object ob)
{
    return 0;
}

void unconcious()
{
    message_vision("\n$N突然化作一道金光飞向天际，不见了。\n", this_object());
    destruct(this_object());
}

void die()
{
    unconcious();
}

int do_swear(string arg)
{
    object ob = this_player();
    if (environment() == ob) return 0;
    if (OBSTACLES_D->check_obstacles(ob, "dntg")) return 0;
    if (!arg) return notify_fail("你要发出什么誓言？\n");
    message_vision("\n$N指天发誓：我要 " + arg + " ！\n", ob);
    if (arg != "大闹天宫") {
        tell_object(ob, "可是什么也没有发生。\n");
        return 1;
    }
    message_vision("倏的一声，$n自动飞进了$P的怀里。\n", ob, this_object());
    move(ob);
    return 1;
}
