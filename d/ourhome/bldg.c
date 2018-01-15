// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 


// Room: /d/city/bldg.c

#include <ansi.h>
inherit ROOM;

/*void init(); */
int do_go(string temp2);
int do_sit(string temp3);

void create()
{

      set("short", "住宅区");
   set("long", @LONG
终於见到人烟了。看起来这是一片没有俊工的住宅区。
四周杂草丛生。除了几条脏不啦唧的小狗在这里逛来逛去
外，还有个脸上盖着顶破草帽的男人，正靠在一辆老爷
车(car)上打瞌睡。 
LONG
   );

   set("exits", ([
     "north" : __DIR__"kedian3",
   ]));
   
    set("item_desc", ([
          "car":"一辆破破乱乱的老爷车，只有两个座位。 \n",
   ]));
                                   

   set("objects",([
     __DIR__"npc/driver" : 1,
     ]));
   
   set("no_fight", 1);
   
   setup();
}

void init()
{
   add_action("do_go", "drive");
   add_action("do_sit", "sit");
}


int do_go(string arg)
{

   object me;
   object driver; 

   me=this_player();
   if( !objectp(driver = present("driver", environment(me))) )
           {     return notify_fail("司机没在，你得等会儿。