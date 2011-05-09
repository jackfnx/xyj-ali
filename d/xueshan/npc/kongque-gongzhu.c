// kongque-gongzhu.c...weiqi, 97.09.15.

inherit NPC;

string get_ice(object me);
void do_drop(object ob);

void create()
{
    set_name("孔雀公主", ({"kongque gongzhu", "kongque", "gongzhu"}));
    set("title", "明王护法");
    set("gender", "女性" );
    set("age", 23);
    set("per", 21);

    set("long", "孔雀公主乃孔雀明王的女儿。孔雀明王被佛祖如来押至灵山后，\n"
        "她由大鹏明王一手带大。说是侄女，与大鹏明王实则有父女之情。\n");
    set("class", "yaomo");
    set("combat_exp", 800000);
    set("attitude", "peaceful");
    create_family("大雪山", 3, "弟子");
    set_skill("unarmed", 70);
    set_skill("pressheart-hand", 70);
    set_skill("dodge", 90);
    set_skill("peripateticism", 120);
    set_skill("parry", 70);
    set_skill("throwing", 100);
    set_skill("sword", 90);
    set_skill("avian-sword", 120);
    set_skill("force", 90);
    set_skill("iceblood-force", 90);
    set_skill("literate", 90);
    set_skill("spells", 80);
    set_skill("dengxian-dafa", 90);
    map_skill("spells", "dengxian-dafa");
    map_skill("force", "iceblood-force");
    map_skill("unarmed", "pressheart-hand");
    map_skill("sword", "avian-sword");
    map_skill("dodge", "peripateticism");

    set("max_kee", 1000);
    set("max_sen", 600);
    set("force", 1600);
    set("max_force", 800);
    set("mana", 1000);
    set("max_mana", 500);
    set("force_factor", 60);
    set("mana_factor", 25);

    set("eff_dx", -200000);
    set("nkgain", 400);

    setup();
    carry_object("/d/obj/cloth/nihong-yuyi")->wear();
    carry_object("/d/obj/cloth/shoes")->wear();
    carry_object("/d/obj/weapon/sword/fenghuang-qin")->wield();
}

void attempt_apprentice(object ob)
{
    if ((string)ob->query("family/family_name") == "大雪山") {
        if ((int)ob->query("family/generation") < 3) {
            command("say 不敢，不敢。我该拜" + RANK_D->query_respect(ob) + "您为师才是。\n");
        } else if ((int)ob->query("family/generation") == 3) {
            command("say 你这个" + RANK_D->query_respect(ob) + "就别来消遣小女子了！\n");
        } else {
            if ((int)ob->query("combat_exp") >= 50000) {
                command(":) ");
                command("say 好，" + RANK_D->query_respect(ob) + "既然看得起小女子，小女子定然用心传授！\n");
                command("recruit " + ob->query("id") );
            } else {
                command("say 这位" + RANK_D->query_respect(ob) + "，你还是找鹦鹉，乌鸦他们先练着吧。\n");
            }
        }
    } else {
        command("hmm ");
        command("say 这位" + RANK_D->query_respect(ob) + "，你还是找鹦鹉，乌鸦他们先练练吧。\n");
    }

    return;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "yaomo");
}

void init()
{
    object ob, me;

    me = this_player();

    ::init();

    set("chat_chance", 10);
    set("inquiry", ([
        "name" : "不告诉你。\n",
        "here" : "你还没完了...别在这儿打搅！\n", 
        "大鹏王" : (: get_ice :),
        "大鹏明王" : (: get_ice :),
        "二叔" : (: get_ice :),
    ]) );

    set("chat_msg", ({
        "孔雀公主叹了口气。\n",   
        "孔雀公主自言自语道：也不知道二叔的病什么时候能好。\n",
        "孔雀公主皱了皱眉道：按说这种草性暖，二叔怎么会认为可以提炼寒毒呢？\n",
        "孔雀公主又叹了口气：做了这么久还不成，肯定还差点什么...这么多花草混来混去也没用呀？\n",
        "孔雀公主自言自语道：二叔再弄不到寒毒，恐怕大事不妙了。\n",        
    }));

    if ((string)me->query("gender") == "男性" && (int)me->query("per") > 25 && random(3) > 1) {
        remove_call_out("greeting");
        call_out("greeting", 1, me);
    }

}

void greeting(object me)
{
    if (!me || environment(me) != environment()) return;

    switch (random(1)) {
        case 0:
            //command("look " + me->query("id"));
            //command("blush ");
            break;
    }
}

string get_ice(object me)
{
    object env;

    me = this_player();
    env = environment(this_object());

    if (me->query_temp("ice_given") && (string)env->query("short") == "小木屋" && (string)me->query("family/family_name") == "大雪山") {
        me->delete_temp("ice_given");
        command("whisper " + me->query("id") + " 既然你想见他，这就让你去。\n");
        message_vision("只见孔雀公主伸手在桌子底下按了一按。\n", me);
        env->open_down();
        return "上来时敲一敲墙即可。\n";
    } else {
        return "大鹏明王就是我二叔，我二叔就是大鹏明王。\n";
    }
}

int accept_object(object me, object ob)
{
    if ((string)ob->query("id") != "lan bingkuai"
    &&  (string)ob->query("id") != "shuangse bing") {
        command("say 这位" + RANK_D->query_respect(me) + "就别给小女子捣乱了。");
        command("sigh ");
        //command("drop " + ob->query("id"));
        //this does not work due to time problem...
        //have to use call_out().
        call_out("do_drop", 1, ob);
        return 1;
    } else {
        command("ah ");
        command("jump ");
        command("say 这位" + RANK_D->query_respect(me) + "真是有心人！");
        command("whisper " + me->query("id") + " 那我告诉你一个大秘密：\n    我二叔现在根本就不在冰宫里。他病得很厉害，正需要这种寒毒。");
        me->set_temp("ice_given", 1);
        return 1;
    }
}

void do_drop(object ob)
{
    command("drop "+ob->query("id"));
}
