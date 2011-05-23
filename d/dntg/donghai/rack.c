// rack.c

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("兵器架",({"rack"}));
    set("env/invisibility",1);
    set_max_encumbrance(50000000);
    set_max_items(10000);
    set_weight(100);
    set("no_get",1);
    set("no_magic", 1);
    set("no_fight", 1);
    seteuid(getuid());
    setup();
}

string short()
{
    object owner = query("owner");
    if (!owner) return "兵器架";
    else return sprintf("兵器架(owner: %s)", geteuid(owner));
}

void init()
{
    add_action("do_kun", "kun");
    call_out("start_organize", 5, this_player());
}

int check_in_aolai(object ob, object helper)
{
    if (sscanf(file_name(environment(ob)), "/d/4world/%*s") == 1) {
        helper->speak(({ CYN "说道：咦？你怎么回来了？我不是告诉你离傲来国远点吗？怎么不听我的话啊！" NOR }));
        call_out((: call_other, helper, "disappear" :), 3);
        return 1;
    }
    return 0;
}

void start_organize(object me)
{
    object owner;
    object helper;

    if (!(owner = query("owner")) || me != owner) return;
    if (!(helper = owner->query_temp("dntg_helper"))) return;
    if (owner->query("dntg/huaguo") != "done") return;
    if (owner->query("dntg/donghai")) return;
    if (environment(owner)->query("exercising")) return;
    if (query("organizing")) return;

    helper->speak(({
            CYN "说道：嘿嘿嘿嘿，没办法了吧，找不到兵器吧？" NOR,
            CYN "说道：大爷我有办法！" NOR,
            CYN "说道：你家金箍棒大爷会作法让傲来国国王心血来潮，搞一次演习。" NOR,
            CYN "说道：不过在这个期间，你可得离傲来国远点。" NOR,
            CYN "说道：万一刺激了傲来国，让演习取消了，那可就不好办了。" NOR,
            0,
            0,
            0,
            (: call_other, this_object(), "organize_exercise", 0 :),
    }));
}

void organize_exercise(int prog)
{
    object owner, helper;
    if (!(owner = query("owner"))) return;
    if (!(helper = owner->query_temp("dntg_helper"))) return;
    
    switch (prog) {
        case 0:
            helper->speak(({ CYN "说道：行了我已经开始作法了，可千万别回来了啊。" NOR }));
            break;
        case 1:
        case 2:
        case 3:
            if (check_in_aolai(owner, helper)) return;
            break;
        case 4:
            if (check_in_aolai(owner, helper)) return;
            helper->speak(({ CYN "说道：行了，傲来国的演习已经在筹备中了，兵器也在打造中了，现在可千万别回去啊。" NOR }));
            break;
        case 5:
        case 6:
            if (check_in_aolai(owner, helper)) return;
            helper->speak(({ CYN "说道：嗯！已经打造的差不多了，再等等就好了。" NOR }));
            break;
        case 7:
        case 8:
            if (check_in_aolai(owner, helper)) return;
            break;
        default:
            if (check_in_aolai(owner, helper)) return;
            helper->speak(({ CYN "说道：哈哈哈，成了，成了，走走走，回去取我们的兵器吧。" NOR }));
            call_out("start_exercise", 1, helper);
            return;
    }
    call_out("organize_exercise", 10, prog + 1);
}

void start_exercise(object helper)
{
    object ob, room, entrance;

    // drill entrance room
    room = helper->get_drillent_room();
    entrance = room;
    room->set("o_long", room->query("long"));
    room->set("long", @LONG

这里是傲来国演武场的入口，往常这里是没什么人的，但是今天似
乎有点特别，这里站立着几个威武的禁军教头，盯着来往的行人。
演武场里面也不时传来雄壮的号角声。
LONG);
    tell_object(room, "一队队军士开进了演武场，陆陆续续还有文臣武将也来到演武场，几个威武的禁军教头把手在门前。\n");
    tell_object(room, "看样子这里的把守严密了很多，可能是要出什么事了。\n");
    ob = new(__DIR__"jiaotou");
    ob->move(room);
    ob = new(__DIR__"jiaotou");
    ob->move(room);
    set("drillent_room", room);

    // drill room
    room = helper->get_drill_room();
    room->set("o_long", room->query("long"));
    room->set("long", @LONG

傲来国演武场，文官武将，各穿锦衣；帐下偏裨将校，都披银铠，
分两行；左右军士，皆全装惯带，持戈执戟而立；中间一行行兵士
威风凛凛的穿行于其中。
LONG);
    tell_object(room, "一队队军士开进了演武场，陆陆续续还有文臣武将也来到演武场。\n");
    tell_object(room, "难道是要演习了？这可是百年不遇的新鲜事啊。\n");
    foreach (object o in all_inventory(room)) {
        if (userp(o)) {
            tell_object(o, "几个军士跑过来，喝到：军事演习！闲杂人等退散！\n");
            tell_object(o, "几个军士把你一把架起，扔出了演武场。\n");
            tell_room(room, "军士们把" + o->name() + "赶了出去。\n", ({ o }));
            o->move(entrance);
            tell_object(o, "啪叽一声，你被摔在了演武场入口处，摔得你眼冒金星。\n");
            tell_room(entrance, o->name() + "被从演武场中扔了出来。\n", ({ o }));
        } else {
            tell_room(o, "几个军士七手八脚的把" + o->name() + "清理掉。\n");
            destruct(o);
        }
    }
    ob = new(__DIR__"jiaotou");
    ob->move(room);
    ob = new(__DIR__"jiaotou");
    ob->move(room);
    ob = new(__DIR__"junshi");
    ob->move(room);
    ob = new(__DIR__"junshi");
    ob->move(room);
    set("drill_room", room);

    // arsenal room
    room = helper->get_arsenal_room();
    room->set("o_long", room->query("long"));
    room->set("long", @LONG

这里是傲来国的兵器库，里面各种兵器(bingqi)：刀、枪、剑、戟、
斧、钺、毛、镰、鞭、钯、挝、锏、弓、弩、叉、矛，件件俱备。
整整齐齐的堆放着，几个威武的武士在这里把守着。
LONG);
    room->set("item_desc", ([
            "bingqi" : "各种各样的兵器，看来想拿走不方便，得捆(kun)一下才好拿。\n"
        ]));
    room->set("exercising", 1);
    foreach (object o in all_inventory(room)) {
        if (o == this_object()) {
        
        } else if (userp(o)) {
            tell_object(o, "几个军士跑过来，喝到：军事演习！闲杂人等退散！\n");
            tell_object(o, "几个军士把你一把架起，扔出了演武场。\n");
            tell_room(room, "军士们把" + o->name() + "赶了出去。\n", ({ o }));
            o->move(entrance);
            tell_object(o, "啪叽一声，你被摔在了演武场入口处，摔得你眼冒金星。\n");
            tell_room(entrance, o->name() + "被从演武场中扔了出来。\n", ({ o }));
        } else {
            tell_room(o, "几个军士七手八脚的把" + o->name() + "清理掉。\n");
            destruct(o);
        }
    }
    ob = new(__DIR__"pianjiang");
    ob->move(room);
    ob = new(__DIR__"pianjiang");
    ob->move(room);
    ob = new(__DIR__"pianjiang");
    ob->move(room);
    ob = new(__DIR__"pianjiang");
    ob->move(room);
    set("arsenal_room", room);
    
    call_out("finish_exercise", 1200);
}

void finish_exercise()
{
    object room;

    if (room = query("arsenal_room")) {
        room->set("long", room->query("o_long"));
        room->delete("o_long");
        room->delete("item_desc");
        room->delete("exercising");
        tell_object(room, "演习似乎结束了，守卫的偏将们把这里的兵器收拾一下搬走了。\n");
        tell_object(room, "听他们闲谈的意思，似乎是想把这些兵器卖掉还钱。\n");
        tell_object(room, "你终于明白这里平时为什么没有兵器了。\n");
        foreach (object ob in all_inventory(room)) {
            if (!userp(ob) && ob != this_object()) destruct(ob);
        }
    }
    
    if (room = query("drill_room")) {
        room->set("long", room->query("o_long"));
        room->delete("o_long");
        tell_object(room, "演习似乎结束了，军士们陆续都离开了，文臣武将们更是早就溜了。\n");
        tell_object(room, "军士们临走前还打扫了一下卫生，把周围的垃圾都清理掉了。\n");
        foreach (object ob in all_inventory(room)) {
            if (!userp(ob) && ob != this_object()) destruct(ob);
        }
    }
    
    if (room = query("drillent_room")) {
        room->set("long", room->query("o_long"));
        room->delete("o_long");
        tell_object(room, "演习似乎结束了，一队队军士纷纷离开了演武场，这里又恢复了往日的宁静。\n");
        foreach (object ob in all_inventory(room)) {
            if (!userp(ob) && ob != this_object()) destruct(ob);
        }
    }
    
    destruct(this_object());
}

void weather_effect(string weather)
{
    if (weather != "wind") return;
    call_out("away", 2, this_player());
    call_out("go_back", 60, this_player());
}

void away(object who)
{
    object where = environment();
    object who1 = present("pian jiang 1", where);
    object who2 = present("pian jiang 2", where);

    if (!who1) return;

    destruct(who1);
    destruct(who2);
    tell_object(where, "狂风吹得人们都挣不开眼，几个偏将哭嚎着跑了出去。\n");
}

void go_back(object who)
{
    object who1, who2;
    object where = environment();

    // mon 3/24/99
    // prevent getting too many pian jiang by go_back.
    // at most 4.
    if (present("pian jiang 4", where)) return;

    who1 = new(__DIR__"pianjiang");
    who2 = new(__DIR__"pianjiang");
    who1->move(where);
    who2->move(where);
    tell_object(where, "偏将们揉着眼睛走回兵器库。\n");
}

int do_kun(string arg)
{
    object me = this_player();
    object env = environment();
    object jiang, bingqi;

    if (!arg || arg != "bingqi")
        return notify_fail("你要捆什么？\n");
    if (!env->query("exercising"))
        return notify_fail("这里没有兵器\n");
    if (objectp(jiang = present("pian jiang", environment(me))) && living(jiang))
        return notify_fail("偏将大喝道：敢动我国兵器库里的东西，反了不成？\n",me);
    if (me->is_busy())
        return notify_fail("你正在忙着呢。\n");

    if (me->query("kee") < 50)
        me->unconcious();
    else {
        me->receive_damage("kee", 50);
        message_vision("$N急急忙忙收拾起一堆兵器，捆了捆，背了起来，又撒了一些。\n", me);
        bingqi = new(__DIR__"bingqi");
        bingqi->move(me);
        me->start_busy(5, 5);
    }
    return 1;
}
