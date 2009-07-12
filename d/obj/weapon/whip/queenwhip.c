// sixue
 
// queenwhip.c

#include <weapon.h>

inherit WHIP;

void create()
{
    set_name("女王之鞭", ({"queenwhip", "whip"}));
    set_weight(1000);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long","一条漆黑的皮鞭，质地很柔软，抽打在身上并不怎么痛，反而有种酥麻的感觉\n");
        set("unit", "条");
        set("value", 500);
        set("rigidity", 100);
        set("wave", 100);
    }
    init_whip(1);
    setup();
}

