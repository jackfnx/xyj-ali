// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit NPC;
inherit F_VENDOR;

void create()
{
  set_name("拉苏律司", ({"lasu lusi", "lusi", "boss"}));
  set("gender", "男性");
  set("combat_exp", 5000);
  set("age", 40);
  set("per", 44);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 60);
  set("vendor_goods", ([
        "jiezhi": "/d/qujing/biqiu/obj/ring",
        "xiangquan": "/d/qujing/biqiu/obj/neck",
        "wanlian": "/d/qujing/biqiu/obj/wrists",
      ]) );

  setup();
  carry_object("/d/obj/cloth/choupao")->wear();
}

void init()
{
  ::init();
  add_action("do_vendor_list", "list");
}
