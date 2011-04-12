// cracked by vikee 2/09/2002   vikee@263.net
#include <ansi.h>

#include <dbase.h>
#include <armor.h>

inherit NECK;

void create()
{
    set_name("仙花", ({ "flower"}));
    set_weight(100);
    set("unit", "朵");
    set("armor_prop/armor", 1);
    set("armor_prop/personality", 2);
    setup();
}

void init()
{
    add_action("do_eat","eat");
}

int do_eat(string arg)
{
    object me = this_player();
    int qn = 0;
    int score = query("score");
    if (!arg || !id(arg)) return 0;
    message_vision(HIC"$N吃下一朵"+query("name")+HIC"，只觉得香气扑鼻，齿颊芬芳。\n"NOR, me);
    if (query("target")==me && score>0) {
        me->add("combat_exp", score);
        qn = score*(20+random(10))/100;
        if (me->query("potential")-me->query("learned_points") < 1000)
            me->add("potential", qn);
        tell_object(me, HIC"你得到了"+COMBAT_D->chinese_daoxing(score)+"道行，"+qn+"点潜能。\n"NOR);
        MONITOR_D->report_system_object_msg(me, " got "+score+" exp "+qn+" pots from baihua-gu.\n" );
        log_file("baihuagu", me->query("id")+" got "+score+" exp "+qn+" pots on "+ctime(time())+".\n");
    }
    destruct(this_object());
    return 1;
}