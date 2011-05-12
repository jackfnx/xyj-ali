
inherit ROOM;

void create()
{
    set("short", "兵器库");
    set("long", @LONG

这里是傲来国的兵器库，一股霉味扑鼻而来，恐怕十来年没有人进
来过了吧。偶尔拨开尘土找到一件兵器，也早已经锈迹斑斑。
LONG);

    set("exits", ([
        "north"   : __DIR__"drill",
    ]));

    set("no_magic", 1);

    setup();
    replace_program(ROOM);
}
