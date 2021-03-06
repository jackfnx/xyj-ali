// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/nanhai/zoulang
inherit ROOM;

void create ()
{
    set ("short", "走廊");
    set ("long", @LONG

这里是通往普陀山书院和禅房的走廊。普陀山书院藏有大量佛
经，供门人弟子们参禅修行时使用，不过外人一般说来是不允
许进入书院的。
LONG);

    set("exits", ([ /* sizeof() == 3 */
        "south" : __DIR__"chanfang",
        "west" : __DIR__"shuyuan",
        "east" : __DIR__"guangchang.c",
    ]));
    set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/honghaier" : 1,
        __DIR__"npc/jinzha" : 1,
    ]));

    setup();
}

int valid_leave(object me, string dir)
{
    object ob=present("jinzha", environment(me));
    if (me->query("family/family_name") != "南海普陀山" && dir == "west")
        if (objectp(ob) && living(ob))
            return notify_fail("\n金吒伸手拦住你，彬彬有礼地对你说道：此地乃普陀书院，"
                    + RANK_D->query_respect(ob) + "请不要乱闯。\n");

    return ::valid_leave(me, dir);
}
