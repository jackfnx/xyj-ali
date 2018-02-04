// ALi by NewX

inherit NPC;

void create()
{
    set_name("行刑弟子", ({"dizi", "girl"}));
    set("long", @LONG
一个穿着紧身皮衣的少女，凹凸有致的身材，娇媚迷人的面貌。
不过最醒目的还是胯下正固定着一根高高挺立的双头龙，双头龙表面狰狞粗糙，似乎还会跳动。
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
        "行刑弟子挥舞着皮鞭抽打在囚犯身上，皮鞭刁钻的落在乳头、阴蒂这些最敏感、最脆弱的部位，打得囚犯惨叫连连，再也硬气不起来。\n",
        "行刑弟子的欲望渐渐高涨，顾不得行刑，一挺胯下的双头龙，狠狠的插入了囚犯的御道，将囚犯插得淫水横飞，嗯嗯啊啊的淫叫。\n",
        "囚犯被行刑弟子插得意识模糊，浑身颤抖，下体冒出了粘稠的液体。行刑弟子大喜，急忙把嘴巴贴近，将液体舔入嘴里，脸上露出了陶醉的表情。\n"
        }) );

    setup();
}
