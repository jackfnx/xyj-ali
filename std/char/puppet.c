inherit NPC;
inherit F_SAVE;

int save_record(object me, object ob)
{
    object *inv;
    mapping hp_status, skill_status, map_status;
    string *skillnames, *mapnames;
    int i, weapon_cnt, armor_cnt;

    reset_eval_cost();
    hp_status = ob->query_entire_dbase();

    me->set("str", hp_status["str"]);
    me->set("per", hp_status["per"]);
    me->set("int", hp_status["int"]);
    me->set("age", hp_status["age"]);

    me->set("max_gin",     hp_status["max_gin"]);
    me->set("eff_gin",     hp_status["eff_gin"]);
    me->set("gin",     hp_status["gin"]);
    me->set("max_kee",     hp_status["max_kee"]);
    me->set("eff_kee",     hp_status["eff_kee"]);
    me->set("kee",     hp_status["kee"]);
    me->set("max_sen",     hp_status["max_sen"]);
    me->set("eff_sen",     hp_status["eff_sen"]);
    me->set("sen",     hp_status["sen"]);
    me->set("max_force",   hp_status["max_force"]);
    me->set("force",       hp_status["force"]);
    me->set("max_mana",    hp_status["max_mana"]);
    me->set("mana",    hp_status["mana"]);
    me->set("gender",      hp_status["gender"]);
    me->set("combat_exp",  hp_status["combat_exp"]);

    me->set("eff_gin", me->query("max_gin"));
    me->set("gin",     me->query("max_gin"));
    me->set("eff_kee", me->query("max_kee"));
    me->set("kee",     me->query("max_kee"));
    me->set("eff_sen", me->query("max_sen"));
    me->set("sen",     me->query("max_sen"));
    me->set("force",   me->query("max_force")*2);
    me->set("mana",    me->query("max_mana")*2);

    skill_status = me->query_skills();
    if (mapp(skill_status))
    {
        skillnames = keys(skill_status);

        for (i=0; i<sizeof(skillnames); i++)
        {
            me->delete_skill(skillnames[i]);
        }
    }

    skill_status = ob->query_skills();
    if (mapp(skill_status))
    {
        skillnames = keys(skill_status);

        for (i=0; i<sizeof(skillnames); i++)
        {
            me->set_skill(skillnames[i], skill_status[skillnames[i]]);
        }
    }

    me->set("force_factor", me->query_skill("force")*3/4);

    reset_eval_cost();
    if (!me->query("new_player"))
    {
        me->save();
        reset_eval_cost();
        return 1;
    }

    me->set("new_player", 0);

    if (mapp(map_status = me->query_skill_map()))
    {
        mapnames = keys(map_status);

        for (i=0; i<sizeof(mapnames); i++)
        {
            me->map_skill(mapnames[i]);
        }
    }

    map_status = ob->query_skill_map();
    if (mapp(map_status))
    {
        mapnames = keys(map_status);

        for (i=0; i<sizeof(mapnames); i++)
        {
            me->map_skill(mapnames[i], map_status[mapnames[i]]);
        }
    }
  
    inv = all_inventory(me);
    for (i=0; i<sizeof(inv); i++)
    {
        destruct(inv[i]);
    }

    // save once here, an external bug might stop the following
    me->setup();
    me->save();

    weapon_cnt = 0;
    armor_cnt = 0;
    inv = all_inventory(ob);
    for (i=0; i<sizeof(inv); i++)
    {
        if (!inv[i]->query_unique()
        &&  inv[i]->query("skill_type")
        &&  inv[i]->query("equipped")
        &&  !weapon_cnt)
        {
            object obj = new(base_name(inv[i]));
            if (obj)
            {
                if(obj->move(me)) // mon 8/13/97
                obj->wield();
            }
            me->set("weapon", base_name(inv[i]));
            weapon_cnt = 1;
        }
        else if (!inv[i]->query_unique()
            &&  !inv[i]->query("skill_type")
            &&  inv[i]->query("equipped")
            &&  !armor_cnt)
        {
            object obj = new(base_name(inv[i]));
            if (obj)
            {
                if(obj->move(me))
                obj->wear();   //mon 8/13/97
            }
            me->set("armor", base_name(inv[i]));
            armor_cnt = 1;
        }
        else if (weapon_cnt && armor_cnt)
            break;
    }

    me->setup();
    me->save();
    reset_eval_cost();

    return 1;
}

int init_identity(object me, object master, object where)
{
    mapping skill_status;
    string *skillnames;
    int i;

    reset_eval_cost();
    me->setup();

    me->move(where);
    me->set("where", base_name(where));

    me->set("gender", master->query("gender") );
    me->set("current_master", master->query("id"));
    me->set("current_master_base_name", base_name(master));
    me->set("family/generation", master->query("family/generation"));
    me->set("family/family_name", master->query("family/family_name"));

    me->set("short", me->query("name")+"("+capitalize(me->query("id"))+")");

    me->restore();
    if (me->query("current_player") != "none of us")
        return 1;

    remove_call_out("self_adjust");
    call_out("self_adjust", 1, me);

    me->reset_me(me);
    me->set("new_player", 1);
    save_record(me, master);

    return 1;
}

void create_identity(mixed master, mixed where)
{
    object master_ob, where_ob;

    if (this_object()->query("created"))
        return;
    this_object()->set("created", 1);

    if (objectp(master))
        master_ob = master;
    else
    {
        master_ob = new(master);
        master_ob->restore();
    }

    if (objectp(where))
        where_ob = where;
    else
    {
        call_other(where, "???");
        where_ob = find_object(where);
    }
    init_identity(this_object(), master_ob, where_ob);
}

int convert_identity(object me, object ob)
{
    object who;
    string data_key = me->query("data_key");
    string my_title = me->query("title");

    reset_eval_cost();

    who = find_player(me->query("current_player"));
    if (!who)
    {
        // nobody to recover
    }
    else if (who->query(data_key+"/title_old"))
    {
        who->set("title", who->query(data_key+"/title_old"));
    }
    else if (who->query("family/family_name"))
    {
        who->set("title",
            sprintf("%s第%s代%s",
            who->query("family/family_name"),
            chinese_number(who->query("family/generation")),
            who->query("family/title")));
        who->save();
    }
    ob->set(data_key+"/base_name", base_name(me));
    ob->set(data_key+"/data_name", me->query_save_file());
    ob->set(data_key+"/title_old", ob->query("title"));

    ob->set(data_key+"/title", my_title);
    ob->set("title", my_title);
    ob->save();

    me->reset_me(me);
    me->set("name", ob->query("name"));
    me->set("gender", ob->query("gender"));
    me->set("current_player", ob->query("id"));

    me->set("short", me->query("name")+"("+capitalize(me->query("id"))+")");

    save_record(me, ob);

    return 1;
}

void reset_me(object me)
{
    int i;
    object *inv;
    mapping skill_status, map_status;
    string *skillnames, *mapnames;
    
    reset_eval_cost();
    if (mapp(map_status = me->query_skill_map()))
    {
        mapnames = keys(map_status);
        for (i=0; i<sizeof(mapnames); i++)
        {
            me->map_skill(mapnames[i]);
        }
    }

    if (mapp(skill_status = me->query_skills()))
    {
        skillnames = keys(skill_status);
        for (i=0; i<sizeof(skillnames); i++)
        {
            me->delete_skill(skillnames[i]);
        }
    }

    inv = all_inventory(me);
    for (i=0; i<sizeof(inv); i++)
    {
        destruct(inv[i]);
    }

    me->set("attitude", "heroism");
    me->set("current_player", "none of us");

    me->set("str", 30);
    me->set("per", 30);
    me->set("int", 30);
    me->set("age", 30);

    me->set("weapon", 0);
    me->set("armor", 0);

    me->set_skill("force",  60);
    me->set_skill("spells", 60);
    me->set_skill("unarmed",60);
    me->set_skill("sword",  60);
    me->set_skill("dodge",  60);
    me->set_skill("parry",  60);

    me->set("max_gin", 600);
    me->set("eff_gin", 600);
    me->set("gin", 600);
    me->set("max_kee", 600);
    me->set("eff_kee", 600);
    me->set("kee", 600);
    me->set("max_sen", 600);
    me->set("eff_sen", 600);
    me->set("sen", 600);
    me->set("force", 600);
    me->set("max_force", 600);
    me->set("mana", 600);
    me->set("max_mana", 600);
    me->set("force_factor", 600);
    me->set("combat_exp", 100000);

    me->setup();
    carry_object("/d/obj/cloth/linen")->wear();
    reset_eval_cost();
}

int fully_recover(object me)
{
    object *inv;
    object ob;
    string player_name;
    object current_player;

    reset_eval_cost();

    me->set("eff_gin", me->query("max_gin"));
    me->set("gin",     me->query("max_gin"));
    me->set("eff_kee", me->query("max_kee"));
    me->set("kee",     me->query("max_kee"));
    me->set("eff_sen", me->query("max_sen"));
    me->set("sen",     me->query("max_sen"));
    me->set("force",   me->query("max_force")*2);
    me->set("mana",    me->query("max_mana")*2);

    player_name = me->query("current_player");
    if (!player_name || player_name == "none of us")
        return 1;
  
    if (current_player = find_player(player_name))
    {
        if (current_player->query("combat_exp")>me->query("combat_exp"))
            save_record(me, current_player);
    }
    else if (current_player = LOGIN_D->find_body(player_name))
    {
        if (current_player->query("combat_exp")>me->query("combat_exp"))
            save_record(me, current_player);
    }
    else
    {
        seteuid(player_name);
        current_player = new(USER_OB);
        current_player->set("id", player_name);
        if (!current_player->restore())
        {
            destruct(current_player);
            return 1;
        }
        export_uid(current_player);
        seteuid(getuid());
        current_player->setup();
        if (current_player->query("combat_exp")>me->query("combat_exp"))
            save_record(me, current_player);
        destruct(current_player);
    }

    inv = all_inventory(me);
    while (inv && sizeof(inv))
    {
        destruct(inv[0]);
        inv = all_inventory(me);
    }

    if (me->query("weapon"))
    {
        ob = new(me->query("weapon"));
        if(ob->move(me))
            ob->wield();
    }

    if (me->query("armor"))
    {
        ob = new(me->query("armor"));
        if(ob->move(me))
            ob->wear();
    }

    reset_eval_cost();
    return 1;
}

string query_save_file()
{
    string str = query("save_file");
    int i;

    if (str)
        return str;

    str = DATA_DIR+"puppet/puppet_"+query("current_master");
    for (i = 0; i < sizeof(str); i++)
        if (str[i]==' ') str[i] = '_';

    return str;
}

void set_save_file(string str)
{
    set("save_file", str);
}

object find_and_restore(string name)
{
    object me = find_object(name);

    if (!me || !me->restore())
        me = new(name);
    me->setup();
    return me;
}

void init()
{
    object me = this_object();

    ::init();
    add_action("do_bandage", "bandage");

    if (me->query("current_player") == "none of us")
        me->reset_me(me);
    me->restore();
    me->fully_recover(me);
}

int do_bandage(string arg)
{
    object who = this_player();
    object me = this_object();

    if (!arg || me != present(arg, environment(me)))
        return 0;

    message_vision("$N别有用心地要给$n包扎伤口。\n", who, me);
    call_out("no_bandage", 2, who, me);
    return 1;
}

void no_bandage(object who, object me)
{
    message_vision("$N向$n摇了摇头。\n", me, who);
}
