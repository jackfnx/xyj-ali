// ALi by NewX

inherit ROOM;

void create ()
{
    set ("short", "练功房");
    set ("long", @LONG

这里竟然是轩辕派的练功房，对于轩辕派最重要的就是床上功夫。因此
其中弟子每天都会苦练床上功夫。因为优秀的男性练功伙伴很难寻觅，
所以大多数时候她们都只能用手淫的方式来修炼。放眼望去，一望无际
的雪白肉体疯狂的进行着手淫，快感的呻吟、高潮的浪叫此起彼伏，实
在是蔚为壮观。
LONG);

  set("objects", ([ /* sizeof() == 3 */
        __DIR__"npc/zmgirl.c" : 3,
]));

    set("exits", ([ /* sizeof() == 1 */
        "west" : __DIR__"shidong3.c",
]));

    setup();
}

/*
void init()
{
        add_action("do_serve", "serve");
   add_action("do_stand", "stand");
   add_action("do_sit", "sit");
}

int valid_leave()
{
        if((present("snowglass", this_player())))
            return notify_fail("此杯乃嫦娥心爱之物，带走不妥吧。\n");
    return ::valid_leave();
}

int do_sit(string arg)
{     
      object me;

      me=this_player();

        if ( !arg || ((arg != "seat")&&(arg != "deng")&&(arg != "table") ))
                return notify_fail("你要坐在什么上面？\n");

        if (this_player()->query_temp("marks/sit"))
                return notify_fail("你已经坐下了。\n");
      
      if ( arg != "seat"&&arg != "deng")
              return notify_fail("坐桌子上？太不雅观了吧。\n");
        
        this_player()->set_temp("marks/sit", 1);
        message_vision("$N轻轻巧巧地坐上了小木凳。\n",me);
      return 1;
}
int do_stand(string arg)
{
      object me;

      me=this_player();

      if (!this_player()->query_temp("marks/sit"))
          return notify_fail("你本来就站着。\n");

      this_player()->set_temp("marks/sit", 0);
      message_vision("$N伸了个懒腰，站了起来。\n", me);
      return 1;
}
int do_serve(string arg)
{
        object m,mm;
   if ((int)this_player()->query_temp("marks/sit") == 0)
     return notify_fail("如此良辰美景，何不坐下来小酌？\n");
        if((int)this_player()->query("food") >=
     (int)this_player()->max_food_capacity()*90/100)
        return notify_fail("这儿风景这么好，别光想着吃：）\n");
            
        if(present("xue li", this_player()) || 
     present("guihuageng", this_player()) ||
     present("xue li", environment(this_player()))
   )
        return notify_fail("不是还有吃的吗？\n");

        m=new(__DIR__"obj/xueli.c");
   mm=new(__DIR__"obj/guihuageng.c");
   
   message_vision("$N嘴里嘟囔了两句，木桌上立刻有摆满了果品点心．\n", this_player());

        m->move(environment(this_player()));
        mm->move(environment(this_player()));

return 1;
}
*/

