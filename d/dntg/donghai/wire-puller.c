// wire-puller.c

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("幕后操纵者", ({"wire-puller"}));
    set("env/invisibility", 1);
    set_weight(100);
    set("no_get", 1);
    seteuid(getuid());
    setup();
}

string short()
{
    object owner = query("owner");
    if (!owner) return "幕后操纵者";
    else return sprintf("幕后操纵者(owner: %s)", geteuid(owner));
}

void init()
{
    if (query("owner") == this_player()) {
        add_action("do_ask", "ask");
    }
}

void start_testing()
{
    object owner = query("owner");
    object aoguang = present("ao guang", environment());

    if (!owner) return;
    if (!aoguang || !aoguang->is_character()) return;
    set("aoguang", aoguang);
}
