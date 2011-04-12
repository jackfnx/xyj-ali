// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat 12/8/1997


inherit NPC;
inherit F_VENDOR;

void create()
{
  set_name("黄汤", ({"huang tang", "huang", "tang"}));
  set("gender", "男性");
  set("combat_exp", 90000);
  set("age", 38);
  set("per", 21);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 40);
  set_skill("dodge", 40);
  set_skill("parry", 40);
  set("vendor_goods", ([
        "jiuhu": "/d/qujing/tianzhu/obj/jiuhu",
        "jiuguan": "/d/qujing/tianzhu/obj/jiuguan",
        "jiuzhong": "/d/qujing/tianzhu/obj/jiuzhong",
      ]) );

  setup();
  carry_object("/d/qujing/tianzhu/obj/baipao")->wear();
}

void init()
{
  ::init();
  add_action("do_vendor_list", "list");
}

