// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /moon/ontop.c
//cglaem...12/13/96.

inherit ROOM;

void create ()
{
  set ("short", "月门");
  set ("long", @LONG

一个月牙状的小门，那门栏窗格，俱是细雕新鲜花样，并无朱粉涂饰，一
色水磨群墙；下面白石台阶，凿成梅花样。左右一望，皆雪白粉墙，下面
虎皮石，随势砌去。门口有一株桂树(tree)，郁郁苍苍。空气虽冷，却有
花香习习，令人精神备爽。
LONG);

  set("item_desc", ([ /* sizeof() == 1 */
  "tree" : "一株高耸入云的大桂树 。上面无数的桂花
正散发出阵阵清香，不知道怎样才能采集到。
",
]));
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"obj/guishuzhi" : 1,
  __DIR__"npc/girl" : 1,
]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
  "enter" : __DIR__"road1",
  //"down" : __DIR__"tree2",
]));

  setup();
}

void init()
{
    add_action("do_climb", "climb");
}

int do_climb(string arg)
{
    object me = this_player();

    if (!arg || (arg != "tree" && arg != "桂树"))
        return notify_fail("爬什么？\n");

    message_vision("$N顺着树干出溜了下去。\n", me);
    me->move(__DIR__"tree2.c");
    message_vision("$N从桂树上出溜了下来。\n", me);
    return 1;
}
