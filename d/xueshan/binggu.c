//binggu.c

inherit ROOM;

void create ()
{
   set ("short", "冰谷");
   set ("long", @LONG

眼前的情景把你惊呆了。没想到在这绝无生迹的冰天雪地中还有
这么一块地方。四周望不到顶的冰崖把这里围成了一个方圆近十
里的山谷。紧靠冰崖有大小建筑数十座。
LONG);

   set("exits", ([ //sizeof() == 3
     "north" : __DIR__"wuchang-s",
     "west" : __DIR__"wroad1",
     "east" : __DIR__"eroad1",
   ]));
   
   set("objects", ([ //sizeof() == 1
     __DIR__"npc/zhangmen" : 1,
   ]));

   set("outdoors", "xueshan");

   setup();
}



