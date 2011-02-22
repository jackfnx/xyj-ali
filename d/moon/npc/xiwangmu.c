// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//xiwangmu.c
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("西王母", ({"xi wangmu", "xi", "wangmu","master"}));
        set("long", @LONG

一个充满成熟女人韵味的女子，被狰狞的锁链死死的锁住，悬挂在空中。

她的身体上挂满了淫具：她的乳峰上是一对欲火钳，恶毒的钳制着她的乳蒂，
不时放射出闪电，她的乳峰中不由自主的喷射出一道道乳汁，被淫具收集在了
一个容器里；她的下体中是一根震荡按摩棒，疯狂的在她的玉门里肆虐，淫器
上布满了狰狞的蠕动着的突起，带给她强大的刺激，让她的阴精疯狂的喷射，
同样被淫具收集到了一个容器里。。。

这个女子所遭受的淫刑让你深深震撼，但是更让你震撼的是这个女子体内隐隐
透出的可怕力量。

LONG);
        set("title", "被擒的");
        set("gender", "女性");
        set("age", 30);
        set("class","xian");
        set("attitude", "friendly");
        set("cor", 30);
        set("per", 30);
        set("looking", "神色困顿，无精打采。");
        set("max_kee", 4500);
        set("max_gin", 800);
        set("max_sen", 4500);
        set("force", 4000);
        set("max_force", 2000);
        set("force_factor", 125);
        set("max_mana", 2000);
        set("mana", 4000);
        set("mana_factor", 100);
        set("combat_exp", 2000000);
        set_skill("literate", 150);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("force", 180);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("spells", 180);
        set_skill("moonshentong", 180);
        set_skill("baihua-zhang", 180);
        set_skill("moonforce", 180);
        set_skill("snowsword", 200);
        set_skill("moondance", 150);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");
        set("inquiry", ([
            "name": "我。。。我就是月宫祖师西王母。。。",
            "here": "本座也不知这是哪里啊。。。",
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "arrow" :),
        }) );

        create_family("月宫", 1, "红");
        setup();
}

void attempt_apprentice(object ob)
{
   if ( !((string)ob->query("gender")=="女性")){
      command("shake");
          command("say 我们月宫只收女徒，这位" + RANK_D->query_respect(ob) + "还是另请高就吧。\n");
      return;
   }

   if ( (string)ob->query("family/family_name")=="月宫") {
   if (((int)ob->query("combat_exp") < 100000 )) {
   command("say " + RANK_D->query_respect(ob) +
"的道行不够高深，有些绝学秘法恐怕难以领悟。\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们月宫发扬光大。\n");
       command("recruit " + ob->query("id") );
   return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"还是先去学些基础功夫吧。\n");
        return;
}
int accept_fight(object me)
{
   return 0;
}
