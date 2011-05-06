#include <ansi.h>

inherit NPC;

string *names = ({"虎精","豹精","狮精","狼精"});
string *ids = ({"hu jing","bao jing","shi jing","lang jing"});

void create()
{
    int ii = random(sizeof(names));
    set_name(names[ii], ({ids[ii], "jing", "monster"}));
    set("race", "野兽");
    set("age", 33);

    set("long", "一只吸取日月精华而成精的猛兽。");

    set("attitude", "aggressive");
    set("combat_exp", (random(5)*10000+50000));
    set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
    set("verbs", ({ "bite"}));

    set("kee", 800);
    set("max_kee", 800);
    set("sen", 1200);
    set("max_sen", 800);
    set("force", 1000);
    set("max_force", 1000);
    set("mana", 500);
    set("max_mana", 500);
    set("force_factor", 30);
    set("mana_factor", 30);
    set("str", 30);

    set_skill("unarmed", random(50)+80);
    set_skill("spells", 100);
    set_skill("yaofa", 100);
    set_skill("force", 100);
    set_skill("ice-force", 100);

    map_skill("force", "ice-force");
    map_skill("spells", "yaofa");

    setup();
}

void init()
{
    add_action("override_move", ({ "go", "west", "east", "south", "north" }));
}

void kill_ob(object ob)
{
    set_temp("my_killer", ob);
    ::kill_ob(ob);
}

void die()
{
    object killer = query_temp("my_killer");
    object mowang, another, env;
    
    if (killer) {
        env = environment();
        if (killer->query_temp("dntg/huaguo/kill_jing") >= 15) {
            foreach (object ob in all_inventory(env)) {
                if (ob == this_object()) continue;
                if (base_name(ob) == base_name(this_object())) {
                    message("vision", HIG "\n" + ob->name() + "逃跑了！\n" NOR, env);
                    destruct(ob);
                }
            }
            if (!present("mowang", env)) {
                mowang = new(__DIR__"mowang");
                mowang->move(env);
                message_vision(HIR "\n只听得一阵「桀桀桀」的笑声，$N" HIR "出现了！\n\n" NOR, mowang);
                mowang->kill_ob(killer);
            }
        }
        else {
            another = new(__FILE__);
            message("vision", HIR "\n又一只" + another->name() + "跑了过来！\n\n" NOR, env);
            another->move(env);
            another->kill_ob(killer);
            killer->add_temp("dntg/huaguo/kill_jing", 1);
        }
    }
    ::die();
}

void unconcious()
{
    die();
}

int override_move(string dir)
{
    string verb = query_verb();
    object killer = query_temp("my_killer");
    
    if (verb != "go") dir = verb;
    if (killer != this_player()) return 0;
    if (!environment()->query("exits/" + dir)) return 0;

    tell_object(killer, name() + "疯狂的向你扑来，挡住了你的去路。\n");
    return 1;
}

