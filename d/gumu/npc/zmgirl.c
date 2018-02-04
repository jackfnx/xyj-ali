// ALi by NewX

inherit NPC;

void create()
{
    set_name("手淫女", ({"girl", "nv"}));
    set ("long", @LONG
一个赤裸的少女，凹凸有致的身材，娇媚迷人的面貌，正在旁若无人
的手淫。
LONG);

    set("gender", "女性");
    set("age", 15+random(20));
    set("per", 20+random(15));
    set("combat_exp", 10000);
    set_skill("dodge", 10);
    set_skill("moondance", 20);
    set("max_gin", 200);
    set("max_atman", 200);
    set("chat_chance", 5+random(40));
    set("chat_msg", ({
        "手淫女的双手抚上了胸前的双峰，鲜红的乳头娇艳欲滴，在玉手的爱抚下越发变得膨胀...\n",
        "手淫女的手指插入了自己的花穴，只见纤纤的玉指在娇艳的花瓣中进进出出，带出了闪闪发光的蜜汁，更是倍显淫靡...\n",
        "手淫女在自己的爱抚之下，欲火高升，不断发出了动人的娇吟，眼看就要达到快感的巅峰。\n",
        "手淫女尖叫一声，浑身剧烈的颤抖，花穴中喷出了一股闪亮的阴精，竟然已经达到了高潮。\n"
        }) );

    setup();
}
