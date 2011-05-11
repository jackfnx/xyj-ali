//created 5-20-97 pickle
 
inherit NPC;

void create()
{
    set_name("尉迟恭", ({"yuchi gong", "yuchi", "gong", "yuchigong", "jingde", "yuchi jingde", "yuchijingde", "master", "shifu"}));
    set("long", @LONG
尉迟恭，字敬德，乃是唐太宗手下猛将。排为隋唐时第
十二条好汉。起初他是反王刘武州殿前元帅，后因兵败
降唐。他惯使一条点钢枪，且喜使一对雌雄竹节钢鞭。
LONG);

    set("title", "开国元勋");
    set("gender", "男性");
    set("age", 43);
    set("str", 45);
    set("per", 15);
    set("int", 20);
    set("cor", 50);
    set("cps", 40);
    set("combat_exp", 1400000);
    set_skill("spear", 120);
    set_skill("force", 150);
    set_skill("dodge", 150);
    set_skill("parry", 120);
    set_skill("mace", 180);
    set_skill("jinglei-mace", 150);
    set_skill("yanxing-steps", 120);
    set_skill("bawang-qiang", 100);
    set_skill("lengquan-force", 150);
    set_skill("unarmed", 120);
    set_skill("changquan", 100);
    map_skill("mace", "jinglei-mace");
    map_skill("force", "lengquan-force");
    map_skill("unarmed", "changquan");
    map_skill("spear", "bawang-qiang");
    map_skill("parry", "jinglei-mace");
    map_skill("dodge", "yanxing-steps");
    set("max_sen", 1500);
    set("max_kee", 4000);
    set("force", 1000);
    set("max_force", 2500);
    set("force_factor", 100);

    create_family("将军府", 2, "蓝");
    setup();

    carry_object("/d/obj/weapon/spear/gangqiang");
    carry_object("/d/obj/weapon/mace/malemace")->wield();
    carry_object("/d/obj/armor/tiejia")->wear();
}
 
int accept_fight(object me)
{
    command("say 老夫手重，若是伤人反而不美了。\n");
    return 0;
}

void attempt_apprentice(object me)
{
    string myname = RANK_D->query_rude(me);
    int effstr = (int)(me->query("str")+me->query_skill("unarmed",1)/10-2);

    if (effstr < 20 || (int)me->query_con() < 25) {
        command("say 这"+myname+"手无缚鸡之力，不配作我徒弟！");
        return;
    }
    if ((int)me->query("cps") < 20 && (int)me->query_cor() < 20) {
        command("say 这"+myname+"胆子还不如只老鼠！");
        return;
    }
    command("say 要想拜我为师，倒也不难。只需将建成元吉那两个小兔崽子给我捉过来，让我揍一顿就行！\n");
    return;
}

int accept_object(object me, object ob)
{
    string myname = RANK_D->query_rude(me);
    string obname = ob->query("id");
    int kar = me->query_kar(), diff;

    if (!ob->is_character()
    ||  userp(ob)
    ||  (obname != "li jiancheng" && obname != "li yuanji")) {
        command ("say 这是什么破烂？");
        return 0;
    }
    me->add_temp("yuchg/give " + obname, 1);
    
    if (me->query_temp("yuchg/give li jiancheng") && me->query_temp("yuchg/give li yuanji")) {
        command("hehe");
        command("say 这帮仙人还真是坏，特意将这两个小兔崽子复活，放到我们对面，让我们打了解闷。");
        command("say 有趣，有趣。");
        command("say 就是那个罗成有点无趣，明明当初是被这两个小兔崽子弄死的，如今复活了也不来找他们的麻烦，真是搞不懂。");
        if (me->query_temp("pending/apprentice") == this_object()) {
            command("look " + me->query("id"));
            command("nod");
            command("say "+myname+"果然有两下子，老夫就收下你吧！");
            command("recruit " + me->query("id"));
        } else if (!me->query("family")) {
            command("look " + me->query("id"));
            command("nod");
            command("say "+myname+"，我看你骨骼清奇，是个练武的奇才，不如当我的徒弟吧。");
            command("recruit " + me->query("id"));
        } else if (me->is_apprentice_of(this_object())) {
            command("recruit " + me->query("id"));
        } else {
            command("look " + me->query("id"));
            command("nod");
            command("say 可惜！"+myname+"你已经有了师门，否则老夫定要收你为徒。");
            command("whisper "+ me->query("id") +"好处也不会短你的，我在长安那座麒麟阁里藏了一本秘籍，"+myname+"若是有兴趣，不妨去找找。");
        }
        me->delete_temp("yuchg");
    } else {
        command("say 好！好！好！");
        command("say 还有一个，把那个也弄来，自然有你的好处。");
    }
    
    call_out("destroy", 1, ob);
    return 1;
}

int recruit_apprentice(object ob)
{
    if (::recruit_apprentice(ob))
        ob->set("class", "fighter");
}

void destroy(object ob)
{
    if (ob) destruct(ob);
}
