// ALI by NewX

// fabao smelter

#include <ansi.h>
#include <weapon.h>
#include <armor.h>

inherit ITEM;

void confirm_recycle(string arg, object ob, object fabao_ob);
void pay(object me, object ob);
void get_new_desc(object ob, string arg);

int is_container() { return 1; }

void create()
{
    set_name("法宝炼制炉", ({"fabao smelter", "smelter", "lzl"}));
    set_weight(1000);
    set_max_encumbrance(100000);
    seteuid(getuid());
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "座");
        set("long", @LONG
一座小巧的熔炉，隐隐透出神秘的力量。
上面刻满了字，全都是关于炼制法宝的法门。

                  (** 法宝炼制指南 **)
  炼制新法宝               make_fabao                         
  炼化(销毁)法宝           recycle                            
  查看法宝炼制/升级费用    cost                               
  升级                     upgrade <prop>                     
  五行强化                 enhance                            
                                                              
  给法宝改代号             change_id <fabao_id> <new id>      
  给法宝改名               change_name <fabao_id> <new name>  
  给法宝改描述             change_desc <fabao_id> <new desc>  
  给法宝改单位名称         change_unit <fabao_id> <new unit>  
  封印威能（武器专用）     seal <fabao_id>                    
  解开封印（武器专用）     unseal <fabao_id>                  
LONG);
        set("material", "bronze");
        set("value", 1000000);
        set("no_sell", 1);
    }

    setup();
}

void set_owner(object who)
{
    set_temp("owner", who);
    who->set_temp("smelter", this_object());
    set("name", "『" + who->name(1) + "』的法宝炼制炉");
}

void reset()
{
    object owner = query_temp("owner");
    object env = environment();
    if (!env || !owner) {
        destruct(this_object());
        return;
    }
    if (env != owner && env != environment(owner)) {
        tell_room(env, name() + "忽然化作一道长虹飞向了远方。\n");
        destruct(this_object());
        return;
    }
}

void init()
{
    add_action("do_make", "make_fabao");
    add_action("do_recycle", "recycle");
    add_action("do_cost", "cost");
    add_action("do_upgrade", "upgrade");
    add_action("do_enhance", "enhance");
    add_action("do_change_name", "change_name");
    add_action("do_change_id", "change_id");
    add_action("do_change_desc", "change_desc");
    add_action("do_change_unit", "change_unit");
    add_action("do_seal", "seal");
    add_action("do_unseal", "unseal");
}

int do_make()
{
    if (!FABAO_D->varify_formula("", this_object()))
        return 0;
    if (!FABAO_D->varify_player("", this_player(), this_object()))
        return 0;
    
    FABAO_D->start_make_fabao(this_player(), this_object());
    return 1;   
}

void complete_make_fabao(object ob)
{
    string fabao_type;
    object fabao_ob;
    
    fabao_ob = FABAO_D->new_fabao_ob(ob);
    if (!fabao_ob) {
        write("法宝对象创建失败。\n");
        return;
    }

    fabao_ob->setup();

    ob->set("fabao/" + ob->query_temp("fabao_new"),
        fabao_ob->query("series_no"));

    pay(ob, fabao_ob);

    if (!fabao_ob->move(this_object()))
        if (!fabao_ob->move(ob))
            fabao_ob->move(environment(ob));

    fabao_ob->save();
    ob->save();
    
    tell_room(environment(ob), HIY "天空中忽然涌起一团祥云，隐约中似有仙乐传来，仔细一看，原来是"
            + ob->name() + "炼制出了一" + fabao_ob->query("unit") + fabao_ob->query("name") + HIY "。\n" NOR, ob);
    tell_object(ob, HIY "天空中忽然涌起一团祥云，隐约中似有仙乐传来，你炼制出了一"
            + fabao_ob->query("unit") + fabao_ob->query("name") + HIY "。\n" NOR);
}

int do_recycle()
{
    object me = this_player();
    object fabao_ob = first_inventory();
    
    if (!objectp(fabao_ob))
        return notify_fail("请先放入法宝，再输入销毁指令。\n");
    if (objectp(next_inventory(fabao_ob)))
        return notify_fail("请只放入法宝，不要放入其他物品。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no"))
        return notify_fail("这不是法宝耶！\n");

    printf("%s\n%s", fabao_ob->short(), fabao_ob->long());
    printf("------------------------------------------------\n");
    printf("%s其中所蕴含的力量：%s(如果炼化它可以得到其中的75%%)\n%s", YEL, HIR, NOR);
    printf("%s内力： %s%d%s\t", YEL, HIG, fabao_ob->query("power/force"), NOR);
    printf("%s法力： %s%d%s\t", YEL, HIG, fabao_ob->query("power/mana"), NOR);
    printf("%s道行： %s%s%s\n", YEL, HIG, COMBAT_D->chinese_daoxing(fabao_ob->query("power/exp")), NOR);
    write("你确定要炼化这件法宝吗？(y/n)");
    input_to( (: confirm_recycle, me, fabao_ob :) );
    return 1;
}

void confirm_recycle(object ob, object fabao_ob, string arg)
{
    int i, series, moving = 0;
    string type;
    
    if (arg != "y" && arg != "Y") {
        write("OK, 那就算了。\n");
        return;
    }
    
    type = fabao_ob->query("fabao_type");
    for (i = 1; series = ob->query("fabao/" + type + i); i++) {
        if (fabao_ob->query("series_no") == series) {
            //seteuid(getuid(ob));
            //rm( fabao_ob->query_save_file() + __SAVE_EXTENSION__ );
            ob->add("max_force", fabao_ob->query("power/force"));
            ob->add("max_mana", fabao_ob->query("power/mana"));
            ob->add("combat_exp", fabao_ob->query("power/exp"));
            ob->delete("fabao/" + type + i);
            moving = 1;
        }
        else if (moving) {
            ob->set("fabao/" + type + (i - 1), ob->query("fabao/" + type + i));
            ob->delete("fabao/" + type + i);
        }
    }
    ob->save();
    tell_room(environment(ob), "天色突然一暗，隐约中似乎传来鬼神的哭泣，原来竟是"
        + ob->name() + "炼化了" + fabao_ob->name() + "，吸收了其中能量，实力大增。\n", ({ ob }));
    printf("你炼化了%s，获得了%d点内力，%d点法力，%s道行。\n",
        fabao_ob->name(),
        fabao_ob->query("power/force"),
        fabao_ob->query("power/mana"),
        COMBAT_D->chinese_daoxing(fabao_ob->query("power/exp")));
    destruct(fabao_ob);
}

int do_cost(string arg)
{
    object fabao_ob, me = this_player();
    
    foreach (object ob in all_inventory()) {
        if (ob->query("owner_id") && ob->query("series_no")) {
            if (objectp(fabao_ob))
                return notify_fail("你到底想查看哪一件法宝的升级花费。\n");
            fabao_ob = ob;
        }
    }
    
    FABAO_D->show_upgrade_cost(fabao_ob, me);
    return 1;
}

int do_upgrade(string arg)
{
    object me = this_player(), ob = this_object(), fabao_ob;
    int   upgraded;
    
    if (!arg || arg == "")
        return notify_fail("请把法宝放入炼制炉内，用 upgrade <特性> 来升级，升级特性可用cost查看。\n");

    if (!FABAO_D->varify_formula(arg, ob))
        return 0;
    
    if (!FABAO_D->varify_player(arg, me, ob))
        return 0;
    
    fabao_ob = ob->query_temp("fabao_ob");
    
    pay(me, fabao_ob);
    
    upgraded = fabao_ob->add("upgraded/" + arg, 1);
    if (upgraded == 5) {
        fabao_ob->add("stars/" + arg, 1);
        fabao_ob->set("upgraded/" + arg, 0);
    }
    tell_room(environment(ob), HIY + name() + HIY "上忽然升起了一缕缕青烟，其中的"
        + fabao_ob->name() + HIY "散发出强大的气息。\n" NOR, me);
    tell_object(me, HIG "法宝炼制炉上突然传来阵阵的吸力，将你体内的力量强行抽取了一部分，让你不禁阵阵眩晕。。。\n"
        "不过你并没有惊慌，反而感觉很兴奋。\n"
        "因为你清楚的感觉到炉中的" + fabao_ob->name() + HIG "其『"
        + query_temp("upgraded_prop") + HIG "(" + arg +")』明显增强了\n" NOR);
    
    fabao_ob->setup();
    fabao_ob->save();
    me->save(); 

    return 1;
}

int do_enhance()
{
    object me = this_player(), ob = this_object(), fabao_ob;
    string fabao_type, elem_type, elem_name;
    int elem_point;

    if (!FABAO_D->varify_formula("enhance", ob))
        return 0;
    
    if (!FABAO_D->varify_player("enhance", me, ob))
        return 0;
    
    fabao_ob = ob->query_temp("fabao_ob");
    fabao_type = fabao_ob->query("fabao_type");
    
    pay(me, fabao_ob);
    
    elem_type = query_temp("enhance/type");
    elem_point = query_temp("enhance/point");
    elem_name = query_temp("enhance/name");
    
    fabao_ob->add(fabao_type + "_prop/" + elem_type, elem_point);
    tell_room(environment(ob), HIY + name() + HIY "上忽然升起了一缕缕青烟，其中的"
        + fabao_ob->name() + HIY "散发出强大的气息。\n" NOR, me);
    tell_object(me, HIG "法宝炼制炉上忽然升起了一缕缕青烟，其中的材料渐渐融入" + fabao_ob->name() + HIG "中。\n"
        "你清楚的感觉到" + fabao_ob->name() + HIG "的『" + elem_name + HIG "』属性明显增强了。\n" NOR);
    
    fabao_ob->setup();
    fabao_ob->save();
    me->save(); 
    
    return 1;
}

void pay(object me, object ob)
{
    mapping my_costs;
    
    if (mapp(my_costs = me->query_temp("fabaod"))) {
        foreach (string prop in keys(my_costs)) {
            me->add(prop, -(int)my_costs[prop]);
            ob->add("power/" + prop, (int)my_costs[prop]);
        }
    }
    me->delete_temp("fabaod");
    
    foreach (object m in all_inventory())
        if (m != ob) {
            message_vision(name() + "升起一缕缕青烟，其中的" + m->name() + "融化了。\n\n", me);
            destruct(m);
        }
}

int do_change_id(string arg)
{
    string name, newname;
    object fabao_ob, me = this_player();
    string *id_list, *t_list;
    
    if (!arg || arg == "") 
        return notify_fail("请用 change_id 法宝 新英文名 来改名。\n");
    if (sscanf(arg, "%s %s", name, newname) != 2)
        return notify_fail("请用 change_id 法宝 新英文名 来改名。\n");
    if (!objectp(fabao_ob = present(name, me)))
        return notify_fail("你身上没有这样东西啊。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
        return notify_fail("那个不是法宝耶！\n");
    if (fabao_ob->query("equipped"))
        return notify_fail("你必须放下法宝才能改名。\n");
    if (!LOGIN_D->check_legal_id(newname, 20, 1)) return 1;
    
    newname = replace_string(newname, " ", "_"); 
    fabao_ob->set("id", newname);
    
    id_list = ({ newname });
    t_list = explode(newname, "_");
    if (sizeof(t_list) > 1) {
        id_list += t_list;
    }
    fabao_ob->set_name(fabao_ob->query("name"), id_list); 
    fabao_ob->save();
    
    write("改动成功。\n");
    return 1;
}

int do_change_name(string arg)
{
    string id, newname;
    object fabao_ob, me = this_player();
    
    if (!arg || arg == "") 
        return notify_fail("请用 change_name 法宝 新中文名 来改名。\n");
    if (sscanf(arg, "%s %s", id, newname) != 2)
        return notify_fail("请用 change_name 法宝 新中文名 来改名。\n");
    if (!objectp(fabao_ob = present(id, me)))
        return notify_fail("你身上没有这样东西啊。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
        return notify_fail("那个不是法宝耶！\n");
    if (fabao_ob->query("equipped"))
        return notify_fail("你必须放下法宝才能改名。\n");
    
    newname += "$NOR$";
    arg = newname;

    arg = replace_string(arg, "$BLK$", "");
    arg = replace_string(arg, "$RED$", "");
    arg = replace_string(arg, "$GRN$", "");
    arg = replace_string(arg, "$YEL$", "");
    arg = replace_string(arg, "$BLU$", "");
    arg = replace_string(arg, "$MAG$", "");
    arg = replace_string(arg, "$CYN$", "");
    arg = replace_string(arg, "$WHT$", "");
    arg = replace_string(arg, "$HIR$", "");
    arg = replace_string(arg, "$HIG$", "");
    arg = replace_string(arg, "$HIY$", "");
    arg = replace_string(arg, "$HIB$", "");
    arg = replace_string(arg, "$HIM$", "");
    arg = replace_string(arg, "$HIC$", "");
    arg = replace_string(arg, "$HIW$", "");
    arg = replace_string(arg, "$NOR$", "");
    
    if (!LOGIN_D->check_legal_name(arg, 12)) return 1; 
    
    arg = newname;
    
    arg = replace_string(arg, "$BLK$", BLK);
    arg = replace_string(arg, "$RED$", RED);
    arg = replace_string(arg, "$GRN$", GRN);
    arg = replace_string(arg, "$YEL$", YEL);
    arg = replace_string(arg, "$BLU$", BLU);
    arg = replace_string(arg, "$MAG$", MAG);
    arg = replace_string(arg, "$CYN$", CYN);
    arg = replace_string(arg, "$WHT$", WHT);
    arg = replace_string(arg, "$HIR$", HIR);
    arg = replace_string(arg, "$HIG$", HIG);
    arg = replace_string(arg, "$HIY$", HIY);
    arg = replace_string(arg, "$HIB$", HIB);
    arg = replace_string(arg, "$HIM$", HIM);
    arg = replace_string(arg, "$HIC$", HIC);
    arg = replace_string(arg, "$HIW$", HIW);
    arg = replace_string(arg, "$NOR$", NOR);
    
    fabao_ob->set("name", arg);
    fabao_ob->save();     
    
    write("改动成功。\n");
    return 1;
}

int do_change_desc(string arg)
{
    string id, desc;
    object fabao_ob, me = this_player();
    
    if (!arg || arg == "") 
        return notify_fail("请用 change_desc 法宝 新描述 来修改描述。\n");
    if (sscanf(arg, "%s %s", id, desc) != 2)
        return notify_fail("请用 change_desc 法宝 新描述 来修改描述。\n");
    if (!objectp(fabao_ob = present(id, me)))
        return notify_fail("你身上没有这样东西啊。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
        return notify_fail("那个不是法宝耶！\n");
    if (fabao_ob->query("equipped"))
        return notify_fail("你必须放下法宝才能改名。\n");
    
    fabao_ob->set("long", desc);
    fabao_ob->save();
    
    write("改动成功。\n");
}

int do_change_unit(string arg)
{
    string name, newname;
    object fabao_ob, me = this_player();
    
    if (!arg || arg == "") 
        return notify_fail("请用 change_unit 法宝 单位 来指定法宝单位。\n");
    if (sscanf(arg, "%s %s", name, newname) != 2)
        return notify_fail("请用 change_unit 法宝 单位 来指定法宝单位。\n");
    if (!objectp(fabao_ob = present(name, me)))
        return notify_fail("你身上没有这样东西啊。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
        return notify_fail("那个不是法宝耶！\n");
    if (fabao_ob->query("equipped"))
        return notify_fail("你必须放下法宝才能改名。\n");
    
    if (!LOGIN_D->check_legal_name(newname, 2)) return 1;
    
    fabao_ob->set("unit", newname);
    fabao_ob->save();
    
    write("改动成功。\n");
    return 1;
}

int do_seal(string arg)
{
    int equipped = 0;
    object fabao_ob, me = this_player();
    
    if (!arg || arg == "") 
        return notify_fail("你要封印哪一件法宝？\n");
    if (!objectp(fabao_ob = present(arg, me)))
        return notify_fail("你身上没有这样东西啊。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no"))
        return notify_fail("那个不是法宝耶！\n");
    if (fabao_ob->query("fabao_type") != "weapon")
        return notify_fail("这件法宝不能封印。\n");
    if (fabao_ob->query("seal"))
        return notify_fail("这件法宝已经被封印了。\n");

    if (equipped = fabao_ob->query("equipped"))
        fabao_ob->unequip();
    fabao_ob->set("seal", 1);
    FABAO_D->build_weapon(fabao_ob);
    message_vision("$N照着" + name() + "上的文字念了一段咒语。\n顿时，"
            + fabao_ob->name() + "上泛起了一层淡淡的光，那种毁灭的气息消失了。\n",
        me);
    fabao_ob->save();
    if (equipped)
        fabao_ob->wield();
    return 1;
}

int do_unseal(string arg)
{
    int equipped = 0;
    object fabao_ob, me = this_player();
    
    if (!arg || arg == "") 
        return notify_fail("你要封印哪一件法宝？\n");
    if (!objectp(fabao_ob = present(arg, me)))
        return notify_fail("你身上没有这样东西啊。\n");
    if (!fabao_ob->query("owner_id") || !fabao_ob->query("series_no"))
        return notify_fail("这件物品不是法宝。\n");
    if (fabao_ob->query("fabao_type") != "weapon")
        return notify_fail("这件法宝不能封印。\n");
    if (!fabao_ob->query("seal"))
        return notify_fail("这件法宝没有被封印啊。\n");

    if (equipped = fabao_ob->query("equipped"))
        fabao_ob->unequip();
    fabao_ob->delete("seal");
    FABAO_D->build_weapon(fabao_ob);
    message_vision("$N照着" + name() + "上的文字念了一段咒语。\n顿时，"
            + fabao_ob->name() + "上放射出耀眼的光芒，一股毁灭的气息扑面而来。\n",
        me);
    fabao_ob->save();
    if (equipped)
        fabao_ob->wield();
    return 1;
}
