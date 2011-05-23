//sgzl

#include <ansi.h>

inherit F_UNIQUE;
inherit ITEM;

void create()
{
    set_name("定海神针铁", ({ "shen tie" ,"tie"}));
    set_weight(30000);
    set("long", @LONG

传说这神铁乃是大禹治水之时，定江海浅深的一个定子。
上前仔细观瞧， 原来两头是两个金箍，中间乃一段乌铁；
紧挨箍有镌成的一行字，唤做『如意金箍棒』，重一万三
千五百斤。
LONG );

    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "个");
        set("material", "crimsonsteel");
        set("value", 20000000);
        set("no_get", "这么粗的神铁哪里拿得起来？\n");
        set("no_sell", 1);
    }
    setup();
}

void init()
{
    add_action("do_xiao", "xiao");
}

int do_xiao()
{
    object me = this_object();
    object who = this_player();
    object helper = who->query_temp("dntg_helper");

    if (who->query("dntg/donghai") != "hua gan ji" || !helper) {
        message_vision("$N大喝一声＂小，小，小！但神铁一点反应也没有发生。\n", who);
        return 1;
    }

    if (who->query("mana") < 500)
        message_vision("$N大喝一声＂小，小，小！但什么也没有发生。\n", who);
    else {
        who->add("mana", -500);
        if (random(5) < 4)
            message_vision("$N大喝一声＂小，小，小！＂\n只见神铁果然变短变细了些。\n", who);
        else {
            message_vision("$N大喝一声＂小，小，小！＂\n只见神铁化作了一团虚影，融入了$N身上的" +helper->name()+ "。\n", who);
            call_out("finish_summary", 1, who);
            load_object("/obj/empty");
            move("/obj/empty");
        }
    }
    return 1;
}

void finish_summary(object who)
{
    object helper;
    
    if (!who || !(helper = who->query_temp("dntg_helper"))) return;

    who->start_busy(50);
    helper->speak(({
            CYN "说道：嘿嘿嘿嘿，大概你也已经猜到了。" NOR,
            CYN "说道：这里根本就没有金箍棒！" NOR,
            CYN "说道：其实，自从当年大圣爷爷把我从这里抢走，那敖广便疯了。" NOR,
            CYN "说道：整天以为金箍棒还在这，整天担惊受怕有人会来抢。" NOR,
            CYN "说道：时间长了，这里竟然被他凭空观想出了一条定海神针的虚影。" NOR,
            CYN "说道：这玩意戳在这里，对本老人家成道却是大大不利，所以我才让你帮我演这么一出戏。" NOR,
            CYN "说道：你小子帮了我大忙，本老人家自然也不会亏待你。" NOR,
            CYN "说道：这样吧，我便传你一套如意变化之道，只要你有自制法宝兵器，我可以让它拥有第二种形态。" NOR,
            CYN "说道：虽然不如金箍棒变化多端，但也别有一番妙用。" NOR,
            CYN "说道：就算你暂时没有自制法宝兵器也没关系，本大爷最守信用，将来等你有了再来找我，本大爷随时恭候。" NOR,
            CYN "说道：好了好了，废话说完了，现在该离开了。" NOR,
            (: call_other, this_object(), "finish_announce", who :),
    }));
}

void finish_announce(object ob)
{
    object wang;
    ob->start_busy(-1);
    ob->continue_action();
    ob->command_function("up");
    wang = new(__DIR__"announcer");
    wang->announce_success(ob);
    destruct(this_object());
}
