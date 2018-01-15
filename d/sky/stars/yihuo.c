
//翼火星官
inherit NPC;

void create()
{
    int gd,sk;
    gd=random(2);
    sk=random(10);

    set_name("翼火星官", ({ "xing guan", "huan", "star" }));
    set("long", @LONG
二十八位星官之一，正在殿中四处巡游。
LONG);
    set("title", "星宿");

    if (gd==1) set("gender", "男性");
    else set("gender", "女性");
    set("age", 60);
    set("class", "taoist");
    set("attitude", "friendly");
    set("per", random(20) + 10);
    set("max_kee", 600);
    set("max_gin", 200);
    set("max_sen", 600);
    set("force", 1500);
    set("max_force", 1500);
    set("force_factor", 60);
    set("mana", 1500);
    set("max_mana", 1500);
    set("mana_factor", 60);
    set("combat_exp", 800000);

    set("env/no_teach", 1);

    set("eff_dx", 800000);
    set("nkgain", 800);

    switch (sk) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    default :
    }
    setup();

    if (gd==0) carry_object("/d/obj/cloth/nichang")->wear();
    else carry_object("/d/obj/cloth/jinpao")->wear();

    carry_object("/d/obj/armor/tiejia")->wear();
    switch (sk) {
    case 0:
        carry_object("/d/obj/weapon/sword/changjian")->wield();
        break;
    case 1:
        carry_object("/d/obj/weapon/sword/changjian")->wield();
        break;
    case 2:
        carry_object("/d/obj/weapon/stick/bintiegun")->wield();
        break;
    case 3:
        carry_object("/d/obj/weapon/spear/changqiang")->wield();
        break;
    case 4:
        carry_object("/d/obj/weapon/sword/changjian")->wield();
        break;
    case 5:
        carry_object("/d/obj/weapon/fork/gangcha")->wield();
        break;
    case 6:
        carry_object("/d/obj/weapon/axe/huafu")->wield();
        break;
    case 7:
        carry_object("/d/obj/weapon/staff/chanzhang")->wield();
        break;
    case 8:
        carry_object("/d/obj/weapon/sword/changjian")->wield();
        break;
    default :
        carry_object("/d/obj/weapon/fork/gangcha")->wield();
    }
}
