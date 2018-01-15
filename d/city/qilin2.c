// ALi by NewX
 
// Room: /d/city/qilin2.c

inherit ROOM;

void create()
{
    set("short", "麒麟阁二楼");
    set("long", @LONG

二楼比起一楼来，只有更加豪华气派。墙(wall)上绘着几幅壁画，尽
是沙场景象，一幅是秦琼走马取关，一幅是程咬金斧劈隋将，一副是
尉迟恭单鞭夺槊，一副是罗成枪扫群雄。端的是气势磅礴，可惜周围
人声寥寥，惨惨戚戚，只能给人留下无数感怀。
LONG
    );
    set("item_desc", ([
        "wall" : @WALL

墙上的壁画固然气势磅礴，不过你却留意到那不起眼的地方有一行小
字：

　　　　小子！眼神不错啊！居然能看到这些字！
　　　　老黑我看对面那座楼不顺眼！你要是能把那座楼拆了，
　　老黑我送你一份机缘。
　　　　记住了，拆了楼以后，拿着柱子回来。在这行字下面
　　可以找到一个洞。插进去！然后你就知道了。
　　　　嘿嘿！
　　　　　　　　　　　　　　　　　　　　　　尉迟恭　留

你仔细找了找，果然在不起眼的角落里有一个圆形的洞(hole)。
WALL,
    ]));
    set("light_up", 1);
    set("no_clean_up", 0);
    set("exits", ([ /* sizeof() == 1 */
        "down" : __DIR__"qilin",
    ]));
    set("objects", ([
        "/d/obj/misc/chairs" : 4,
        "/d/obj/misc/tables" : 1,
    ]));

    setup();
}

void init()
{
    add_action("do_insert", "insert");
}

int do_insert(string arg)
{
    object me=this_player(), here=this_object(), ob, book;

    if (!arg || arg != "zhu zi into hole")
        return notify_fail("你要把什么插入什么里面(insert ** into **)？\n");
    if (!(ob = present("zhu zi", me)))
        return notify_fail("你身上没有这样东西(zhu zi)。");
    if ((string)ob->query("name_recognized")!="醉星楼柱子")
        return notify_fail("你这个柱子的尺寸不对，塞不进去。");
    if (me->query_temp("weapon") == ob)
        return notify_fail("你不能把当前的武器插入洞里面。\n");

    message_vision("$N将一根柱子插入到一个圆形的洞里，用力一拧。\n", me);
    message_vision("整座楼突然开始剧烈的晃动，你站立不稳，啪叽一下摔了个屁股蹲。\n", me);
    message_vision("就在你认为楼要塌了的时候，晃动突然停止了。\n", me);
    if (!here->query("book_drop")) {
        message_vision("忽然，啪嗒一声，一本书从不知道什么地方掉了出来，掉在了地板上。\n", me);
        ob->move(here);
        destruct(ob);
        book=new("/d/obj/book/parrybook2");
        book->move(here);
        here->add("book_drop", 1);
    }
    else {
        tell_object(me, "你等了半天，什么也没发生，难道这是尉迟恭的恶作剧？\n");
    }
    return 1;
}