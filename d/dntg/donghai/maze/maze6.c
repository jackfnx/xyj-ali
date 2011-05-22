
inherit __DIR__"maze";

void create()
{
    set("ways", ({
        __DIR__"mazea",
        __DIR__"maze3",
        __DIR__"maze2",
        __DIR__"mazed",
        __DIR__"maze3",
    }));
    set("exits", ([
        "south" : __DIR__"mazeend",
    ]));
    setup();
}
