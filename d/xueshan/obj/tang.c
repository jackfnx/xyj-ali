inherit ITEM;

#include <ansi.h>

int do_he(string);

void create() 
{
    set_name(YEL "五仙汤" NOR, ({"tang"}));
    set_weight(50);
    set("unit","碗");
    setup();
}

void setup()
{
    if (!query("prices")) set_name("刷锅水", ({"tang"}));
    set("long", "一碗花花绿绿的"+name()+"，尝尝(he)味道？\n");
}

void init()
{
    add_action("do_he", "he");
}

int do_he(string arg)
{
    object who = this_player();

    if (!id(arg)) return notify_fail("你想喝啥？\n");
    message_vision("$N端起"+name()+"咕嘟咕嘟的喝了下去。\n", who);
    if (query("prices") <= 0)  message_vision("但什么滋味也没尝出来。\n", who);
    else if ((int)who->query_skill("iceblood-force", 1) < 10
        ||  (int)who->query_skill("iceblood-force", 1) > 199 ) {
            message_vision("$N只感到一阵恶心，天悬地转。\n", who);
            who->unconcious();
    } else {
        message_vision("$N苦得涕泪横流，强忍着没吐出来。\n", who);
        who->improve_skill("iceblood-force", query("prices"));
        tell_object(who, "你只感到腹内如有数十把小刀在乱攒乱刺，你使尽了力气，"
            +"才将毒汤的药力完全化解。\n");
        tell_object(who, YEL "你的冰谷凝血功增加了"+ chinese_number(query("prices"))+"点！\n" NOR);
    } 
    destruct(this_object());
    return 1;
}

