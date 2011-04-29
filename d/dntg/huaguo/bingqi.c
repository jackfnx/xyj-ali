// bingqi.c

inherit ITEM;

void create()
{
    set_name("兵器",({"bing qi"}));
    set_weight(20000);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("long","一大捆兵器，刀、枪、剑、戟、斧、钺、钩、叉\n"
"什么都有，上面都刻有几个大字：＂傲来国制＂。\n");
        set("unit","捆");
    }
}

void init()
{
    object ob = this_object();
    object where = environment();

    if (userp(where)) {
        if (!ob->query("owner"))
            ob->set("owner", where);
        else if (ob->query("owner") != where)
            call_out("destruct_me", 5, ob);
    }
}

void destruct_me(object ob)
{
    if (ob) {
        tell_object(environment(ob), "兵器唏哩哇啦撒了一地。\n");
        destruct(ob);
    }
}
