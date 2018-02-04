// ALi by NewX

inherit ROOM;

void create ()
{
    set("short", "绮梦殿堂");
    set("long", @LONG

这里是古墓弟子梦寐以求的殿堂，只有那些立下大功的弟子才有资格
进入这里享乐。这里有无穷无尽的阳精供你品尝，也有无穷无尽的猛
男可以把你伺候的无微不至。
大多数弟子到了这里，都会敞开心怀，放纵的享受性爱的美妙。但也
有些最强大的弟子可以把这里当成一个挑战。在这里接受雄奴们七天
七夜的服侍，若是能保持本性，不被欲望征服，那么这个弟子就离出
师不远了。

LONG);

    set("objects", ([ /* sizeof() == 3 */
        __DIR__"npc/dickslaver" : 3,
        __DIR__"npc/enjoygirl" : 1,
    ]));

    set("exits", ([ /* sizeof() == 1 */
        "east" : __DIR__"shidong3",
    ]));

    setup();
}

