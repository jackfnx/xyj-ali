#include <ansi.h>

inherit ROOM;

string look_flag();

void create()
{
    set("short", "花果山教军场");
    set("long", @LONG

一片开阔的草地，被猴子们当作他们的教军场，只见其中一个严肃的
通背猿指挥着一列列，一排排走过来的猴子兵。草地的北侧竖着一根
十丈多高的旗杆，上面挂着一面大旗(flag)，在风中飒飒飘舞。
LONG
    );

    set("exits", ([
        "east"   : __DIR__"shanya",
    ]));

    set("item_desc",([
        "flag": (: look_flag :)
    ]));

    set("objects", ([
        __DIR__"npc/beng-jiangjun" : 1,
    ]));

    set("no_clean_up", 1);
    set("outdoors", __DIR__);
    setup();
}

void init()
{
    add_action("do_start", ({"raise","gua","sheng","hang"}));
}

string look_flag()
{
    string str = "一面三尺见方的大旌旗，迎风飘展。\n";
    if (query("host")) 
        str += ("旗上绣着"+HIY+" 齐天大圣 "+query("host")->query("name")+NOR+" 几个大字。\n\n");
    else
        str += ("风太大，看不清楚旗上面写着什么。\n\n");
    return str;
}

int do_start(string arg)
{
    object me = this_player();
    object host = query("host");
    object lijing;

    if (!arg || arg!="flag") return notify_fail("你要做什么？\n");
    if (host)
        return notify_fail(host->query("name")+"已在此占山为王了。\n");   
    if (me->query("combat_exp") < 100000)
        return notify_fail("旗杆太高了，你功夫太差，挂不上去。\n");
    if (me->query("dntg/lijing") == "done")
        return notify_fail("你上次已经过足齐天大圣瘾了，这次留给别人玩吧。\n");

    set("host", me);
    message_vision(HIG"$N将“齐天大圣”的大旗挂上旗杆。\n"NOR, me);
    message_vision(HIG"$N高声宣布：“从今日起，"
        + RANK_D->query_self_rude(me) + "就是齐天大圣，与玉帝老儿平起平坐！”\n"NOR, me);

    lijing = new("/d/dntg/lijing/lijing");
    lijing->move(this_object());
    lijing->set("target", me);
    lijing->start();

    return 1;
}
