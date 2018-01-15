// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997


inherit NPC;
inherit F_VENDOR;

void create()
{
  set_name("钱寡妇", ({"qian guafu", "qian", "guafu", "fu"}));
  set("gender", "女性");
  set("combat_exp", 5000);
  set("age", 30);
  set("per", 21);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 30);
  set("vendor_goods", ([
    "kuang" : "/d/obj/misc/kuang",
    "shaozhou" : "/d/obj/misc/shaoba",
    "bag" : "/d/obj/misc/bag",
  ]));
  setup();
  carry_object("/d/qujing/qinfa/obj/dao");
  carry_object("/d/obj/cloth/skirt")->wear();
}

void init ()
{
  ::init();
  add_action ("do_vendor_list", "list");
}
