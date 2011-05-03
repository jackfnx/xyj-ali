// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: ylt.c
// AceP

inherit ROOM;

void create ()
{
  set ("short", "杏林外");
  set ("long", @LONG

这儿是杏林外一片乾净整齐的草地。据说这处杏林本是月老的办公
之所，订婚的少男少女往往到此拜竭月并在杏林中举行婚礼。一些
有生意头脑的人，发现婚礼是个好买卖，就在这儿开了张，花轿，
轿夫，吹鼓手，一应俱全。可惜如今三界大乱，再也没人来找月老
成亲了，这里的生意顿时一落千丈。
LONG);

  set("objects", ([ /* sizeof() == 5 */
  __DIR__"obj/jiaozi" : 1,
  __DIR__"npc/jiaofu" : 1,
  __DIR__"npc/lgshou" : 1,
  __DIR__"npc/jftou" : 1,
  __DIR__"npc/snshou" : 1,
]));
  set("no_steal", "1");
  set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"ontop2",
  "enter" : __DIR__"ylt",
]));
  set("no_sleep_room", "1");
  set("no_fight", "1");
  set("outdoors", 1);

  setup();
}
