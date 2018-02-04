#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
    set("short", "铁板桥");
    set("long", @LONG

你欠身上桥头，再走再看，却似有人家住处一般，真个好所在。但见那：

　　翠藓堆蓝，白云浮玉，光摇片片烟霞。虚窗静室，滑凳板生花。乳窟
　　龙珠倚挂，萦回满地奇葩。又见那一竿两竿修竹，三点五点梅花。几
　　树青松常带雨，浑然相个人家。

看罢多时，跳过桥中间，左右观看，只见正当中有一石碣(shi jie)。
LONG
    );

    set("item_desc", ([
        "shi jie": @SHIJ
　　　　　　□□□　　　　□□□
　　　　　　□水□　　　　□花□　　　　
　　　　　　□帘□　　　　□果□　　　　　
　　　　　　□洞□　　　　□山□　　　　
　　　　　　□洞□　　　　□福□　　　　
　　　　　　□天□　　　　□地□　　　　
　　　　　　□□□　　　　□□□
SHIJ
    ]));

    set("exits", ([
        "east"   : __DIR__"shifang",
    ]));
    create_door("east", "石门", "west", DOOR_CLOSED);
    setup();
}

void init ()
{
    add_action("do_jump", "jump");
}

int do_jump(string arg)
{
    object me = this_player();
    if (!arg || (arg != "bridge" && arg != "qiao"))
        return notify_fail("你往哪儿跳？\n");

    if (random(30) + me->query("kar") < 30) {
        message_vision("$N奋力向上一跃，又从半空中摔了下来。\n", me);
        me->unconcious();
    } else {
        message_vision("$N从桥上飞身纵出瀑布。\n", me);
        me->move(__DIR__"fall");
    }

    return 1;
}
