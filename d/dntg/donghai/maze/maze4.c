
inherit __DIR__"maze";

void create()
{
    set("ways", ({
        __DIR__"mazea",
        __DIR__"mazeb",
        __DIR__"maze3",
        __DIR__"maze2",
        __DIR__"maze1",
    }));
    set("exits", ([
        "south" : __DIR__"maze5",
    ]));
    setup();
}
