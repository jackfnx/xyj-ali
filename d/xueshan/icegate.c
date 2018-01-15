//standroom.c used by weiqi...others may hate this format:D
//icegate.c

inherit ROOM;

void create ()
{
   set ("short", "冰宫大门");
   set ("long", @LONG

放眼望去，这座冰宫通体雪明，当真是巍峨壮观。但是此刻宫门
紧闭，一位身披银甲的壮汉和一位面目阴森的老者正神情紧张地
守在门前。
LONG);

   set("exits", 
   ([ //sizeof() == 1
     "south" : __DIR__"wuchang-n",
   ]));
   
   set("objects", 
   ([ //sizeof() == 1
     __DIR__"npc/tuying-guai" : 1,
     __DIR__"npc/baixiang-xiaow" : 1,
   ]));


   set("outdoors", "xueshan");

   setup();
}
