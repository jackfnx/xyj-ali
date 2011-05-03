// ALi by NewX

inherit ROOM;

void create()
{
   set("short", "杏林");
   set("long", @LONG

一片冷冷清清的杏林，杏林中有一位孤独的老人。此刻他拄着木杖，
坐在一块大石头上，正在颤巍巍地翻阅着一本看起来有些特别的簿
子(book)。
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
