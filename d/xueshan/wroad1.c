
//wroad1.c

inherit ROOM;

void create ()
{
   set ("short", "冰崖底");
   set ("long", @LONG

看样子前面是过不去了。往西的路被一块大牌子堵死。牌子上用
醒目的大字写着：“冰谷禁地，擅闯者死！”。
LONG);

   set("exits", ([ //sizeof() == 1
     "east" : __DIR__"binggu",
   ]));

   set("outdoors", "xueshan");

   setup();
}
