// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/jjf/nogate.c

inherit ROOM;

void create()
{
    set("short", "将军府");
    set("long", @LONG

这里本是当朝大将秦叔宝的官邸，可是自从秦琼犯事以后这里便被查
封了，如今已经很少有人来了。
LONG
   );
    set("exits", ([ /* sizeof() == 1 */
        "north" : "/d/city/qinglong-e2",
    ]));
   set("out_doors", 1);
   set("no_clean_up", 0);

   setup();
}
