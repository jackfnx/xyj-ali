
//eroad2.c

inherit ROOM;

void create ()
{
   set ("short", "小木屋外");
   set ("long", @LONG

很难想象这些木头是从哪里来的。但是这里的确是一间小木屋。
周围是一道冰制的围墙，也不过半人来高。
LONG);

   set("exits", ([ //sizeof() == 3
     "south" : __DIR__"xiaomuwu",
     "west" : __DIR__"eroad1",
     "east" : __DIR__"eroad3",
   ]));

   set("objects", ([ //sizeof() == 1
     __DIR__"npc/shier" : 2,
   ]));

   set("outdoors", "xueshan");

   setup();
}

int valid_leave(object me, string dir)
{
    object shier;
    if (dir == "south") {
        if (objectp(shier = present("shi er", environment(me))) && living(shier)) {
            if (me->query("family/family_name") == "大雪山" && (int)me->query("family/generation") <= 3)
                message_vision("$N低眉顺目向$n行礼。\n", shier, this_player());
            else 
                return notify_fail("侍儿把你一拦道：公主有令，任何人不得入内打搅！\n");
        }
    }

    return ::valid_leave(me, dir);
}

