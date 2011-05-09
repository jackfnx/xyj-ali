//xiaozuanfeng.c

inherit NPC;
inherit F_VENDOR;

void create()
{
    set_name("小钻风", ({"xiao yao", "xiaoyao", "yao"}));
    set("gender", "男性" );
    set("age", 16);
    set("long", "小钻风原是狮驼山的巡山小妖。\n"
        "跟着青狮老魔到大雪山后改当厨师了。\n"
        "不过他好个吃喝，在这里近水楼台先得月，倒也逍遥快活。\n");
    set("class", "yaomo");
    set("combat_exp", 5000);
    set("attitude", "peaceful");
    set("title", "小妖");
    set_skill("unarmed", 20);
    set_skill("dodge", 20);
    set_skill("parry", 10);

    set("per", 11);
    set("max_kee", 150);

    set("vendor_goods", ([
        "jiudou": "/d/xueshan/obj/jiudou",
        "peijian": "/d/obj/weapon/sword/peijian",
        "yinzhen": "/d/obj/weapon/throwing/yinzhen",
        "kongqueling": "/d/obj/weapon/throwing/kongque-ling",
    ]));

    setup();
    carry_object("/d/obj/armor/shoupi")->wear();
}

void init()
{
    object ob=this_player();
    object me=this_object();

    ::init();
    add_action("do_vendor_list", "list");
}

