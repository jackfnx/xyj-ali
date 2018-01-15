
inherit ITEM;

void create ()
{
    set_name("〖ORZ-ZTO〗", ({"orz", "zto"}));
    set_weight(100);
    seteuid(getuid());
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "套");
        set("long", "orz zto");
        set("material", "paper");
        set("value", 0);
        set("no_get", 1);
        set("no_give", 1);
        set("no_sell", 1);
        set("no_drop", 0);
        set("no_put", 1);
    }

    setup();
}

void init()
{
    add_action("do_orz", "orz");
    add_action("do_zto", "zto");
}

int do_orz()
{
    object me;
    mapping f, w, ar;
    mapping *ff;
    int i;
    
    me = find_player("sixue");
    f = me->query("fabao");
    
    if (!mapp(f)) {
        printf("不是map.\n");
        return 1;
    }
    
    ff = ({});
    if (!undefinedp(f["weapon"])) {
        w = ([]);
        w["type"] = "weapon";
        w["series_no"] = atoi(f["weapon"]);
        ff += ({ w });
    }
    for (i = 0; i < 10; i++) {
        if (!undefinedp(f["armor"+i])) {
            ar = ([]);
            ar["type"] = "armor";
            ar["series_no"] = atoi(f["armor"+i]);
            ff += ({ ar });
        }
    }
    printf("fabao: %O\n", ff);
    me->set("fabao", ff);
    
    return 1;
}

int do_zto()
{
    for (int i = 0; i < 6; i++)
    {
        object ob = new("/obj/fabao");
        ob->set("owner_id", "sixue");
        ob->set("series_no", i + 1);
        ob->restore();
        printf("%d: %O\n", i, ob->query_entire_dbase());
    }
    return 1;
}