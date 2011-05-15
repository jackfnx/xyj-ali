
#include <ansi.h>
#include <combat.h>

inherit NPC;

void set_skills(object);
void endfight();
void reward(object, object, object, int);
void transform();

void create()
{
    set_name("玉兔", ({"yu tu", "tu", "rabbit", "jade rabbit"}));
    set("title", "月宫");
    set("long", "一只活泼可爱的小白兔，红眼睛，三瓣嘴，两只耳朵长乎乎。\n");
    set("gender", "女性");
    set("age", 10);
    set("class", "xian");
    set("rank/respect", "仙兔");
    set("per", 999);
    set("str", 30+random(10));
    set("cor", 40);
    set("cps", 30);
    set("int", 20);
    set("max_sen", 1000);
    set("sen", 1000);
    set("max_kee", 2000);
    set("kee", 2000);
    set("max_mana", 500);

    set("combat_exp", 300);
    set_skill("unarmed", 10);
    set_skill("flower-hand", 10);
    map_skill("unarmed", "flower-hand");
    set_skill("dodge", 20);

    create_family("月宫", 2, "弟子");
    setup();
    set("renxing", 0);

    carry_object("/d/moon/obj/luoyi");
    carry_object("/d/moon/obj/daoyaochu")->wield();
    set("chat_msg", ({
            (: random_move :),
            (: transform :),
    }));
    set("chat_chance", 3);
    set("chat_chance_combat", 4);
    set("chat_msg_combat", ({
            (CYN "玉兔越打越高兴，口中连呼：“好玩，好玩！再打，再打！”\n" NOR),
            (: endfight :),
    }));
}

void transform()
{
    object me = this_object();
    object luoyi = present("luoyi", me);
    if (query("renxing")) {
        message_vision(MAG "$N身形一晃，显出了原型，原来是一个活泼可爱的小白兔。\n" NOR, me);
        set("long", "一只活泼可爱的小白兔，红眼睛，三瓣嘴，两只耳朵长乎乎。\n");
        set("limbs", ({
                "头部", "颈部", "胸口", "后心", "尾巴", "耳朵",
                "左爪", "右爪", "腰间", "小腹", "前腿", "后腿",
                "前爪", "后爪" }));
        set("age", 10);
        set("rank/respect", "仙兔");
        setup();
        set("renxing", 0);
        if (luoyi) luoyi->unequip();
    } else {
        message_vision(MAG "$N身形一晃，化作了人形，变成了一个亭亭玉立的少女。\n" NOR, me);
        set("long",
"她原本只是嫦娥的宠物，因吃了嫦娥掉在地上的灵药而成人形。她\n"
"因灵药之事被王母罚去捣药，久而久之竟颇通药道。\n");
        delete("limbs");
        set("age", 16);
        set("rank/respect", "仙子");
        setup();
        set("renxing", 1);
        if (luoyi) luoyi->wear();
    }
}

void attempt_apprentice(object ob)
{
    command("shake");
    command("say 不收！不收！收徒不好玩！\n");
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "xian");
}

void welcome(object ob)
{
    command("xixi " + ob->query("id"));
    message_vision(CYN "$N歪着脑袋说道：你是谁啊？干嘛来月宫啊？\n" NOR, this_object());
    tell_object(ob, GRN "你可以回答(answer): 1.玩 2.拜师 3.走亲戚\n" NOR);
    ob->set_temp("wait_answer/yutu", 1);
}

int do_answer(string arg)
{
    object ob = this_player();
    object me = this_object();
    string str;
    if (!ob || !ob->query_temp("wait_answer/yutu")) return 0;
    if (arg == "1") {
        ob->set_temp("wait_answer/yutu", 0);
        message_vision(CYN "$N答道：我来玩！\n\n" NOR, ob);
        command("wink " + ob->query("id"));
        message_vision("$N迷惑的望着$n，自言自语道：月宫有什么好玩的？冷冷清清的。\n", me, ob);
        command("say 好吧，你接着玩吧。");
        call_out("disappearing", 3);
        return 1;
    }
    else if (arg == "2") {
        ob->set_temp("wait_answer/yutu", 0);
        message_vision(CYN "$N答道：我来拜师！\n\n" NOR, ob);
        command("look " + ob->query("id"));
        if (ob->query("gender") != "女性") {
            command("shake");
            command("say 月宫里都是女孩子，" + RANK_D->query_respect(ob) + "一个大男人来拜什么师啊？\n");
            command("sigh");
            command("say 不愿说就算了");
            call_out("disappearing", 3);
            return 1;
        } else if (ob->query_skill("dodge", 1) > 120 || ob->query_skill("moondance", 1) > 120) {
            command("jump");
            command("say " + RANK_D->query_respect(ob) + "，你好厉害啊！有你这样的人才加入，我们月宫一定可以打败轩辕古墓的。");
            call_out("disappearing", 3);
            return 1;
        } else {
            command("jump");
            command("say 以后又有新伙伴了。");
            command("say 嗯，我看你上去恐怕挺费劲的，不如帮你一把吧。\n");
            message_vision("$N身形突然飞起，钻进了枝叶间。\n", ob);
            ob->move("/d/moon/ontop");
            message_vision("$N突然从桂树枝叶间飞出，轻飘飘的落在地上。\n", ob);
            call_out("disappearing", 3);
            return 1;
        }
    }
    else if (arg == "3") {
        ob->set_temp("wait_answer/yutu", 0);
        message_vision(CYN "$N答道：我来走亲戚！\n\n" NOR, ob);
        command("wink " + ob->query("id"));
        message_vision("$N迷惑的望着$n，自言自语道：走亲戚？没听说过月宫上谁还有亲戚啊？\n", me, ob);
        command("say 该不会。。。是那个人的亲戚吧？");
        message_vision("$N好像突然想起什么似的，脸上露出恐惧的神情，急忙闭嘴不说话了。\n", me);
        call_out("disappearing", 1);
        return 1;
    } else
        return 0;
}

void disappearing()
{
    if (!is_fighting()) {
        message_vision("$N蹦蹦跳跳的离开了。\n", this_object());
        destruct(this_object());
    }
    remove_call_out("disappearing");
    call_out("disappearing", 120);
}

void endfight()
{
    command("surrender");
    if (random(2)) {
        command("say 你打的我好痛，不和你玩了。");
        command("angry");
    } else {
        command("say 不打了，不打了，你太不经打了。");
        command("sigh");
    }
    random_move();
}

void init()
{
    object me = this_player();
    remove_killer(this_player());
    remove_enemy(this_player());

    ::init();
    add_action("do_answer", "answer");
}

int accept_fight(object me)
{
    command("jump");
    command("say 总算有人陪我玩了。");
    kill_ob(me);
    return 1;
}

int kill_ob(object victim)
{
    set_skills(victim);
    return ::kill_ob(victim);
}

void set_skills(object me)
{
    mapping skill = me->query_skills();
    int max_value = 10;
    string *skillnames;

    if (!skill) return;
    skillnames = keys(skill);
    for (int i=0; i<sizeof(skillnames); i++) 
        if (skill[skillnames[i]] > max_value)
            max_value = skill[skillnames[i]];

    if (query("max_force") < me->query("max_force")) 
        set("max_force", me->query("max_force")*(10+random(3))/10);
    if (query("max_mana") < me->query("max_mana")) 
        set("max_mana", me->query("max_mana")*(10+random(3))/10);
    if (query("comat_exp") < me->query("combat_exp")) 
        set("combat_exp", me->query("combat_exp")*(10+random(3))/10);
    set("force", query("max_force"));
    set("mana", query("max_mana"));
    if (query_skill("unarmed") < max_value) {
        max_value = max_value*(10+random(3))/10;
        set_skill("force", max_value);
        set_skill("moonforce", max_value);
        map_skill("force", "moonforce");
        set_skill("spells", max_value);
        set_skill("moonshentong", max_value);
        map_skill("spells", "moonshentong");
        set_skill("unarmed", max_value);
        set_skill("flower-hand", max_value);
        map_skill("unarmed", "flower-hand");
        set_skill("dodge", max_value*2+random(2));
        set_skill("hammer", max_value*2+random(2));
        set_skill("parry", max_value*2);
        set("force_factor", (int)query_skill("force") / 2);
    }
}

varargs int receive_damage(string type, int damage, object who)
{
    object weapon = who->query_temp("weapon");
    int lvl, amount;
    string skill, attack_skill;

    if (objectp(weapon)) {
        if (weapon->query("use_apply_skill"))
            attack_skill = weapon->query("apply/skill_type");
        else
            attack_skill = weapon->query("skill_type");
    }
    else attack_skill = "unarmed";

    skill = who->query_skill_mapped(attack_skill);
    if (skill && type=="kee") {
        lvl = who->query_skill(skill, 1);
        amount = lvl + who->query_skill(attack_skill, 1);
        amount += query_skill("dodge");
        if (SKILL_D(skill)->practice_skill(who)
        &&  lvl*lvl*lvl/10 < (int)who->query("combat_exp"))
            who->improve_skill(skill, amount*(10+random(10))/15, 0);
    }
    delete_temp("no_move");
    return ::receive_damage(type, damage, who);
}

void reset_action()
{
    object me = this_object();
    mapping action;
    mapping new_act = ([]);

    ::reset_action();
    if (!action=query("actions")) return;
    new_act=copy(action);
    if (new_act["post_action"]) 
        new_act["post_action"]= (: reward :);
    else new_act += (["post_action" : (: reward :) ]);
    set("actions", new_act);
}

void reward(object me,object victim, object weapon, int damage)
{
    int lvl = 0;
    string skill = victim->query_skill_mapped("dodge");
    int ammount;

    if (!skill || damage!= RESULT_DODGE) return;
    lvl = victim->query_skill(skill, 1);
    ammount = lvl;
    if (weapon) ammount = query_skill("hammer", 1);
    if (SKILL_D(skill)->practice_skill(victim)
    &&  lvl*lvl*lvl/10 < (int)victim->query("combat_exp"))
        victim->improve_skill(skill, ammount*(10+random(10))/15, 0);
}

