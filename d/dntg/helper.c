#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

#define DNTG_START_ROOM "/d/hgs/inner"
#define HUAG_GETFLAG_ROOM "/d/hgs/shifang"
#define HUAG_WAVE_ROOM "/d/hgs/fall"

string ask_for_dntg();
string ask_for_detail();
void one_hit_to_die(object me, object victim, object weapon, int damage);

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
    set("unit", "条");
    set("race", "妖魔");
    set("limbs", ({ "棒体" }));
    set("can_speak", 1);
    set("rank_info/respect", "金箍棒大人");
    set("rank_info/rude", "死妖怪");
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
    set("replace_file", "/d/obj/weapon/stick/bintiegun");

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
    add_action("do_ba", "ba");
    add_action("override_move", ({ "go", "west", "east", "south", "north" }));
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
    command("say 除非接受本老人家的指点。");
    command("hehe");
    command("say " + RANK_D->query_respect(ob) + "要是愿意，就发一个誓(swear)，说你要“大闹天宫”！");
    ob->delete_temp("pending/ask_for_detail");
    return "本老人家若是心情好，说不定会指点与你。";
}

void reset_action()
{
    set("actions", ([
        "action":     "$N挥动棒体攻击$n的$l",
        "damage_type":   "致命伤",
        "post_action":   (: one_hit_to_die :)
    ]));
}

void one_hit_to_die(object me, object victim, object weapon, int damage)
{
    if (damage > 0) {
        message_vision("$N身上放射出一道毁灭的红光！！！\n", me);
        victim->die();
    }
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

void report_progress(object ob)
{
    string prog = "";
    if (ob->query("dntg/huaguo") != "done")
        prog = "第一件事，你要首先成为花果山水帘洞的群猴之王";
    else if (ob->query("dntg/donghai") != "done")
        prog = "第二件事，你现在已经是花果山水帘洞的群猴之王了，你要操练手下的群猴，将花果山建设成铜墙铁壁";
    else {
        if (OBSTACLES_D->check_obstacles(ob, "dntg")) {
            tell_object(ob, name() + CYN "惊奇的说道：咦？"
                    + RANK_D->query_respect(ob) + "居然已经完成了大闹天宫的壮举！\n" NOR);
            tell_object(ob, name() + CYN "道：佩服佩服！\n" NOR);
            tell_object(ob, name() + CYN "道：我走也！\n" NOR);
            tell_object(ob, name() + "化作一道金光，飞向了天际。\n");
            destruct(this_object());
        }
        return;
    }
    tell_object(ob, name() + CYN "对着你耳朵大叫道：" + prog + "！\n" NOR);
}

int do_swear(string arg)
{
    object ob = this_player();
    if (environment() == ob) return 0;
    if (OBSTACLES_D->check_obstacles(ob, "dntg")) return 0;
    if (!arg) return notify_fail("你要发出什么誓言？\n");
    message_vision("$N指天发誓：我要 " + arg + " ！\n", ob);
    if (arg != "大闹天宫") {
        tell_object(ob, "可是什么也没有发生。\n");
        return 1;
    }
    command("haha");
    command("say 好！好！好！");
    command("say " + RANK_D->query_respect(ob) + "既然由此雄心壮志，本老人家就送你一场造化。");
    message_vision("倏的一声，$n自动飞进了$P的怀里。\n", ob, this_object());
    set_temp("chosen", ob);
    ob->set_temp("dntg_helper", this_object());
    move(ob);
    environment(ob)->open_door();
    
    call_out("report_progress", 3, ob);
    return 1;
}

int do_ba(string arg)
{
    object me;
    object env;
    object qi;

    if ((me = query_temp("chosen")) != this_player())
        return 0;
    if (file_name(env = environment(me)) != HUAG_GETFLAG_ROOM)
        return 0;

    if (!arg || arg != "flag")
        return notify_fail("你要拔什么？\n");
    if (present("flag", me))
        return notify_fail("你不是已经有旗子了吗？\n");
    else if (env->query("getflag"))
        return notify_fail("大旗已经被别人拔走了，这里只留下一截旗杆。\n");
    else if (me->query("dntg/huaguo") == "done")
        return notify_fail("你手握大旗，不禁想起自己当年在此称王的快乐时光。\n");

    if (me->query("kee") <= 200) {
        me->unconcious();
        return 1;
    }
    me->receive_damage("kee", 200);
    if (random(10) < 5)
        message_vision("$N使尽吃奶的力气也没将大旗拔出来。\n", me);
    else {
        qi = new("/d/dntg/huaguo/flag");
        qi->move(me);
        message_vision("$N大喝一声，将大旗拔了下来。\n", me);
        env->set("getflag", 1);
        call_out((: call_other, HUAG_GETFLAG_ROOM, "delete" :), 1200, "getflag");
    }
    return 1;
}

int check_huaguo_waveroom()
{
    object chosen = query_temp("chosen");
    if (!chosen) return 0;
    return file_name(environment(chosen)) == HUAG_WAVE_ROOM;
}

int override_move(string dir)
{
    string verb = query_verb();
    object chosen = query_temp("chosen");
    
    if (verb != "go") dir = verb;
    if (chosen != this_player()) return 0;
    
    switch (file_name(environment(chosen))) {
        case HUAG_GETFLAG_ROOM:
            if (dir == "east" && chosen->query("dntg/huaguo") != "allow") {
                tell_object(chosen, "几只小猴子跑过来冲你喊到：＂我们正在选猴王，没事别来捣乱。＂\n");
                tell_object(chosen, "小猴子又急匆匆的走了。\n");
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}
