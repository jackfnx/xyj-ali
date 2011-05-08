// ALi by NewX
inherit ROOM;

void create()
{
    set("short", "雪路");
    set("long", @LONG

路又渐渐变得难走了。这里的积雪很厚，而且因为走的人很多，积雪
都被踩实了，都被踩得溜光溜滑的，稍不小心就会摔倒。即使是常年
生活在这里的雪山弟子，一不小心也会摔倒。沿路上，经常可以看到
摔到仆街的雪山弟子，看着他们啪叽啪叽的摔着嘴啃泥，你自己都觉
得好疼。
LONG);

    set("exits", ([ //sizeof() == 4
        "north" : __DIR__"xuejie-1",
        "south" : __DIR__"wuchang-n",
    ]));

    set("objects", ([
        __DIR__"obj/ice" : 1,
    ]));

    set("outdoors", "xueshan");

    setup();
}

int valid_leave(object me, string dir)
{
    if (random(me->query_kar()) < 15 && (int)me->query_skill("dodge") < 100) {
        message_vision("$N刚一迈步，忽然脚下一滑，摔了个嘴啃泥！好疼！\n", me);
        if (me->query("kee") < 50)
            me->unconcious();
        else
            me->receive_damage("kee", 50);
        return notify_fail("你疼得直咧嘴。\n");
    }
    return ::valid_leave(me, dir);
}
