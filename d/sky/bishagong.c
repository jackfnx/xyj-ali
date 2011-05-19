//created by vikee
//2000.10

inherit ROOM;

void create()
{
    set("short", "毗沙宫");
    set("long", @LONG

绛纱衣星辰灿烂，鞭蓉冠金譬辉煌。玉簪珠履。紫绶金章。
金钟撞动，三曹神表进丹樨；天鼓鸣时，万圣朝王参玉帝.
LONG);

    set("exits", ([ /* sizeof() == 1 */
        "south"  :  __DIR__"tongmingdian",
        "north"  :  __DIR__"tonglugong",
    ]));
    set("objects",([
        //__DIR__"npc/xszj"  :  1,
    ]));
    set("no_quit",1);
    setup();
}

void init()
{
    object wang,zj,who = this_player(),env = this_object();

    if(!userp(who) || who->query("huoyan/bgl")!="done"||
      who->query("dntg/huoyan")=="done") return;
    if(!zj=present("xusheng zhenjun",env) ){
      zj = new(__DIR__"npc/xsjz");
      zj->move(env);
   }
    zj->command_function("chat " + who->name() + "这" + RANK_D->query_rude(who) +
      "打到毗沙宫了，四大天王快来护驾！\n");
    message_vision("四大天王蜂拥而至，将$N包围在当中。\n",who);
    if(!present("moli hong",env)){
      wang = new(__DIR__"npc/tianwang2");
      wang ->move(env);
   }
    if(!present("moli qing",env)){
      wang = new(__DIR__"npc/tianwang3");
      wang ->move(env);
   }
    if(!present("moli shou",env)){
      wang = new(__DIR__"npc/tianwang4");
      wang ->move(env);
   }
    if(!present("moli hai",env)){
      wang = new(__DIR__"npc/tianwang1");
      wang ->move(env);
   }
}

int valid_leave(object ob, string dir)
{
    object guan;
    if( !guan = present("xusheng zhenjun",this_object()));
      guan = present("moli hong",this_object());
    if( !guan ) guan = present("moli qing",this_object());
    if( !guan ) guan = present("moli shou",this_object());
    if( !guan ) guan = present("moli hai",this_object());
    if(guan) {
      message_vision("$n把$N一挡：想走？没那么容易！\n",ob,guan);
      return notify_fail("看样子是走不成了。\n");
   }
    return ::valid_leave(ob,dir);
}

