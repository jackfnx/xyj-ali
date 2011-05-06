// sgzl

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

int do_install(string);
int do_uninstall(string);

void create()
{
    set_name("凤凰琴", ({"fenghuang qin","qin","sword"}));
    set_weight(4000);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long", "一把淡蓝色的细剑，剑身几乎透明，剑锋处闪着点点寒光。\n"
"剑柄处似乎有个机关能装 (install) 些暗器进去。\n");
        set("unit", "把");
        set("value", 3000);
        set("material", "steel");
        set("wield_msg", "$N冷笑一声，从背后拔出了凤凰琴。\n");
        set("unwield_msg", "$N将手中的凤凰琴插回鞘中，嘴角多了一丝笑意。\n");

        set("anqi/allow", 1);
        set("anqi/max", 50);
        set("anqi/now", 0);
    }
    init_sword(60);
    setup();
}

void init()
{
    add_action("do_install", "install");
    add_action("do_uninstall", "uninstall");
}


int do_install(string arg)
{
    object me = this_object();
    object who = this_player();
    object aq;
    int remain;

    if (!arg) return notify_fail("你想装什么？\n");

    aq = present(arg, who);
    if (!present(arg, who))
        return notify_fail("你身上没有这东西。\n");
    else if (aq == me)
        return notify_fail("自己装自己？\n");
    else if (aq->query("name") != "银针" && aq->query("name") != "毒针" && aq->query("name") != "孔雀翎") 
        return notify_fail("这玩艺太大了，装不进去。\n");
    else if (query("anqi/now") == query("anqi/max"))
        return notify_fail(name()+"已经装满暗器了。\n");
    else if (query("anqi/now") > 0 && query("anqi/type") != aq->query("name"))
        return notify_fail(name()+"不能装不同的暗器。\n");
    else {
        message_vision("$N打开"+name()+"的机关，将一"+aq->query("unit")+aq->query("name")+"装了进去。\n", who);
        who->start_busy(3);
        if (query("anqi/now") == 0) {
            me->set("anqi/type", aq->query("name"));
            me->set("anqi/base_unit", aq->query("base_unit"));
        }
        if (query("anqi/now") + aq->query_amount() > query("anqi/max")) {
            remain = query("anqi/now") + aq->query_amount() - query("anqi/max");
            me->set("anqi/now", query("anqi/max"));
            aq->set_amount(remain);
        } else {
            me->set("anqi/now",query("anqi/now") + aq->query_amount());
            destruct(aq);
        }
        return 1;
    }
}

int do_uninstall(string arg)
{
    object ob;
    object me = this_object();
    object who = this_player();
    
    if (!me->id(arg)) return notify_fail("你想拆什么？\n");
    else if (query("anqi/now") == 0) return notify_fail(name()+"里面什么也没有。\n");
    else {
        if (query("anqi/type") == "银针") ob = new("/d/obj/weapon/throwing/yinzhen");
        else if (query("anqi/type") == "孔雀翎") ob = new("/d/obj/weapon/throwing/kongque-ling");
        else ob = new("/d/obj/weapon/throwing/yinzhen");
        ob->set_amount(query("anqi/now"));
        ob->move(who);
        me->set("anqi/now", 0);
        message_vision("$N从"+name()+"里面拆出一"+ob->query("unit")+ob->query("name")+"。\n", who);
        who->add_busy(3);
        return 1;
    }
}

string extra_long()
{
    if (!query("anqi/now")) return "";
    else return sprintf("里面已经装了%s%s%s，想拆掉用uninstall。\n",
                    chinese_number(query("anqi/now")), query("anqi/base_unit"), query("anqi/type"));
}
