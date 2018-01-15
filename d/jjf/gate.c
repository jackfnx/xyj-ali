// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/jjf/gate.c

inherit ROOM;

void create()
{
   set("short", "将军府");
   set("long", @LONG

这里竟然是开国大将秦叔宝的官邸，传说秦琼获罪时被仙人所救，
将整个府邸都挪移到一处不知名的仙境，没想到竟然就是这里。如
今秦府上下的生活似乎没有收到任何影响，除了慕名而来拜访之人
少了很多。但是秦琼戎马一生，能够获得一个安闲的晚年，也未尝
不是一件幸事。这里的院子很大，门口有一对石狮子；东边是一棵
槐树，郁郁葱葱，遮盖了大半个院子，整个院子里阴凉阴凉的；南
边是个空场，大概是秦府家将演武之地。
LONG
   );
   set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"front_yard.c",
  "northeast" : __DIR__"center",
]));
   set("out_doors", 1);
   set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/qinan" : 1,
]));
   set("no_clean_up", 0);

   setup();
}

int valid_leave(object me, string dir)
{
    if (dir == "south" ) {
   if (((string)me->query("family/family_name")=="将军府") 
   ||   wizardp(me)
   ||   me->query_temp("pending/jiangjun_answer")) {
     return ::valid_leave(me, dir);
           }
     if(objectp(present("qin an", environment(me)))) {
               return
notify_fail("秦安喝道：将军府岂是你乱闯之地！有何贵干(answer)？\n");
         }
     return 1;
   }
       return 1;
   }

