#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

#define DNTG_START_ROOM "/d/hgs/inner"
#define HUAG_GETFLAG_ROOM "/d/hgs/shifang"
#define HUAG_WAVE_ROOM "/d/hgs/fall"
#define HUAG_VOTE_ROOM "/d/hgs/throne"
#define DONH_ASNL_ROOM "/d/4world/arsenal"
#define DONH_DRILL_ROOM "/d/4world/drill"
#define DONH_DRILLENT_ROOM "/d/4world/drillent"
#define DONH_GATE_ROOM "/d/sea/under1"
#define DONH_PLAYG_ROOM "/d/hgs/playground"
#define DONH_PALACE_ROOM "/d/sea/inside3"
#define HELL_BED_ROOM "/d/hgs/ironbridge"
#define HELL_ENT_ROOM "/d/death/new-zhaopo"

#define NPC_BAIWC "/d/death/npc/baiwuchang"
#define NPC_HEIWC "/d/death/npc/heiwuchang"

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
    map_skill("force", "nine-turn");
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

void report_progress(int co)
{
    call_out("do_report_progress", co);
}

void do_report_progress()
{
    string prog = "";
    object ob = query_temp("chosen");
    object foo;
    
    if (!ob) return;
    if (ob->query("dntg/huaguo") != "done") {
        prog = "首先，你要成为花果山水帘洞的群猴之王";
        foo = new(__DIR__"huaguo/flag");
        foo->set("owner", ob);
        foo->place_room(HUAG_GETFLAG_ROOM);
    }
    else if (ob->query("dntg/donghai") == 0) {
        prog = "你已经是花果山的群猴之王了，现在你要做的是操练手下的群猴，将花果山打造成铜墙铁壁";
        foo = new(__DIR__"donghai/rack");
        foo->set("owner", ob);
        foo->move(DONH_ASNL_ROOM);
    }
    else if (ob->query("dntg/donghai") != "done") {
        prog = "走！走！走！去东海！去拿金箍棒！";
        foo = new(__DIR__"donghai/patrol");
        foo->set("target", ob);
        foo->move(DONH_GATE_ROOM);
    }
    else if (ob->query("dntg/hell") == 0) {
        tell_object(ob, name() + CYN "自言自语道：啊哈！接下来又是闹地府！我最喜欢闹地府了！\n" NOR);
        prog = "走！走！走！先去铁板桥上睡觉！";
        foo = new(__DIR__"hell/bed");
        foo->set("owner", ob);
        foo->set("hell_ent_room", HELL_ENT_ROOM);
        foo->set("npc_baiwc", NPC_BAIWC);
        foo->set("npc_heiwc", NPC_HEIWC);
        foo->move(HELL_BED_ROOM);
    }
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

void speak_one(int i)
{
    object ob = query_temp("chosen");
    mixed* msgs = query_temp("speak_msgs");

    remove_call_out("speak_one");
    if (!ob || !msgs || i >= sizeof(msgs)) return;
    if (stringp(msgs[i])) tell_object(ob, name() + msgs[i] + "\n");
    else if (functionp(msgs[i])) evaluate(msgs[i], ob);
    call_out("speak_one", 1, i + 1);
}

void speak(mixed* msgs)
{
    set_temp("speak_msgs", msgs);
    call_out("speak_one", 1, 0);
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
    command("say 除非接受本老人家的指点。");
    command("hehe");
    command("say " + RANK_D->query_respect(ob) + "要是愿意，就发一个誓(swear)，说你要“大闹天宫”！");
    ob->delete_temp("pending/ask_for_detail");
    return "本老人家若是心情好，说不定会指点与你。";
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
    
    report_progress(3);
    return 1;
}

void disappear()
{
    object chosen = query_temp("chosen");
    if (chosen)
        tell_object(chosen, name() + CYN "喝到：" + chosen->name(1) + CYN "！你太让我失望了，你就不是个能做大事的人！\n" NOR);
    message_vision("\n$N突然化作一道金光飞向天际，不见了。\n", this_object());
    destruct(this_object());
}

void unconcious()
{
    set_temp("chosen", 0);
    disappear();
}

void die()
{
    unconcious();
}

int check_room(string room)
{
    object chosen = query_temp("chosen");
    if (!chosen) return 0;
    return file_name(environment(chosen)) == room;
}

int check_huaguo_waveroom()
{
    return check_room(HUAG_WAVE_ROOM);
}

int check_huaguo_voteroom()
{
    return check_room(HUAG_VOTE_ROOM);
}

object get_object(string fname)
{
    if (!find_object(fname))
        load_object(fname);
    return find_object(fname);
}

object get_drillent_room()
{
    return get_object(DONH_DRILLENT_ROOM);
}

object get_drill_room()
{
    return get_object(DONH_DRILL_ROOM);
}

object get_arsenal_room()
{
    return get_object(DONH_ASNL_ROOM);
}

object get_playg_room()
{
    return get_object(DONH_PLAYG_ROOM);
}

object get_palace_room()
{
    return get_object(DONH_PALACE_ROOM);
}
