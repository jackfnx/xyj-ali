// ALi By NewX

//self-made fabao room

inherit ROOM;

void create ()
{
    set ("short", "女娲补天处");
    set ("long", @LONG

这里是一片开阔地。地上铺满了一堆又一堆奇形怪状色彩斑斓的
残岩碎石，在雪色映照下溢彩流光。边上一块大石上刻着几行大
字：

    昆仑绝处
    女娲补天
    彩石未尽
    遗福後人

底下还密密麻麻地刻了一篇小字(words)，隔远了也看不清说的是
什么。
LONG);

    set("item_desc", ([ "words" : "你离近了也还是没看清楚\n", ]));

    set("exits", 
    ([ //sizeof() == 1 
            "east" : __DIR__"fabao-road2",
    ]));

    setup();
}
