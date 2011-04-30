
#include <ansi.h>

#define NAME "ยํิชหง"
#define ID "ma yuanshuai"

inherit NPC;

void create()
{
    set_name(NAME, ({ ID }));
    set("gender", "ฤะะิ");
    set("age", 23);
    set("long", "าปึปด๓ยํบ๏กฃ\n");
    set("combat_exp", 1000000);

    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("dragonstep", 120);
    map_skill("dodge", "dragonstep");
    set("force", 900);
    set("max_force", 900);
    set("force_factor", 10);

    setup();
}

void announce_success(object who)
{
    int dx = 3000 + random(500);
    object panzi;

    who->add("dntg/number",1);
    who->set("dntg/huaguo", "done");
    who->add("combat_exp", dx);
    command("chat "+who->query("name")+"ีถมหฐิีผฮารวหฎมฑถดตฤฤงอทฃฌหณภ๛ดณนýด๓ฤึฬ์นฌตฺาปนุฃก");
    command("chat ดำดหฦ฿สฎถþถดพซม้ฝิำฆื๐"+who->query("name")+"ฮชอ๕ฃฌหๆสฑฬýบ๒ต๗วฒฃก");
    tell_object(who, "ฤใำฎตรมห"+ COMBAT_D->chinese_daoxing(dx) +"ตฤตภะะฃก\n");

    panzi = new(__DIR__"shipan");
    panzi->move(who);
    message_vision(HIY NAME+"ตใอทนþัüตฤถิ$NหตตฝฃบีโสวฮารวึฺะึตÜตฤาปตใถ๙ะกาโหผฃฌฒปณษพดาโกฃ\n" NOR,who);
    tell_object(who, "ยํิชหงธ๘ฤใาปธ๖สฏอทลฬืำกฃ\n");
    who->save();
}

void refuse_player(object who)
{
    string name;
    name = who->name();

    message_vision(HIY NAME+"อปศปลÜมหนýภด$Nากากอทฃบฮารวีýิฺักบ๏อ๕ฃฌรปสยฑ๐ภดตทยากฃ\n" NOR,who);
    message_vision(HIY "หตฐี"+NAME+"ผฑดาดาตฤภ๋ฟชมหกฃ\n" NOR,who);
}

ÿÿ
