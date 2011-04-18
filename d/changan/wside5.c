// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//cglaem...12/12/96.

inherit ROOM;

void create ()
{
  set ("short", "泾水之滨");
  set ("long", @LONG

这里已经距离长安城已经有些远了，路上的游人越来越稀少
了。但绿柳轻垂，微风拂面，这里的景色依旧很美丽，而且
其中还多了一份宁静、幽怨。绿柳掩映间，隐约可见一条小
路通向远方。
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "west" : "/d/gao/lu1",
  "east" : __DIR__"wside4",
]));
  set("outdoors", 1);

  setup();
}
