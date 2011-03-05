// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// fabao.c

#include <weapon.h>
#include <armor.h>
#include <ansi.h>

inherit EQUIP;
inherit F_SAVE;
inherit F_BACKUP;

void create()
{
   seteuid(0);   
   set_name("自制法宝物件", ({ "fabao object", "fabao", "object" }) );
   setup();
}

void reset()
{
    if( !environment() ||  //mon 2/4/98
        query("owner_id") != getuid(environment()) )  {
        destruct(this_object());
        return;
    }
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
   string id, series;

   id = query("owner_id");
   series = query("series_no");
   if( !id || !series) return 0;

   return sprintf(DATA_DIR "fabao/%c/%s-%s", id[0], id, series);
}

int save()
{
   if( query("equipped") )   {
     write("必须放下法宝才能储存。\n");
     return 0;
   }
   return ::save();
}

void setup()
{
   ::setup();
}

int query_unique()  { return 1; }

int init()
{
    if (query("series_no") == "1") {
        add_action("do_seal", "seal");
        add_action("do_unseal", "unseal");
    }
}

int do_seal(string arg)
{
    int equipped = 0;
    
    if (!id(arg)) return 0;
    if (query("series_no") != "1") return 0;
    if (query("seal"))
        return notify_fail("法宝已经被封印了。\n");
    if (equipped = query("equipped"))
        unequip();
    set("seal", 1);
    set("short", short() + CYN + "『封印中』" + NOR);
    set("weapon_prop/damage", 1);
    tell_object(this_player(), this_object()->name() + "上泛起了一层淡淡的光，那种毁灭的气息消失了。\n");
    save();
    if (equipped)
        wield();
    return 1;
}

int do_unseal(string arg)
{
    int damage = 10;
    int stars = query("stars/damage");
    int upgraded = query("upgraded/damage");
    int equipped = 0;
    
    if (!id(arg)) return 0;
    if (query("series_no") != "1") return 0;
    if (!query("seal"))
        return notify_fail("法宝没有被封印啊。\n");
    if (equipped = query("equipped"))
        unequip();
    delete("seal");
    delete("short");
    switch (stars) {
        case 1:
            damage += 4 * upgraded;
            break;
        case 2:
            damage += 4 * 5;
            damage += 6 * upgraded;
            break;
        case 3:
            damage += 4 * 5;
            damage += 6 * (upgraded + 5);
            break;
        case 4:
            damage += 4 * 5;
            damage += 6 * (upgraded + 10);
            break;
        case 5:
            damage += 4 * 5;
            damage += 6 * 15;
            break;
        default:
            break;
        }
    set("weapon_prop/damage", damage);
    tell_object(this_player(), this_object()->name() + "上放射出耀眼的光芒，一股毁灭的气息扑面而来。\n");
    save();
    if (equipped)
        wield();
    return 1;
}

string extra_long()
{
    string str = "\n自制法宝等级：\n";
    int series_no, damage_stars, force_stars, i;
    int dodge_stars, armor_stars, vs_force_stars, spells_stars, vs_spells_stars;
    
    if (query("series_no") == "1")  {
        damage_stars = query("stars/damage");
        force_stars = query("stars/force");
        str += "    " + HIG + "伤害力        " + HIR;
        for(i=0; i<damage_stars; i++)
            str += "★";
        for(i=damage_stars; i<5; i++)
            str += "　";
        str +="    " + HIC + "内功攻击力    " + HIR;
        for(i=0; i<force_stars; i++)
            str += "★";
        str += NOR + "\n";
    }
    else {
        dodge_stars = query("stars/dodge");
        armor_stars = query("stars/armor");
        vs_force_stars = query("stars/armor_vs_force");
        spells_stars = query("stars/spells");
        vs_spells_stars = query("stars/armor_vs_spells");
        str += "    " + HIY + "防御力        " + HIR;
        for(i=0; i<dodge_stars; i++)
            str += "★";
        for(i=dodge_stars; i<5; i++)
            str += "　";
        str += "    " + HIB + "抵抗力        " + HIR;
        for(i=0; i<armor_stars; i++)
            str += "★";
        str += "\n"; 
        str += "    " + HIM + "内功抵抗力    " + HIR;
        for(i=0; i<vs_force_stars; i++)
            str += "★";
        for(i=vs_force_stars; i<5; i++)
            str += "　";
        str += "    " + HIC + "魔法攻击力    " + HIR;
        for(i=0; i<spells_stars; i++)
            str += "★";
        str += "\n"; 
        str += "    " + HIW + "魔法抵抗力    " + HIR;
        for(i=0; i<vs_spells_stars; i++)
            str += "★";
        str += NOR + "\n";
    }
    
    return str;
}