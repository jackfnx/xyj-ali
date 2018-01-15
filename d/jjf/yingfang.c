
inherit ROOM;

void create()
{
    set("short", "营房");
    set("long", @LONG

秦琼隐居后，除了他的家将以外，还有一些老部下也愿意追随他。
他便将这些老兄弟安置在府邸对面的一处营房内。大家都是过惯了
军旅生涯的铁血汉子，实在是闲不住，所以经常喜欢集合起来操练
一番。大柳树下躺着一个大汉，半眯着眼睛休息，看样子似乎是主
帅。
LONG);

    set("exits", ([ /* sizeof() == 1 */
        "southwest" : __DIR__"center",
    ]));
    set("objects", ([ /* sizeof() == 3 */
        __DIR__"npc/fujiang" : 2,
        __DIR__"npc/chengyaojin" : 1,
    ]));
    
    setup();
}

