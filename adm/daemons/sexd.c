// ALI by NewX

#include <ansi.h>

string *penis_names = ({ "肉棒", "阳根", "肉杵", "分身", "龙根", "淫枪", "龙枪", "淫兽" });
string *pussy_names = ({ "玉门", "肉蚌", "玉蛤", "密道", "肉蟹", "花房", "花径", "花穴", "肉穴", "淫穴", "蜜壶" });
string *ass_names = ({ "菊花", "菊穴", "菊肛", "肛菊", "臀尻", "雪臀", "玉臀" });
string *finger_names = ({ "手指", "玉指" });
string *breast_names = ({ "乳房", "玉乳", "酥乳", "娇乳", "乳峰", "豪乳", "爆乳", "乳头", "乳蒂" });
string *sensitive_names_m = ({ "耳垂", "乳头" });
string *sensitive_names_f = ({ "耳垂", "唇瓣", "玉颈", "玉背", "皓腕", "肚脐", "纤腰", "玉腿", "香踝", "玉足" });

string male_status_msg(int ratio)
{
   if (ratio == 0) return HIG "目色清明，毫无欲望的色彩。" NOR;
   if (ratio < 10) return HIG "目色迷离，气息有些散乱。" NOR;
   if (ratio < 20) return HIY "呼吸有些粗重，体温微微有些升高。" NOR;
   if (ratio < 40) return HIY "满脸通红，气喘如牛。" NOR;
   if (ratio < 60) return HIR "满身大汗，如同水里捞出来的一样。" NOR;
   if (ratio < 80) return HIR "已经完全堕入了欲望的深渊，意识有些不清了。" NOR;
   if (ratio < 90) return RED "浑身温度高得吓人，身体下意识的挺动着，喉咙深处隐隐传出声声咆哮。" NOR;
   return RED "已经进入无意识状态，下意识的作出迎合动作，呼吸都快要停止了。" NOR;
}

string female_status_msg(int ratio)
{
   if (ratio == 0) return HIG "目色清明，毫无欲望的色彩。" NOR;
   if (ratio < 10) return HIG "目色迷离，气息有些散乱。" NOR;
   if (ratio < 20) return HIY "呼吸有些粗重，体温微微有些升高。" NOR;
   if (ratio < 40) return HIY "两颊绯红，呻吟娇喘，吐气如兰。" NOR;
   if (ratio < 60) return HIR "香汗淋漓，意识有些模糊。" NOR;
   if (ratio < 80) return HIR "已经完全迷乱在了欲望的深渊，不由自主的挺动着腰肢。" NOR;
   if (ratio < 90) return RED "浑身温度高得吓人，身体下意识的挺动着，口中呼喊着无意义的言语。" NOR;
   return RED "已经进入无意识状态，下意识的作出迎合动作，樱唇虽然翕动着却已经无法发出任何声音。" NOR;
}

void report_sex_status(object ob)
{
    if (ob->query("gender") == "女性")
        message_vision("( $N" + female_status_msg((int)ob->query("lust")) + " )\n",
            ob);
    else
        message_vision("( $N" + male_status_msg((int)ob->query("lust")) + " )\n",
            ob);
}

void announce(object ob, string event)
{
    object makelover = ob->query_temp("sex/makelove_ob");
    object fucker = ob->query_temp("sex/fuck_ob");
    switch (event) {
        case "erect":
            message_vision(HIR "\n$N的" + penis_names[random(sizeof(penis_names))] + "倔强的挺立了起来！\n\n" NOR, ob);
            break;
        case "wet":
            message_vision(HIR "\n一股蜜汁从$N的" + pussy_names[random(sizeof(pussy_names))] + "中喷涌而出，$P显然已经动情！\n\n" NOR, ob);
            break;
        case "no_erect":
            message_vision(HIC "\n随着欲火逐渐消退，$N的" + penis_names[random(sizeof(penis_names))] + "也逐渐恢复了常态！\n\n" NOR, ob);
            break;
        case "no_wet":
            message_vision(HIC "\n随着欲火逐渐消退，$N也逐渐恢复了常态！\n\n" NOR, ob);
            break;
        case "ejaculate":
            if (!objectp(fucker)) {
                message_vision(HIR "\n$N的" + penis_names[random(sizeof(penis_names))] + "中射出了一道真阳！\n\n" NOR, ob);
            } else {
                tell_object(fucker, "\n" + HIR + ob->name() + "射精了，强大的冲击力猛烈的冲击着你的花心！\n\n" NOR);
            }
            break;
        case "orgasm":
            tell_room(environment(ob), HIR "\n" + ob->name() + "的浑身剧烈的颤抖，口中发出无意义的尖叫，肌肤上盛开起一道道绯红的花斑...\n她已经达到了快感的巅峰！\n\n" NOR, ({ob}));
            if (objectp(fucker)) {
                tell_object(fucker, HIR + "你感到" + ob->name() + "的" + pussy_names[random(sizeof(pussy_names))] + "一阵阵剧烈的收缩，一股阴精从花房中喷涌而出，正好淋在你的"+penis_names[random(sizeof(penis_names))]+"上！\n\b" NOR);
            }
            break;
    }
}

void gain_enjoy(object ob, string event)
{
    switch (event) {
        case "ejaculate":
            break;
        case "orgasm":
            break;
    }
}

object get_attacker(object me, object ob)
{
    if (me->query("gender") == ob->query("gender")) {
        if (ob->query_temp("sex_initiative") > me->query_temp("sex_initiative")) {
            return ob;
        } else {
            return me;
        }
    } else {
        if (me->query("gender") == "男性") {
            return me;
        } else {
            return ob;
        }
    }
}

object get_sufferer(object me, object ob)
{
    if (me->query("gender") == ob->query("gender")) {
        if (me->query("sex_initiative") >= ob->query("sex_initiative")) {
            return ob;
        } else {
            return me;
        }
    } else {
        if (me->query("gender") == "男性") {
            return ob;
        } else {
            return me;
        }
    }
}

void push_penis(object me, object ob)
{
    object attacker, sufferer, penis_ob;
    string penis, pussy;

    attacker = get_attacker(me, ob);
    sufferer = get_sufferer(me, ob);

    if (attacker->query("gender") == "男性") {
            penis = penis_names[random(sizeof(penis_names))];;
    } else {
        penis_ob = attacker->query_temp("penis");
        if (objectp(penis_ob)) {
            penis = penis_ob->name();
        } else {
            penis = finger_names[random(sizeof(finger_names))];
        }
    }

    if (sufferer->query("gender") == "女性") {
        pussy = pussy_names[random(sizeof(pussy_names))];
    } else {
        pussy = ass_names[random(sizeof(ass_names))];
    }

    attacker->set_temp("sex/fuck_ob", sufferer);
    sufferer->set_temp("sex/fuck_ob", attacker);
    attacker->fuck_ob(sufferer);
    sufferer->fuck_ob(attacker);
    if (attacker->add_temp("no_move", -1) <= 0) attacker->delete_temp("no_move");
    if (sufferer->add_temp("no_move", -1) <= 0) sufferer->delete_temp("no_move");
    tell_object(attacker, HIR + "\n\n你的"+penis+"已经插入了"+sufferer->name()+"的"+pussy+"！！！\n" + NOR);
    tell_object(sufferer, HIR + "\n\n" + attacker->name() +"的"+penis+"已经插入了你的"+pussy+"！！！\n" + NOR);
}

void pull_penis(object me, object ob)
{
    object attacker, sufferer, penis_ob;
    string penis, pussy;

    if ( me->query_temp("sufferer") == ob
       || ob->query_temp("attacker") == me ) {
        attacker = me;
        sufferer = ob;
    } else if ( me->query_temp("attacker") == ob
            || ob->query_temp("sufferer") == me ) {
        attacker = ob;
        sufferer = me;
    } else
        return;

    if (attacker->query("gender") == "男性") {
            penis = penis_names[random(sizeof(penis_names))];;
    } else {
        penis_ob = attacker->query_temp("penis");
        if (objectp(penis_ob)) {
            penis = penis_ob->name();
        } else {
            penis = finger_names[random(sizeof(finger_names))];
        }
    }

    if (sufferer->query("gender") == "女性") {
        pussy = pussy_names[random(sizeof(pussy_names))];
    } else {
        pussy = ass_names[random(sizeof(ass_names))];
    }

    attacker->delete_temp("sex/fuck_ob");
    sufferer->delete_temp("sex/fuck_ob");
    tell_object(attacker, HIB + "\n\n你将"+penis+"拔出了"+sufferer->name()+"的"+pussy+"！！！\n" + NOR);
    tell_object(sufferer, HIB + "\n\n" + attacker->name() +"将"+penis+"拔出了你的"+pussy+"！！！\n" + NOR);
}

int is_fucking(object ob1, object ob2)
{
    return ob1->query_temp("sex/fuck_ob") == ob2 &&  ob2->query_temp("sex/fuck_ob") == ob1;
}

int do_makelove(object me, object victim, int is_fucking)
{
    mapping action;
    string actionstr, effectstr, sens;
    int me_ap, victim_ap, me_dp, victim_dp, hit, back;

    if (is_fucking) {
        if (!is_fucking(me, victim)) {
            push_penis(me, victim);
            return 0;
        }
        action = me->query("fuck_actions");
    }
    else {
        if (me->query_temp("sex_heat")
        &&  victim->query_temp("sex_heat")
        &&  !is_fucking(me, victim)
        &&  random(2) == 1) {
            push_penis(me, victim);
            return 0;
        }
        action = me->query("sex_actions");
    }
        
    if (victim->query("gender")=="女性") {
        switch (random(4)) {
            case 0:
                sens = pussy_names[random(sizeof(pussy_names))];
                break;
            case 1:
                sens = ass_names[random(sizeof(ass_names))];
                break;
            case 2:
                sens = breast_names[random(sizeof(breast_names))];
                break;
            case 3:
                sens = sensitive_names_f[random(sizeof(sensitive_names_f))];
                break;
            default:
                sens = pussy_names[random(sizeof(pussy_names))];
                break;
        }
    } else {
        switch (random(2)) {
            case 0:
                sens = penis_names[random(sizeof(penis_names))];
                break;
            case 1:
                sens = sensitive_names_m[random(sizeof(sensitive_names_m))];
                break;
            default:
                sens = penis_names[random(sizeof(penis_names))];
                break;
        }
    }

    actionstr = action["action"];
    actionstr = replace_string(actionstr, "$s", sens);
    actionstr = replace_string(actionstr, "$L", penis_names[random(sizeof(penis_names))]);
    actionstr = replace_string(actionstr, "$l", pussy_names[random(sizeof(pussy_names))]);
    actionstr = replace_string(actionstr, "$b", breast_names[random(sizeof(breast_names))]);

    me_ap = me->query_per();
    victim_ap = victim->query_per();
    me_dp = me->query_cps();
    victim_dp = victim->query_cps();
    hit = me_ap > random(victim_dp * 3 / 4);
    back = me_dp < random((victim_dp + victim_ap) * 1 / 2);
    if (!hit)
        effectstr = "弄得$n浑身一颤，急忙深吸一口气，总算没有失控";
    else {
        if (undefinedp(action["effect"]))
            effectstr = "弄得$n浑身一颤，似乎已经意乱情迷";
        else
            effectstr = action["effect"];
    }

    message_vision("\n" + actionstr + "！\n", me, victim);
    message_vision("结果" + effectstr + "！\n", me, victim);
    if (hit) {
        report_sex_status(victim);
        victim->sex_excite("lust", action["enjoy"]);
    }
    if (back) {
        if (hit)
            message_vision("而$N也觉得精神一震，一种满足感油然而生！\n", me);
        else
            message_vision("反而是$N觉得心中一荡，一种满足感油然而生！\n", me);
        report_sex_status(me);
        me->sex_excite("lust", action["self_enjoy"]);
    }

    //me->add("atman", -action["cost"]);

    if (me->query("lust")>=100)
        me->orgasm();

    if (victim->query("lust")>=100)
        victim->orgasm();

    return action["damage"];
}

void makelove(object me, object victim)
{
    if (me->query_temp("sex/fuck_ob") == victim) {
        do_makelove(me, victim, 1);
    } else {
        do_makelove(me, victim, 0);
    }
}

