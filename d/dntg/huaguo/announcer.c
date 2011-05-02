
#include <ansi.h>

#define NAME "马元帅"
#define ID "ma yuanshuai"

inherit NPC;

void create()
{
    set_name(NAME, ({ ID }));
    set("gender", "男性");
    set("age", 23);
    set("long", "一只大马猴。\n");
    set("combat_exp", 1000000);

    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("dragonstep", 120);
    map_skill("dodge", "dragonstep");
    set("force", 900);
    set("max_force", 900);
    set("force_factor", 10);

    setup();
}

void announce_success(object who)
{
    int dx = 3000 + random(500);
    object panzi;
    object hb = who->query_temp("dntg_helper");

    who->add("dntg/number",1);
    who->set("dntg/huaguo", "done");
    who->add("combat_exp", dx);
    command("chat "+who->query("name")+"斩了霸占我们水帘洞的魔头，顺利闯过大闹天宫第一关！");
    command("chat 从此七十二洞精灵皆应尊"+who->query("name")+"为王，随时听候调遣！");
    tell_object(who, "你赢得了"+ COMBAT_D->chinese_daoxing(dx) +"的道行！\n");

    panzi = new(__DIR__"shipan");
    panzi->move(who);
    message_vision(HIY NAME+"点头哈腰的对$N说到：这是我们众兄弟的一点儿小意思，不成敬意。\n" NOR,who);
    tell_object(who, "马元帅给你一个石头盘子。\n");
    who->save();
    if (hb) hb->report_progress(10);
}
