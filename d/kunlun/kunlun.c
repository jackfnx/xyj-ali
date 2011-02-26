// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /moon/kunlun.c
//cglaem...12/13/96.

inherit ROOM;

void create ()
{
  set ("short", "昆仑山区");
  set ("long", @LONG

苍茫昆仑，绵延千里。放眼望去，正所谓千里冰封，万里雪飘。西面奇峰
入云，乃是昆仑主峰玉女峰。据说西王母就隐居在玉女峰绝顶处。东面则
是一条蜿蜒的小路。
LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 3 */
  "north" : "/d/xueshan/xueshan1",
  "southeast" : __DIR__"xiaolu1",
  "west" : "/d/moon/yunu1",
  "east" : __DIR__"fabao-road1",
]));

  setup();
}






