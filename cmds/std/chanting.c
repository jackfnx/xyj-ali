// xiudao.c

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

void finish(object me, int exp_gain);

int main(object me, string arg)
{
    int busy_time, exp_gain;
    int xiudao_lvl;
    mapping fam;
    object where;

    seteuid(getuid());
    where = environment(me);

    if (where->query("no_fight") || where->query("no_magic"))
            return notify_fail("安全区内禁止练功。\n");

//    if (!where->query("jingzuo_room"))
//        return notify_fail("此处不宜静坐修练！\n");

    if ((xiudao_lvl = me->query_skill("spells")) < 20)
        return notify_fail("你法术修为太低，不能行功修炼！\n");
    if (me->is_busy() || me->query_temp("pending/exercising"))
        return notify_fail("你现在正忙着呢。\n");
    if (me->is_fighting())
        return notify_fail("战斗中修道，找死啊？！\n");
    if ((int)me->query("sen") * 100 / (int)me->query("max_sen") < 50)
        return notify_fail("你现在神智不清，再炼恐怕要走火入魔！\n");
    if ((int)me->query("kee") * 100 / (int)me->query("max_kee") < 50)
        return notify_fail("你现在体力不够，再练就要累死了！\n");

    exp_gain = xiudao_lvl/20 + random(3);
    busy_time = random(7200)/exp_gain/100;
    exp_gain = 1 + random(exp_gain*2);
    busy_time *= exp_gain;
    exp_gain = OBSTACLES_D->xiudao_accelerate(me, exp_gain);
    if (me->query("food") + me->query("water") < 20) busy_time *= 2;
    message_vision(HIY "$N闭上眼睛，盘膝坐下，嘴里默默念念不知在说些什么。\n" NOR, me);
    me->start_busy(busy_time);
    call_out("finish", busy_time, me, exp_gain);
    return 1;
}

void finish(object me, int exp_gain)
{
    string *msg = ({
        "多欲为苦，生死疲劳，从贪欲起；少欲无为，身心自在。",
        "懈怠坠落，常行精进，破烦恼恶，摧伏四魔，出阴界狱。",
        "愚痴生死，菩萨常念，广学多闻，增长智慧，成就辩才，教化一切，悉以大乐。",
        "贫苦多怨，横结恶缘，菩萨布施，等念怨亲，不念旧恶，不憎恶人。",
        "生死炽燃，苦恼无量，发大乘心，普济一切。",
        "愿代众生，受无量苦，令诸众生，毕竟大乐。",
        "愿以此功德，庄严佛净土，上报四重恩，下济三途苦。",
        "若有见闻者，悉发菩提心，常行菩萨道，广度诸有情。",
    });
    if (me->query("class") != "bonze") msg = ({
        "道可道，非常道；名可名，非常名。",
        "无名，天地之始；有名，万物之母。",
        "天下皆知美之为美，斯恶已；皆知善之为善，斯不善已。",
        "天地不仁，以万物为刍狗；圣人不仁，以百姓为刍狗。",
        "谷神不死，是谓玄牝，玄牝之门，是谓天地根。绵绵若存，用之不勤。",
        "大道废，有仁义；智慧出，有大伪；六亲不和，有孝慈；国家昏乱，有忠臣。",
        "知人者智，自知者明，胜人者有力，自胜者强，知足者富，强行者有志，不失其所者久，死而不亡者寿。",
        "道常无为而无不为。候王若能守之，万物将自化。",
    });
    message_vision(HIY "$N轻声念道："+msg[random(sizeof(msg))]+"\n" NOR, me);
    message_vision(HIY "$N缓缓睁开眼睛，长舒一口气站了起来。\n" NOR, me);

    tell_object(me, HIC "你的道行增加了" + chinese_number(exp_gain*3) + "时辰！\n" NOR);
    me->add("combat_exp", exp_gain);

    if (me->query("food") >= exp_gain) me->add("food",-exp_gain);
    else me->set("food", 0);

    if (me->query("water") >= exp_gain) me->add("water",-exp_gain);
    else me->set("water", 0);

    me->receive_damage("sen", me->query("int"));
    me->receive_damage("kee", me->query("int"));
    me->improve_skill("spells", random(exp_gain));

    me->start_busy(1);
}

int help(object me)
{
    write(@HELP
指令格式 : chanting

诵经修炼以提高道行。
HELP
    );
    return 1;
}
