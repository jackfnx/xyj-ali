// ALi by NewX

#include <ansi.h>

inherit NPC;

string *slaver_descs = ({
    "一个纤细柔弱的少年，长相清秀，眉目中带着羞涩的气息，如同一只受惊的小鹿。\n",
    "一个高大健壮的猛男，满脸横肉，表情彪悍。\n",
    "一个手无缚鸡之力的书生，满嘴之乎者也，让人生厌。\n不过他胯下的阳物着实不小，即使不勃起都已经比普通人大很多了。\n",
    "一个细皮嫩肉年轻人，显然是个练家子，似乎功夫还不错，放在世俗里应该也是个高手。\n可惜，这里是妖魔的巢穴，武功在这里没用。\n",
});

string *status_descs = ({
    "此时胯下的凶兽，狰狞怒挺，充满了雄性的气势。",
    "此时眼中流落出恐惧气息，就连胯下硕大的阳根也无精打采的。",
    "此时受到周围环境的影响，居然也不可抑止的高高勃起。",
});

void create()
{
    set_name("精奴", ({"slaver", "boy"}));
    set("title", CYN "牢牢锁住的" NOR);
    set("long", slaver_descs[random(sizeof(slaver_descs))]);
    set("looking", status_descs[random(sizeof(status_descs))]);

    set("gender", "男性");
    set("age", 15+random(20));
    set("per", 20+random(15));
    set("combat_exp", 10000);
    set_skill("dodge", 10);
    set_skill("moondance", 20);
    set("max_gin", 200);
    set("max_atman", 200);
    
    set("no_get", "精奴被镣铐牢牢的固定着，根本解不下来。\n");
    set_temp("no_move", 1);

    setup();
}

int accept_fight(object me)
{
    command("fear " + me->query("id"));
    command("say " + RANK_D->query_respect(me)
        + "饶命，小人哪能跟您动手？\n");
    return 0;
}

mixed set_temp(string prop, mixed data)
{
    if (prop == "no_move") return ::set_temp("no_move", 1);
    else return ::set_temp(prop, data);
}

int delete_temp(string prop)
{
    if (prop == "no_move") return ::set_temp("no_move", 1);
    else return ::delete_temp(prop);
}
