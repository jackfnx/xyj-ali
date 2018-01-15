// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit NPC;
inherit F_VENDOR;
void create()
{
        set_name("贾二", ({"jia er", "jia"}));
        set("age", 32);
        set("gender", "男性");
        set("long","包子铺的老板，笑眯眯的看着你。\n");
        set("attitude", "friendly");

        set("combat_exp", 10000);
        set("shen_type", 1);
   set("force", 200);
   set("force_factor", 5);
        set_skill("unarmed", 20);
        set_skill("dodge", 60);
        set_skill("parry", 20);
        set("vendor_goods", ([
                "roubao": "/d/obj/food/bao1",
                "haibao": "/d/obj/food/bao2",                
                "subao": "/d/obj/food/bao3",                
        ]) );

   setup();
        add_money("silver", 3);
        carry_object("/d/obj/cloth/linen")->wear();
}
int accept_fight(object me)
{
        command("say 大家和气生财，和气生财！\n");
        return 0;
}


void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(1) ) {
                case 0:
                        say( name()+"笑咪咪地说道：这位" +
RANK_D->query_respect(ob)
                                + "，进来吃几个包子吧。\n");
                        break;
        }
}

