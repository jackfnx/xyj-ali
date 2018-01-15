// created 12/18/1997 by snowcat

inherit NPC;

void create()
{
    set_name("双尾蝎", ({ "xiezi jing", "xiezi", "jing" }));
    set("long", "一只双尾蝎。\n");
    //set("race", "野兽");
    set("gender", "女性");
    set("age", 26);
    set("attitude", "heroism");
    set("max_kee", 1500);
    set("max_gin", 1500);
    set("max_sen", 1500);
    set("force", 1200);
    set("max_force", 1200);
    set("force_factor", 30);
    set("max_mana", 600);
    set("mana", 600);
    set("mana_factor", 30);
    set("combat_exp", 450000);

    set_skill("spells", 50);
    set_skill("tao", 50);
    set_skill("unarmed", 45);
    set_skill("pressheart-hand", 45);
    set_skill("dodge", 80);
    set_skill("peripateticism", 70);
    set_skill("parry", 85);
    set_skill("force", 70);
    set_skill("fork", 80);
    set_skill("iceblood-force", 70);
    set_skill("fengbo-cha", 80);
    map_skill("spells", "tao");
    map_skill("unarmed", "pressheart-hand");
    map_skill("fork", "fengbo-cha");
    map_skill("parry", "fengbo-cha");
    map_skill("dodge", "peripateticism");
    map_skill("force", "iceblood-force");
    setup();
}

void unconcious()
{
    object ob;
    object me = this_object();
    object where = environment(me);

    ob = new("/d/xueshan/obj/cookfood");
    ob->set("name", me->query("name"));
    ob->set("cook/type", "xie");
    ob->set("cook/value", 5);
    ob->move(where);
    message_vision("\n$N缩成一团，不再动了。\n",me);
    destruct(me);
}

void die()
{
    unconcious();
}

int test_player(object who)
{
    string *names;
    string name;
    int len;

    if (!who) return 0;

    names = who->query_temp("apply/name");
    if (!names) return 0;
    if (sizeof(names) < 1) return 0;

    name = names[0];
    len = strlen(name);
    if (len < 1) return 0;
    if (name[len-2..len-1] != "鸡") return 0;
    
    return 1;
}

int accept_fight(object ob)
{
    ob->apply_condition("killer", 100);
    kill_ob(ob);
    return 1;
}

void kill_ob(object ob)
{
    object me = this_object();

    set_temp("my_killer", ob);
    call_out("hurting", random(5)+5, me, ob);
    ::kill_ob(ob);
}


void hurting(object me, object ob)
{
    string *msgs =({
        "$N挥起毒刺，向$n一扎！\n",
        "$N一转身，一个倒马桩向$n刺去！\n",
        "$N跳起往$n的头上一扎！\n",
    });
    string *strs =({
        "( $N大叫一声：好痛！ )\n",
        "( $N抱起肿起的头忍不住惨叫一声！ )\n",
        "( $N的头上立刻肿起一大块红红的脑门痈！ )\n",
    });
    int damage;

    if (!me) return;
    if (!ob) return;
    if (environment(ob) != environment(me)) return;

    message_vision("\n"+msgs[random(sizeof(msgs))], me, ob);

    if (!test_player(ob)) {
        message_vision(strs[random(sizeof(strs))], ob);
        damage = ob->query("max_kee")/(7+random(3));
        ob->receive_damage("kee", damage);
        ob->receive_wound("kee", damage);
        ob->receive_damage("sen", damage);
        ob->receive_wound("sen", damage);
    } else {
        message_vision("只见$N发出一声鸡叫，"+
                        "$n顿时慌乱转身收起倒马桩！\n",ob,me);
    }
    remove_call_out("hurting");
    call_out("hurting", random(10)+10, me, ob);
}
