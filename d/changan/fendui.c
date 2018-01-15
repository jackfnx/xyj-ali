
// Room: /d/changan/fendui.c
inherit ROOM;

void create()
{
    set("short", "荒坟堆");
    set("long", @LONG

这里是长安城南的一片荒地，周围密密麻麻地堆了好几十个坟头。
有些坟前还有些祭祀，烧纸的痕迹。四处荒凉，很少有人走动，偶
而有几只寻食的野狗跑过。
LONG);
    set("mai_corpse_able", 1);
    set("outdoors", __DIR__"");
    set("exits", ([ /* sizeof() == 1 */
        "west" : __DIR__"broadway1",
    ]));
    setup();
}

void init()
{
    add_action("do_dig", "dig");
}

int do_dig(string arg)
{
    object me;
    me = this_player();
    if ((arg!="ground") && (arg!="地"))
        return notify_fail("你想挖什么？\n");
    message_vision("$N在地上挖开一个洞，钻了进去。\n", me);
    me->move("/d/gumu/door");
    return 1;
}
