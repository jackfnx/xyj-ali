// ALi by NewX
 
// Room: /d/city/qilin.c

inherit ROOM;

void create()
{
    set("short", "麒麟阁");
    set("long", @LONG

太宗李世民在即位前受封秦王，手下谋臣勇将为建立李氏王朝立下了
汗马功劳。高祖为这些功臣们特起了一座彩楼，名曰「麒麟阁」。此
楼飞檐挂角，雕梁画栋，建成之时吸引了无数百姓前来观看。可惜，
如今秦琼获罪，那一班功臣已经风流云散，这里也冷清了下来。偶尔
才有几个文人过来凭吊一番，发出几声酸酸的感叹。
LONG
    );
    set("no_fight", 1);
    set("item_desc", ([ /* sizeof() == 1 */
        "up" : "楼上冷冷清清，寂寂无声，似乎一个人也没有。",
    ]));
    set("no_clean_up", 0);
    set("light_up", 1);
    set("exits", ([ /* sizeof() == 2 */
        "up" : __DIR__"qilin2",
        "east" : __DIR__"xuanwu-n1",
    ]));
    set("objects", ([
        "/d/obj/misc/chairs" : 4,
        "/d/obj/misc/tables" : 1,
    ]));

    setup();
    replace_program(ROOM);
}
