// Éñ»°ÊÀ½ç¡¤Î÷ÓÎ¼Ç¡¤°æ±¾£´£®£µ£°
/* <SecCrypt CPL V3R05> */
 
// sun.c

#include <ansi.h>

int exert(object me, object target)
{
    if (!target
        || !userp(target)
        || target->is_corpse()
        || target==me)
        return notify_fail("ÄãÏëÌæË­½â³ıÊ´ÔÂÖä£¿\n");
    if (!target->query_condition("moon_poison"))
        return notify_fail("Ã»ÖĞÊ´ÔÂÖäÏ¹½ÁºÍÊ²Ã´£!\n");
    if (me->is_fighting() || target->is_fighting())
        return notify_fail("Õ½¶·ÖĞÎŞ·¨ÔË¹¦ÁÆÉË£¡\n");
    if ((int)me->query("force") - (int)me->query("max_force") <  600)
        return notify_fail("ÄãµÄÕæÆø²»¹»¡£\n");
    if ((int)me->query_skill("moonforce",1) < 120)
        return notify_fail("ÄãµÄÄÚ¹¦ĞŞÎª²»×ãÒÔÌæÈË½â³ıÊ´ÔÂÖä¡£\n");
    message_vision(
        HIY "$N×øÁËÏÂÀ´Ä¬Ä¬µÄÄîÆğ¾­À´£¬$nÌı$NÓïÒôÇå´à£¬Ô½ÄîÔ½ÊÇ³åºÍ°²¾²£¬È«ÉíÒşÒş·¢³öÊ¥½àµÄ¹â»Ô¡£\n\n"NOR,
        me, target );
    if (random(me->query_skill("moonforce", 1)-100)>10) {
        target->apply_condition("moon_poison",0);
        message_vision(
            HIY "$NËĞ¾­µÄÉùÒôÔ½À´Ô½ÈáºÍ£¬$nĞÄÖĞ¼È¸Ğ¼¤£¬ÓÖ°²Î¿£¬ÔÚÄÇÎÂÈáò¯³ÏµÄÄî¾­ÉùÖĞÈëÁËË¯Ïç¡£\n"NOR,
            me, target);
        target->set_temp("force_sleep",1);
        target->command_function("sleep");
        target->delete_temp("force_sleep");
    }
    else {
        message_vision(
        HIY "$NÍ»È»Á³É«²Ô°×£¬ËÆºõÌåÁ¦²»Ö§£¬¾¹Å»³öÒ»¿ÚÑªÀ´¡­¡­\n"NOR,
        me, target );
    }

    target->receive_cuiring("kee", 10 + (int)me->query_skill("force")/3);
    me->add("force", -150);
    me->set("force_factor", 0);
    return 1;
}

int help(object me)
{
    write(@HELP
¡¾Ó³ÈÕÖä¡¿
°ïÖú±ğÈË½â³ı¡ºÊ´ÔÂÖä¡»

¡¼Ö¸Áî¡½    exert sun
HELP);
    return 1;
}
