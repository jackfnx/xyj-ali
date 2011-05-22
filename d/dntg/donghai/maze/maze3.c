
inherit __DIR__"maze";

void create()
{
    set("ways", ({
        __DIR__"maze2",
        __DIR__"mazeb",
        __DIR__"mazec",
        __DIR__"maze1",
        __DIR__"maze2",
    }));
    set("exits", ([
        "east"  : __DIR__"maze4",
    ]));
    setup();
}
