
inherit __DIR__"maze";

void create()
{
    set("ways", ({
        __DIR__"maze1",
        __DIR__"mazeb",
        __DIR__"maze1",
        __DIR__"mazed",
        __DIR__"mazee",
    }));
    set("exits", ([
        "north" : __DIR__"maze3",
    ]));
    setup();
}
