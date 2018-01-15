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
    add_action ("do_sleep","sleep");
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

int is_drunk(object me)
{
    int limit = me->query("con")*6+(int)me->query("max_force")/50;
    int duration = me->query_condition("drunk");
    return (duration > limit / 10);
}

int do_sleep (string arg)
{
    object me = this_player();
    int phase = NATURE_D->get_current_day_phase();

    if (me->query("combat_exp") < 50000) return 0;
    if (me->query("dntg/hell") == "done") return 0;
    if (me->query_temp("dntg_hell/next")) return 0;

    if (phase > 0 && phase < 5) {
        tell_object(me, "大白天的睡什么觉？\n");
        return 1;
    }
    if (!is_drunk(me)) {
        tell_object(me,"你精神十足，不需要睡觉。\n");
        return 1;
    }

    message_vision("$N喝得酩酊大醉，倚在在铁板桥边松阴之下，霎时间睡着了。\n", me);
    remove_call_out("go_hell");
    me->start_busy(7);
    call_out("go_hell", 2+random(5), me);
    return 1;
}

void go_hell(object me)
{
    object env;
    object hei, bai;
    object piwen;
    mapping wangs = (["qingguang":"秦广王","songdi":"宋帝王","chujiang":"楚江王",
        "chuguan":"仵官王","pingdeng":"平等王","dushi":"都市王","taishan":"泰山王",
        "lunzhuan":"轮转王","biancheng":"卞城王","yanluo":"阎罗王"]);
    string wang = ((string *)keys(wangs))[random(sizeof(wangs))];

    me->interrupt_me(0, 0);
    me->set_temp("dntg_hell/next", wang);

    tell_object(me, HIB"\n睡梦中忽见两人走了过来，大声喝道：“"+me->query("name")+
                "，汝阳寿已尽，吾等奉冥王之命，特来勾你。”\n"
                +"说罢不容分说，拿根铁索往你颈上一套，拉了就走。\n\n"NOR);
    env = load_object("/d/death/new-zhaopo");
    if (!bai = present("bai wuchang", env)) {
        bai = new("/d/death/npc/baiwuchang");
        bai->move(env);
    }
    if (!hei = present("hei wuchang", env)) {
        hei = new("/d/death/npc/heiwuchang");
        hei->move(env);
    }
    me->move(env);

    piwen = new("/d/dntg/hell/piwen");
    if (random(2)) piwen->move(hei);
    else piwen->move(bai);
    piwen->set("long","    查"+me->query("name")+
                "阳寿已尽，着令黑白无常将其魂魄勾拿归案。\n\n"+
                "                            "+wangs[wang]+"  谕\n\n\n");

    piwen->set("target", me->query("name"));
}
