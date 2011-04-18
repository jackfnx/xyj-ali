// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /changan/wroad3.c
//cglaem...12/12/96.

inherit ROOM;

void create ()
{
  set ("short", "青石路");
  set ("long", @LONG

往西而去路逐渐难行，青石路已开始变成土路了。前方好象
就是传说中的灌江口，你不由得加快了步伐。
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "southwest" : "d/meishan/guanjiang1",
  "northeast" : __DIR__"wroad2",
]));
  set("outdoors", 1);

  setup();
}






