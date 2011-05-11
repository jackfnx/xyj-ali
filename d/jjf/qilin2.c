// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/jjf/qilin2.c

inherit ROOM;

void create()
{
   set("short", "麒麟阁二楼");
   set("long", @LONG

二楼比起一楼来，只有更加豪华气派。墙(wall)上绘着几幅壁画，尽
是沙场景象，一幅是秦琼走马取关，一幅是程咬金斧劈隋将，一副是
尉迟恭单鞭夺槊，一副是罗成枪扫群雄。席间一位黑脸将军正在和一
位道袍老者开怀畅饮。

LONG
   );
   set("light_up", 1);
   set("no_clean_up", 0);
   set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/yuchigong" : 1,
  __DIR__"npc/xumaogong" : 1,
]));
   set("exits", ([ /* sizeof() == 1 */
  "down" : __DIR__"qilin",
]));

   setup();
   replace_program(ROOM);
}
