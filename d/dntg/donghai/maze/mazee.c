
inherit __DIR__"maze";

void create()
{
    set("ways", ({
        __DIR__"maze1",
        __DIR__"mazeb",
        __DIR__"maze2",
        __DIR__"mazed",
        __DIR__"mazee",
    }));
    set("exits", ([
        "west"  : __DIR__"maze1",
    ]));
    set("objects", ([
        __DIR__"jinyu"  : 1,
    ]));
    setup();
}
