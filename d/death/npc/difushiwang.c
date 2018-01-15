// 地府十王

inherit NPC;

void kill_ob(object ob)
{
    object target = query_temp("target");
    if (target != ob) delete_temp("target");
    ::kill_ob(ob);
}

void fully_recover()
{
    set("kee",1000);
    set("eff_kee",1000);
    set("sen",1000);
    set("eff_sen",1000);
    set("gin",1000);
    set("eff_gin",1000);
    set("combat_exp",2000000);
    set("force",2000);
    set("max_force",2000);
    set("mana",4000);
    set("max_mana",2000);
    set("force_factor",120);
    clear_condition();
}

void die()
{
    if (add_temp("attempt/surrender", 1) > 10) {
        ::die();
        return;
    }
    command("surrender");
    fully_recover();
    remove_call_out("delete_temp");
    call_out("delete_temp", 120, "attempt/surrender");
}

void unconcious() { die(); }
