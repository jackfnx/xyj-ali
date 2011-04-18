// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit NPC;
inherit F_VENDOR;

int base_price=100000;

int ask_money();
void create()
{
        set_name("老害虫", ({"xifuhui boss","boss" }));
   set("title", "喜福会老板娘");
   
        set("age", 32);
        set("gender", "女性");
        set("attitude", "friendly");

        set("combat_exp", 50000);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
   set("per", 20);

set("inquiry", ([
"name": "在下便是这里的老板。",
"here": "这里是喜福会，本来是摆喜宴的地方。可惜现在世风日下，人心不古，早就没人结婚了。",
"喜宴" : "去！一边去！现在早就没人结婚了！哪还有什么喜宴？",
"酒席" : "就算不是喜宴，只要你愿意花钱，一样可以为你操办一场宴会。",
"宴会" : "就算不是喜宴，只要你愿意花钱，一样可以为你操办一场宴会。",
"party" : "就算不是喜宴，只要你愿意花钱，一样可以为你操办一场宴会。",
"money": (: ask_money :),
]) );
        setup();
        carry_object("/d/obj/cloth/pink_cloth")->wear();
}

void init()
{
    ::init();
   add_action("do_serve", "serve");
   add_action("do_finish", "finish");
   add_action("do_start", "start");
     add_action("do_fight", "fight");
     add_action("do_kill", "kill");
     add_action("do_steal", "steal");
     add_action("do_cast", "cast");
     add_action("do_exert", "exert");
     add_action("do_perform", "perform");
     add_action("do_bian", "bian");
   add_action("do_fight", "fight");

}

int accept_object(object who, object ob)
{
   object m;
   int value;

   value=ob->value();

   if( !value )
     return notify_fail(name()+"奇怪的看着你说：给我这干什么？\n");

   call_out("destroy", 1, ob);
   if( value >= base_price ) {
	who->set_temp("host_of_party", 1);
	call_out("count_money", 2, who);
	call_out("start_party", 5, who);
   }
   return 1;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}
void count_money(object who)
{
   message_vision("\n$N把$n给的钱仔细的清点了一遍。\n\n", this_object(), who);
   message_vision("$N痛快的说：开席！\n", this_object() );
}

void start_party(object who)
{
   object me=this_object();
   command("chat* "+name()+
          "：各位老爷太太少爷小姐，今日" + who->query("name") +  
"在喜福会大开酒席，欢迎各位前来捧场！");
   command("say 您要开始(start)，我便开席。您要上菜(serve)，我就上菜，等您吃饱了，玩腻了，咱就结束(finish)。");
   me->set_temp("ready_to_party", 1);
}
int do_start()
{   
   object who = this_player();
        object me = this_object();
   int i;
   object *list;
   object girla,girlb,girlc,girld,cup;
   if( !who->query_temp("host_of_party") )
     return notify_fail(name()+"对你说：你又不是主人？\n");
   if( !me->query_temp("ready_to_party") )
     return notify_fail(name()+"对你说：开始什么呀，现在又没人办宴会！\n");
   if( me->query_temp("party_start_already") )
     return notify_fail(name()+"生气的对你说：这不是已经开始了嘛！\n");

   message_vision("$N大声对$n说：老板，开席！\n\n", who, me);
   message_vision("$N大声喊着：开～～席～～喽～～\n\n", me);
   me->set_temp("party_start_already", 1);
   me->delete_temp("ready_to_party");

   list = all_inventory(environment(me));
   i = sizeof(list);
   while (i--)
   {
       object ob= list[i];
      if( cup=new("/d/obj/food/dishes/cup"))
       cup->move(ob);
   }
   seteuid(getuid());
   if(girla=new("/d/city/npc/girla"))   
    girla->move(environment(me));

        seteuid(getuid());
        if(girlb=new("/d/city/npc/girlb"))
        girlb->move(environment(me));

        seteuid(getuid());
        if(girlc=new("/d/city/npc/girlc"))
        girlc->move(environment(me));

        seteuid(getuid());
        if(girld=new("/d/city/npc/girld"))
        girld->move(environment(me));

   tell_room(environment(who), "内堂走出几个漂亮的小姑娘。\n");
   tell_room(environment(who), "你得到了一个白玉酒盏。\n");
   call_out("finish_party", 500, who);
   return 1;
}
int do_serve()
{
   object me=this_object();
   object who=this_player();
   object food;
   if( !who->query_temp("host_of_party") )
     return notify_fail(name()+"对你嚷道：主人还没说话，你嚷个什么劲！\n");
   if( !me->query_temp("party_start_already") )
     return notify_fail(name()+"对你说：你还没宣布开始(start)，怎么上菜呢？\n");
   if ( (present("food 2", environment(me))) )
     return notify_fail(name()+"对你说：慢慢吃，吃完自然会给你上菜。\n");

   message_vision("$N大声嚷嚷着：上菜，上菜！\n", who);

   tell_room(environment(me), "从内堂跑出四五个小伙计，手脚麻利的将桌上的剩菜饭端了下去。\n");
   tell_room(environment(me), "小伙计又从内堂出来，端上了一桌新的酒席。\n");
        if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
   if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
   if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
   if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
   return 1;
}
int do_finish()
{
   object me=this_object();
   object who=this_player();

   if( !who->query_temp("host_of_party") )
     return notify_fail(name()+"瞪了你一眼：别乱说话！\n");

   if( !me->query_temp("party_start_already") )
     return notify_fail(name()+"瞪了你一眼：不是已经结束了吗！\n");
   message_vision("$N对$n说道：吃饱喝足，多谢老板招待！\n", who, me);
   remove_call_out("finish_party");
   call_out("finish_party", 3, who);
   return 1;
}
void finish_party(object who)
{
   object me=this_object();
        int i;
        object *list;

   message_vision("$N大声说道：宴席就此结束，多谢大家光临！\n", me);

   me->delete_temp("party_start_already");
   who->delete_temp("host_of_party");
   list=all_inventory(environment(me));
   i=sizeof(list);
   while (i--)
   {
     if(list[i]->query("id") != "ban niang")
        continue;
     else
        destruct (list[i]);
   }
}