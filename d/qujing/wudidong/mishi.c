// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// /d/qujing/wudidong/mishi.c
// created by mes, updated 6-20-97 pickle

#include <room.h>
inherit ROOM;

void reset();

void create()
{
  set ("short", "暗室");
  set ("long", @LONG

这儿是无底洞的一个支洞，也是玉鼠精的练功房。除了玉鼠之外，
很少有其他人进出。房间布置得十分简单，但是屋中央摆着一张
十分醒目的玉台(tai)。
LONG);
  set("item_desc",([
         "tai" : "
这是一张用万年南极冰玉所雕成的玉台，玲珑透剔。想来必是玉鼠练
功之用。台上刻着几个殷红的大字：

\t\t\t天魔座\n\n
\t\t  入我门来，万劫不复
\n",
         ]));
  set("exits", ([ /* sizeof() == 2 */
      "out" : __DIR__"gongshi",
      ]));
  set("no_clean_up", 1);
  set("if_bed", 1);
  set("sleep_room", 1);
  set("outdoors", 0);
  set("lianxi_yaofa", 1);
  setup();
}       
void init()
{
  add_action("do_climb", "climb");
  add_action("do_climb", "pa");
}
int do_climb(string arg)
{
  object me=this_player();
  if ( !arg || (arg !="tai" && arg != "off" && arg != "down" && arg!="xia") )
    return notify_fail("你要爬什么？\n");
  if (arg == "tai")
    {
      if ((int)me->query_temp("mark/无底洞天魔台climbed"))
   return notify_fail("你已经坐在台上了，还想爬到哪儿去？\n");
      message_vision("$N纵身一跃，爬上天魔台去了。\n", me);
      me->set_temp("mark/无底洞天魔台climbed", 1);
      return 1;
    }
  if(!(int)me->query_temp("mark/无底洞天魔台climbed"))
    return notify_fail("你不在台上。\n");
  message_vision("$N从台上跳了下来。\n", me);
  me->delete_temp("mark/无底洞天魔台climbed");
  return 1;
}

int valid_leave(object me, string dir)
{
  if(dir=="out" && (int)me->query_temp("mark/无底洞天魔台climbed")==1)
    return notify_fail("先从台上跳下去吧！\n");
  return ::valid_leave(me, dir);
}

void practice_yaofa(object me)
{
    me->delete_temp("spellslevel");
    me->delete_temp("d_mana");
    me->delete_temp("apply/name");
    me->delete_temp("apply/id");
    me->delete_temp("apply/short");
    me->delete_temp("apply/long"); 
    if (random(100+me->query_kar()*10)<10) {
        //mon 1/23/98. old formula was <1, I changed to <10.
        //don't know exactly, but <1 seems impossible.
        message_vision("$N昏昏地睡了过去。\n", me);
        me->delete_temp("mark/无底洞天魔台climbed");
        me->move("/d/ourhome/honglou/main");
        if (random(40-me->query_kar())<10)
            me->set("dream_place", "/d/qujing/wudidong/mishi");
    }
}