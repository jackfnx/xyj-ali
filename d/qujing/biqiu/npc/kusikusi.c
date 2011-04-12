// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit NPC;
inherit F_VENDOR;

void create()
{
  set_name("库司库司", ({"kusi kusi", "kusi", "boss"}));
  set("gender", "男性");
  set("combat_exp", 5000);
  set("age", 30);
  set("per", 21);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 30);
  set("vendor_goods", ([
        "tangmian": "/d/qujing/biqiu/obj/tangmian",
        "niutang": "/d/qujing/biqiu/obj/niutang",
      ]) );

  setup();
  carry_object("/d/obj/cloth/choupao")->wear();
}

void init()
{
  ::init();
  add_action("do_vendor_list", "list");
}
