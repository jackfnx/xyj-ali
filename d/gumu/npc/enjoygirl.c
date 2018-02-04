// ALi by NewX

#include <ansi.h>

inherit NPC;

void create()
{
    set_name("古墓弟子", ({"dizi", "girl"}));
    set("title", MAG "正在享乐的" NOR);
    set("long", @LONG
一个赤裸的少女，凹凸有致的身材，娇媚迷人的面貌。
LONG);

    set("gender", "女性");
    set("age", 15+random(20));
    set("per", 20+random(15));
    set("combat_exp", 10000);
    set_skill("dodge", 10);
    set_skill("moondance", 20);
    set("max_gin", 200);
    set("max_atman", 200);
    set("chat_chance", 25+random(40));
    set("chat_msg", ({
        "古墓弟子骑在精奴的身上，忘情的耸动，双手狠狠地抓住自己的乳房，拼命的揉搓着...\n",
        "古墓弟子猛地上半身向后一仰，一对巨大的乳房甩向天空，不知是乳汁、汗水还是淫汁的液体像天上撒去，空气中弥漫着一股古怪的气味。\n",
        "古墓弟子发出一声尖叫，螓首猛地向上一样，蹲着的两条双腿猛地往两边一分，将男女性器结合的部位完全暴露出来。\n",
        "古墓弟子浑身剧烈颤抖，一股带着泡沫的液体，顺着两人性器结合的缝隙喷涌出体外，难道这是潮吹？\n",
        "精奴突然发出一声低吼，下体的肉棒连连跳动，不一会精疲力尽的瘫软下来。得到阳精的古墓弟子却不肯浪费一点时间，马上捂着下体扑向下一个精奴。\n"
        }) );

    setup();
}
