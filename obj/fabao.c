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
    add_action("do_seal", "seal");
    add_action("do_unseal", "unseal");
}

int do_seal(string arg)
{
    if (query("series_no") != "1") return 0;
    if (query("equipped"))
        return notify_fail("你必须放下法宝才能封印。\n");
    if (query("seal"))
        return notify_fail("法宝已经被封印了。\n");
    set("seal", 1);
    set("short", short() + CYN + "『封印中』" + NOR);
    set("weapon_prop/damage", 1);
    tell_object(this_player(), this_object()->name() + "上泛起了一层淡淡的光，那种毁灭的气息消失了。\n");
    save();
    return 1;
}

int do_unseal(string arg)
{
    int damage = 10;
    int stars = query("stars/damage");
    int upgraded = query("upgraded/damage");
    if (query("series_no") != "1") return 0;
    if (query("equipped"))
        return notify_fail("你必须放下法宝才能解除封印。\n");
    if (!query("seal"))
        return notify_fail("法宝没有被封印了。\n");
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
    return 1;
}