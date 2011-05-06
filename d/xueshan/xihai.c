//standroom.c used by weiqi...others may hate this format:D
//xihai.c

inherit ROOM;

void create ()
{
   set ("short", "西海之畔");
   set ("long", @LONG

见惯了一望无际的雪原，巍峨雄伟的冰山，突然间碧波万顷，浩
瀚壮阔的水面展现在面前，你顿时觉得一股柔情蜜意涌上心头。
山，湖，草，鸟，仿佛是到了另一个世界。
LONG);

   set("exits", ([ //sizeof() == 1
     "east" : __DIR__"xueshan5",
   ]));
   
   set("objects", ([ //sizeof() == 1
     __DIR__"npc/hama" : 1,
   ]));

   set("outdoors", "xueshan");

   setup();
}
