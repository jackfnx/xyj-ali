// ALi by NewX

inherit ROOM;

void create()
{
   set("short", "杏林");
   set("long", @LONG

不知从何时开始昆仑山的玉女峰上便有了这么一片杏林，杏林
中便有了这么一位老人。他总在花前月下出现，为天下的有情
人祝福，主婚。此刻他拄着木杖，坐在一块大石头上，正在认
真地翻阅着一本看起来很特别的簿子(book)。
LONG
   );

   set("no_fight", "1");
   set("no_magic", "1");
   set("no_sleep_room", "1");

   set("item_desc", ([
     "book" : "这簿子被涂抹的乱七八糟，勉强能辨认出封面上的几个字：《姻缘簿》\n"
     ]));

   set("exits", ([
     "out" : __DIR__"yltw",
   ]));

   set("objects", ([
     __DIR__"npc/yuelao": 1,
   ]));

   setup();
}
