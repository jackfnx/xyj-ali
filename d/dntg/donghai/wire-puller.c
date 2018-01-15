// wire-puller.c

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name("幕后操纵者", ({"wire-puller"}));
    set("env/invisibility", 1);
    set_weight(100);
    set("no_get", 1);
    seteuid(getuid());
    setup();
}

string short()
{
    object owner = query("owner");
    if (!owner) return "幕后操纵者";
    else return sprintf("幕后操纵者(owner: %s)", geteuid(owner));
}

void start_testing()
{
    object owner = query("owner");
    object ao = present("ao guang", environment());

    if (!owner) {
        call_out("destruct_me", 1);
        return;
    }
    if (!ao || !ao->is_character()) {
        call_out("destruct_me", 1);
        return;
    }
    if (!ao->query("dntg_questing")) {
        ao->set("inquiry/weapon", (: call_other, this_object(), "ask_for_testing" :));
        ao->set("inquiry/bingqi", (: call_other, this_object(), "ask_for_testing" :));
        ao->set("inquiry/兵器", (: call_other, this_object(), "ask_for_testing" :));
        ao->set_temp("wire-puller", this_object());
    }
    set("ao", ao);
    call_out("destruct_me", 1200);
}

int ask_for_testing()
{
    object ao = query("ao");
    object who = this_player();
    object fighter;
    string weapon_name, weapon_id, weapon_unit, trying, respect;

    if (!ao || who != query("owner")) return 0;

    if (who->query("dntg/donghai") == "begin")
        { weapon_name="大砍刀"; weapon_id="da kan dao"; weapon_unit="柄"; trying="try_dao"; }
    else if (who->query("dntg/donghai") == "da kan dao")
        { weapon_name="九股叉"; weapon_id="jiu gu cha"; weapon_unit="支"; trying="try_cha"; }
    else if (who->query("dntg/donghai") == "jiu gu cha")
        { weapon_name="梅花锤"; weapon_id="mei hua chui"; weapon_unit="对"; trying="try_chui"; }
    else if (who->query("dntg/donghai") == "mei hua chui")
        { weapon_name="画杆戟"; weapon_id="hua gan ji"; weapon_unit="柄"; trying="try_ji"; }
    else if (who->query("dntg/donghai") == "hua gan ji") {
        ao->command_function("consider");
        message_vision("从后宫跑来一个龙婆，在$N耳边小声说了几句话。\n", ao);
        call_out("sendto_maze", 3);
        return 1;
    } else if (who->query("dntg/donghai")=="done")
        return 0;
    else {
        ao->command_function("nod");
        message_vision("$N懒洋洋的说：“要兵器啊？傲来国有的是，去那里弄些吧。”\n", ao);
        message_vision("$N顿了顿，又说：“我龙宫的兵器，谅你们这些凡夫俗子也使不了。”\n", ao);
        ao->command_function("wave");
        return 1;
    }

    fighter = present("ye cha", environment());
    if (present(weapon_id, this_player()) && fighter)
        message_vision("$N道：您先拿这"+weapon_unit+weapon_name+"和$n练练吧！\n", ao, fighter);
    else if (present(weapon_id, environment()) && fighter)
        message_vision("$N道：您先拿这"+weapon_unit+weapon_name+"和$n练练吧！\n", ao, fighter);
    else if (present(weapon_id, this_player()) || present(weapon_id, environment())) {
        fighter = new(__DIR__"fighter");
        fighter->move(environment());
        message_vision("$N说道：让我找个人先陪您练练？\n", ao);
        message_vision("$N一招手，一个$n走了过来。\n", ao, fighter);
    } else if (fighter)
        message_vision("$N道：咦？不知那"+weapon_unit+weapon_name+"被谁拿去了！\n", ao);
    else {
        respect = RANK_D->query_respect(who);
        message_vision("$N连忙起身说道："+respect+"稍侯，待我想想？\n", ao,who);
        message_vision("我这龙宫中有"+weapon_unit+weapon_name+"还凑合着能使，"+respect+"若不嫌弃，就送与"+respect+"用吧！\n", who);
        who->set_temp("dntg/donghai", trying);
        call_out("fight_quest", 2, trying);
    }
    return 1;
}

void fight_quest(string trying)
{
    object ao = query("ao");
    object who = query("owner");
    object fighter, weapon;
    string weapon_name, weapon_unit;

    if (trying == "try_dao")
        { weapon_name="大砍刀"; weapon = new(__DIR__"dakandao"); weapon_unit="柄"; }
    else if (trying == "try_cha")
        { weapon_name="九股叉"; weapon = new(__DIR__"jiugucha"); weapon_unit="支"; }
    else if (trying == "try_chui")
        { weapon_name="梅花锤"; weapon = new(__DIR__"meihuachui"); weapon_unit="对"; }
    else if (trying == "try_ji")
        { weapon_name="画杆戟"; weapon = new(__DIR__"huaganji"); weapon_unit="柄"; }
    else
        return;

    fighter = new(__DIR__"fighter");
    fighter->move(environment());
    weapon->move(environment());
    message_vision("$N一招手，一个$n抬过一"+weapon_unit+weapon_name+"。\n", ao, fighter);
    message_vision("$N说道：＂要不要和我的手下先练练？＂\n", ao);
}

void sendto_maze()
{
    object ao = query("ao");
    object who = query("owner");
    if (!ao || !who) {
        call_out("destruct_me", 1);
        return;
    }

    message_vision("$N说道："+RANK_D->query_respect(who)+"武功盖世，可到后面的海藏中试一试定海神针铁。\n",ao,who);
    call_out("send_maze", 3);
}

void send_maze()
{
    object ao = query("ao");
    object who = query("owner");

    if (!ao || !who) {
        call_out("destruct_me", 1);
        return;
    }

    message_vision("说着，$N把$n送到了一个地方。\n", ao, who);
    who->move(__DIR__"maze/hdmg");
    ao->move(__DIR__"maze/hdmg");
    message_vision("$N一拱手道："+RANK_D->query_respect(who)+"向前走即可看到那神铁，恕老夫不奉陪了。\n", ao, who);
    message_vision("说罢，$N转身回宫了。\n", ao);
    ao->move(environment());
    call_out("make_shentie", 1);
}

void make_shentie()
{
    object shentie, room;

    room = find_object(__DIR__"maze/mazeend");
    if (!room) load_object(__DIR__"maze/mazeend");
    if (room = find_object(__DIR__"maze/mazeend")) {
        if (!(shentie = present("shen tie", room))) {
            shentie = new(__DIR__"shentie");
            shentie->move(room);
        }
    }
    call_out("destruct_me", 1);
}

void remove()
{
    object ao = query("ao");
    if (ao && ao->query_temp("wire-puller") == this_object()) {
        ao->delete("inquiry/weapon");
        ao->delete("inquiry/bingqi");
        ao->delete("inquiry/兵器");
    }
}

void destruct_me()
{
    destruct(this_object());
}
