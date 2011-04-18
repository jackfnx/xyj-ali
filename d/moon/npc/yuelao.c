// ALi by NewX

// yuelao.c 月下老人

inherit NPC;

void create()
{
   set_name("月下老人", ({ "yuexia laoren", "yuelao", "laoren" }));
   set("long", 
"他就是专管天上地下姻缘的月下老人了。
他满脸红光，须眉皆白，正坐在那儿翻看一本书，
手上黏着一根红绳，口中正自言自语着些什么。\n");
   set("gender", "男性");
   set("age", 101);
   set("attitude", "friendly");
   set("str", 30);
   set("int", 30);
   set("con", 30);
   set("per", 25);
      
   set("max_kee", 1200);
   set("max_gin", 1000);
   set("max_sen", 1200);
   set("force", 1000);
   set("max_force", 1000);
   set("force_factor", 50);
   set("max_mana", 1200);
   set("mana", 1200);
   set("combat_exp", 500000);

   set_skill("force", 100);
   set_skill("dodge", 100);
   set_skill("unarmed", 100);
   set_skill("parry", 100);
   set_skill("literate", 150);

   set("inquiry", ([
     "name" : "区区乃是月老。",
     "here" : "这儿？这儿就是这儿啊。反正这里不是我办公的地方，所以要结婚也别在这说，我没法帮你办。",
	 "rumors" : "消息？哪有什么消息？有谣传说我被玉皇大帝解职了，这可绝对是谣传啊，绝对的！",
//     "news" :,
     "结婚" : "想结婚？好啊，找我啊。不过在这不行，这不是我办公的地。",
     "登记" : "想结婚？好啊，找我啊。不过在这不行，这不是我办公的地。",
     "离婚" : "想离婚？好啊，找我啊。不过在这不行，这不是我办公的地。",
     "做媒" : "想做媒？好啊，找我啊。不过在这不行，这不是我办公的地。",
	 "办公地点" : "这个你得自己找。你们如果有缘分，相信一定能找到。",
	 "办公的地" : "这个你得自己找。你们如果有缘分，相信一定能找到。"
       ]) );

   setup();
}
