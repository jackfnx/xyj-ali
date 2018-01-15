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
    set_name("自制法宝物件", ({ "fabao object", "fabao", "object" }));
}

void reset()
{
    if (!environment() ||  //mon 2/4/98
        query("owner_id") != getuid(environment()) )  {
        destruct(this_object());
        return;
    }
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
    string id;
    int series;

    id = query("owner_id");
    series = query("series_no");
    if (!id || !series) return 0;

    return sprintf(DATA_DIR "fabao/%c/%s-%d", id[0], id, series);
}

int save()
{
    if (query("equipped"))   {
        write("必须放下法宝才能储存。\n");
        return 0;
    }
    return ::save();
}

void setup()
{
    string *id_list, *t_list, id = query("id");
    
    ::setup();
    
    seteuid(getuid());
    set_weight(1000);
    
    id_list = ({ query("id") });
    t_list = explode(query("id"), "_");
    if (sizeof(t_list) > 1) {
        id_list += t_list;
    }
    set_name(query("name"), id_list);
    
    switch (query("fabao_type")) {
        case "weapon":
            FABAO_D->build_weapon(this_object());
            break;
        case "armor":
            FABAO_D->build_armor(this_object());
            break;
        default:
            CHANNEL_D->do_channel(this_object(), "sys", name() + ": unknown fabao_type\n");
            break;
    }
}

int query_unique()  { return 1; }

string extra_long()
{
    return "\n自制法宝等级：\n"
        + FABAO_D->show_fabao_status(this_object());
}