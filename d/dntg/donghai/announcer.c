// sgzl
#include <ansi.h>
#define NAME "敖广"
#define ID "ao guang"

inherit NPC;

void create()
{
    set_name(NAME, ({ ID }));
    set("gender", "男性");
    set("age", 53);
    set("long", "一条老泥鳅。\n");
    
    setup();
}

void announce_success(object who)
{
    int dx = random(500) + 3000;
    object hb = who->query_temp("dntg_helper");

    who->add("dntg/number", 1);
    who->set("dntg/donghai", "done");
    who->add("combat_exp", dx);
    command("chat "+who->query("name")+"你竟敢拿走我龙宫的定海神针铁，看我不去玉帝面前告你！");
    tell_object(who,"你赢得了"+ COMBAT_D->chinese_daoxing(dx) +"的道行！\n");
    who->save();
    if (hb) hb->report_progress(10);
}

