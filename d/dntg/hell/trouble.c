
#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("烦恼", ({"trouble"}));
    set("env/invisibility", 1);
    set_weight(100);
    set("no_get", 1);
    seteuid(getuid());
    setup();
    call_out("destruct_me", 1200);
}

void destruct_me()
{
    destruct(this_object());
}

string short()
{
    object owner = query("owner");
    if (!owner) return "烦恼";
    else return sprintf("烦恼(owner: %s)", geteuid(owner));
}

mapping wangs = ([ "qingguang":"秦广王", "songdi":"宋帝王", "chujiang":"楚江王",
    "chuguan":"仵官王", "pingdeng":"平等王", "dushi":"都市王", "taishan":"泰山王",
    "lunzhuan":"轮转王", "biancheng":"卞城王", "yanluo":"阎罗王" ]);

string get_next(object wang);

void init()
{
    object who = this_player();
    object wang;

    if (!query("wang") && query("waiting")) {
        foreach (string w in keys(wangs)) {
            if (who->query("id") == w + " wang") {
                set("wang", who);
                delete("waiting");
                break;
            }
        }
    }
    if (query("owner") == who) {
        if (wang = query("wang"))
            wang->fully_recover();
    }
    add_action("do_complain", "complain");
    add_action("do_surrender", "surrender");
    add_action("do_kill", "kill");
}

int do_complain(string arg)
{
    object me = query("owner"), wang = query("wang");
    string complainee;
    
    if (!me || me != this_player()) return 0;
    if (!wang || environment(wang) != environment()) return 0;
    if (!arg || !wang->id(arg))
        return notify_fail("你要找谁申诉？\n");

    message_vision("$N对着$n叫道：“" + RANK_D->query_self_rude(me) +
        "早已超出三界之外，不在五行之中，已不归阴司管辖，怎么又来勾我？”\n", me, wang);
    me->command_function("bug");

    complainee = me->query_temp("dntg_hell/next");
    if (!complainee) {
        message_vision("\n$N皱了皱眉头，对$n说道：“你我阴阳殊途，" +
            "我不治你私闯幽冥之罪，也就是了。还不快快退下！”\n\n", wang, me);
        return 1;
    }
    if (wangs[complainee] != wang->name()) {
        message_vision("\n$N皱了皱眉头，对$n说道：“此事非我经手，" +
            "冤有头，债有主，哪个遣人勾你，你去找哪个吧。”\n\n", wang, me);
        me->set_temp("dntg_hell/next", get_next(wang));
        return 1;
    }
    me->delete_temp("dntg_hell/ready");
    message_vision("\n$N恼羞成怒道：“本王叫你三更死，谁敢留你到五更。"+
        "待我亲自送你去见崔判官！”\n", wang);
    wang->set_temp("target", me);
    wang->kill_ob(me);
    return 1;
}

string get_next(object wang)
{
    string who = keys(wangs)[random(sizeof(wangs))];
    while (wangs[who] == wang->query("name"))
        who = keys(wangs)[random(sizeof(wangs))];
    return who;
}

int do_surrender()
{
    object who = query("owner"), wang = query("wang");
    string next;

    if (this_player() != wang) return 0;
    if (wang->query_temp("target") != who) return 0;

    who->set_temp("dntg_hell/" + wang->name(), 1);
    message_vision(HIW "\n$N说道：「不打了，不打了，我投降....。」\n\n" NOR, wang);
    wang->command_function("say "+who->name()+RANK_D->query_respect(who)+
        "神通广大，小王甘拜下风。");
    next = get_next(wang);
    who->set_temp("dntg_hell/next", next);
    message_vision("$N翻了翻案上的文书，对$n说道：“此事乃" + wangs[next]
        + "传文至此，要小王勾拿" + RANK_D->query_respect(who) + "，" + RANK_D->query_respect(who)
        + "还是去找他理论吧。\n\n", wang, who);

    if (who->query_temp("dntg_hell/" + wangs[next]))
        who->set_temp("dntg_hell/ready", wang);

    return 1;
}

int do_kill(string arg)
{
    object who = query("owner"), wang = query("wang");
    string next;

    if (this_player() != who) return 0;
    if (present(arg, environment()) != wang) return 0;
    if (who->query_temp("dntg_hell/ready") != wang) return 0;
    if (who->query("dntg/hell") == "done") return 0;
    if (!(next = who->query_temp("dntg_hell/next"))) return 0;

    message_vision("$N拍案大叫：“怎么又是" + wangs[next]
        + "？！你这奸王竟敢耍弄于我！拿命来！”\n\n", who);
    message_vision("$N吓得魂飞魄散，颤身说：“罢了罢了，依你，都依你。”\n", wang);
    message_vision("$N从案上拿出生死簿，提起朱笔，饱蘸浓墨，将$n的名字划去。\n\n", wang, who);

    who->set("dntg/hell", "done");
    wang->command_function("chat "+ who->query("name") +"这"+ RANK_D->query_rude(who) +
        "逞强行凶，不服拘唤，大闹罗森，强销名号，待我上天禀明玉帝，再来拿你！");
    wang->delete_temp("target");
    who->delete_temp("dntg_hell");

    __FILE__->uninstall();
    return 1;
}

void install(object owner, string* rooms)
{
    object o;
    
    if (clonep()) return;
    
    for (int i = 0; i < sizeof(rooms); i++) {
        o = new(__FILE__);
        o->set("owner", owner);
        o->set("waiting", 1);
        o->move(rooms[i]);
    }
}

void uninstall()
{
    if (clonep()) return;
    
    foreach (object o in children(__FILE__))
        if (o != this_object()) destruct(o);
    
    destruct(this_object());
}
