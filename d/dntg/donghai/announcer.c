// sgzl
#include <ansi.h>
#define NAME "°½¹ã"
#define ID "ao guang"

inherit NPC;

void create()
{
    set_name(NAME, ({ ID }));
    set("gender", "ÄÐÐÔ");
    set("age", 53);
    set("long", "Ò»ÌõÀÏÄàöú¡£\n");
    
    setup();
}

void announce_success(object who)
{
    int dx = random(500) + 3000;
    object hb = who->query_temp("dntg_helper");

    who->add("dntg/number", 1);
    who->set("dntg/donghai", "done");
    who->add("combat_exp", dx);
    command("chat "+who->query("name")+"Äã¾¹¸ÒÄÃ×ßÎÒÁú¹¬µÄ¶¨º£ÉñÕëÌú£¬¿´ÎÒ²»È¥ÓñµÛÃæÇ°¸æÄã£¡");
    tell_object(who,"ÄãÓ®µÃÁË"+ COMBAT_D->chinese_daoxing(dx) +"µÄµÀÐÐ£¡\n");
    who->save();
    if (hb) hb->report_progress(10);
}

ÿÿ
