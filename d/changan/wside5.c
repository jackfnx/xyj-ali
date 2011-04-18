// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//cglaem...12/12/96.

inherit ROOM;

void create ()
{
  set ("short", "泾水之滨");
  set ("long", @LONG

这里已经接近泾水的源头，人迹越发的稀少。四周静谧幽远，你的
心情也不禁放松下来。绿柳掩映中，隐约可见一条小路通向远方。
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "west" : "/d/gao/lu1",
  "east" : __DIR__"wside4",
]));
  set("outdoors", 1);

  setup();
}
