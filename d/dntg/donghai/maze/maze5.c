
inherit __DIR__"maze";

void create()
{
    set("ways", ({
        __DIR__"mazea",
        __DIR__"mazeb",
        __DIR__"mazec",
        __DIR__"mazed",
        __DIR__"mazee",
    }));
    set("exits", ([
        "west"  : __DIR__"maze6",
    ]));
    setup();
}
