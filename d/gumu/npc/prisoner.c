// ALi by NewX

#include <ansi.h>

inherit NPC;

string *prisoner_descs = ({
    "一个健美的女子，面容有些眼熟，似乎是某一个江湖上有点名气的女侠。\n",
    "一个娇滴滴的大姑娘，一看就是个大小姐。\n",
    "一个年轻的女孩，显然是月宫弟子，不过此时武功法术全都被封，连人都被绑在调教架子上。\n",
    "一个犯了错的古墓弟子，绑在调教架子上，瑟瑟发抖。\n",
});

string *status_descs = ({
    "此时浑身衣服被扒了个精光，身上伤痕累累，狼狈不堪。",
    "此时眼中流落出恐惧气息，就连胯下硕大的阳根也无精打采的。",
    "此时受到周围环境的影响，居然也不可抑止的勃起着。",
});

void create()
{
    set_name("囚犯", ({"fan", "girl"}));
    set("title", CYN "牢牢锁住的" NOR);
    set("long", prisoner_descs[random(sizeof(prisoner_descs))]);
    set("looking", status_descs[random(sizeof(status_descs))]);

    set("gender", "女性");
    set("age", 15+random(20));
    set("per", 20+random(15));
    set("combat_exp", 10000);
    set_skill("dodge", 10);
    set_skill("moondance", 20);
    set("max_gin", 200);
    set("max_atman", 200);
    
    set("no_get", "囚犯被镣铐牢牢的固定着，根本解不下来。\n");
    set_temp("no_move", 1);

    setup();
}

int accept_fight(object me)
{
    command("fear " + me->query("id"));
    command("say " + RANK_D->query_respect(me)
        + "饶命，奴家哪能跟您动手？\n");
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
