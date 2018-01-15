// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat 12/8/1997


inherit NPC;
inherit F_VENDOR;

void create()
{
  set_name("福嫂", ({"fu sao", "sao", "fu"}));
  set("gender", "女性");
  set("combat_exp", 2000);
  set("age", 30);
  set("per", 30);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 30);
  set("vendor_goods", ([
        "guazi": "/d/qujing/tianzhu/obj/guazi",
        "chaodou": "/d/qujing/tianzhu/obj/chaodou",
        "dangao": "/d/qujing/tianzhu/obj/dangao",
        "jiansu": "/d/qujing/tianzhu/obj/jiansu",
      ]) );

  setup();
  carry_object("/d/qujing/tianzhu/obj/huaqun")->wear();
  carry_object("/d/qujing/tianzhu/obj/yunxue")->wear();
}

void init()
{
  ::init();
  add_action("do_vendor_list", "list");
}

