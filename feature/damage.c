// ALI by NewX

// damage.c

#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>
#include <skill.h>
#include <sex.h>

void remove_faint(object me);

int ghost = 0;

int is_ghost() { return ghost; }

int self_purge()
{
    object me=this_object();
    object link_ob = me->query_temp("link_ob");

    if ( !userp(me) ) return 0;
    if (
        // Removed since we don't use this part. Dream 12/11/97.
        // Re-removed again on the same day :-)
        (int)me->query("max_gin") > 0 &&
        (int)me->query("max_kee") > 0 &&
        (int)me->query("max_sen") > 0 )
        return 0;

    set_heart_beat(0);
    ghost =1;
    me->move("/d/death/block.c");
    CHANNEL_D->do_channel(me, "rumor", me->query("name")
            + "因为年纪太大，心力交瘁，不幸与世长辞，永远离开了我们！");
    return 1;
}

varargs int receive_damage(string type, int damage, object who)
{
    int val;

    if ( damage < 0 ) error("F_DAMAGE: 伤害值为负值。\n");
    if ( type!="gin" && type!="kee" && type!="sen" )
        error("F_DAMAGE: 伤害种类错误( 只能是 gin, kee, sen 其中之一 )。\n");

    if ( objectp(who) ) set_temp("last_damage_from", who);
    val = (int)query(type) - damage;

    if ( val >= 0 ) set(type, val);
    else {
        set( type, -1 );

        //added by mon for pk and nk.
        if (living(this_object())&&objectp(who)&&userp(who)
            && !query_temp("last_fainted_from")
            //must not be fainted before within 60 sec.
            ) {
            set_temp("last_fainted_from", who->query("id"));
            if (userp(this_object()))
                call_out("remove_faint", 60, this_player());
            //prevent help other to faint a npc or player
            //and to get daoxing.
            //has to wait 60 second after the faint.
            //for NPC, the last_fainted_from mark will not
            //be erased, so only the first one who faint a npc
            //can possibly get dx. One can't help others to
            //faint a npc.
        }
    }

   set_heart_beat(1);

   return damage;
}

varargs int receive_wound(string type, int damage, object who)
{
    int val;

    if ( damage < 0 ) error("F_DAMAGE: 伤害值为负值。\n");
    if ( type!="gin" && type!="kee" && type!="sen" )
        error("F_DAMAGE: 伤害种类错误( 只能是 gin, kee, sen 其中之一 )。\n");

    if ( objectp(who) ) set_temp("last_damage_from", who);
        val = (int)query("eff_" + type) - damage;

    if ( val >= 0 ) set("eff_" + type, val);
    else {
        set( "eff_" + type, -1 );
        val = -1;

        //added by mon for pk and nk.
        if (living(this_object())&&objectp(who)&&userp(who)
            &&!query_temp("last_fainted_from")
            //must not be fainted before within 60 sec.
            ) {
            set_temp("last_fainted_from",who->query("id"));
            if (userp(this_object()))
                call_out("remove_faint",60,this_player());
            //prevent help other to faint a npc or player
            //and to get daoxing.
            //has to wait 60 second after the faint.
            //for NPC, the last_fainted_from mark will not
            //be erased, so only the first one who faint a npc
            //can possibly get dx. One can't help others to
            //faint a npc.
        }
    }

    if ( (int)query(type) > val ) set(type, val);

    set_heart_beat(1);

    return damage;
}

void remove_faint(object me)
{
    if (me) me->delete_temp("last_fainted_from");
}

int receive_heal(string type, int heal)
{
    int val;

    if ( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
    if ( type!="gin" && type!="kee" && type!="sen" )
        error("F_DAMAGE: 恢复种类错误( 只能是 gin, kee, sen 其中之一 )。\n");

    val = (int)query(type) + heal;

    if ( val > (int)query("eff_" + type) ) set(type, (int)query("eff_" + type));
    else set( type, val );

    return heal;
}

int receive_curing(string type, int heal)
{
    int max, val;

    if ( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
    if ( type!="gin" && type!="kee" && type!="sen" )
        error("F_DAMAGE: 恢复种类错误( 只能是 gin, kee, sen 其中之一 )。\n");

    val = (int)query("eff_" + type);
    max = (int)query("max_" + type);

    if ( val + heal > max ) {
        set("eff_" + type, max);
        return max - val;
    } else {
        set( "eff_" + type, val + heal);
        return heal;
    }
}

// snowcat feb 8 1998 
void remove_ride()
{
    object rider, ridee;
    
    if (ridee = query_temp("ridee"))
        ridee->delete_temp("rider");
    delete_temp("ridee");
    add_temp("apply/dodge", -query_temp("ride/dodge"));
    set_temp("ride/dodge", 0);
    if (rider = query_temp("rider"))
        rider->remove_ride();
    delete_temp("rider");
}

void unconcious()
{
    object defeater;

    if (environment() && environment()->query("alternative_die")) {
        environment()->alternative_die(this_object());
        return;
    }

    if ( !living(this_object()) ) return;
    if ( wizardp(this_object()) && query("env/immortal") ) return;

    if ( objectp(defeater = query_temp("last_damage_from")) )
        COMBAT_D->winner_reward(defeater, this_object());

    this_object()->remove_all_enemy();
    remove_ride();

    message("system", HIR "\n你的眼前一黑，接着什么也不知道了．．．\n\n" NOR,
            this_object());
    this_object()->disable_player(" <昏迷不醒>");
    set("gin", 0);
    set("kee", 0);
    set("sen", 0);
    set_temp("block_msg/all", 1);
    COMBAT_D->announce(this_object(), "unconcious");

    call_out("revive", random(100 - query("con")) + 30);
}

varargs void revive(int quiet)
{
    remove_call_out("revive");

//   delete_temp("last_fainted_from");
// revive will not remove this mark.

    delete_temp("no_move");
    //sometimes players still set no_move after death
    //and can't be cleared.

    if ( this_object()->is_busy() ) this_object()->start_busy(1);
    //clear the busy flag.

    while ( environment()->is_character() )
        this_object()->move(environment(environment()));
    this_object()->enable_player();

    if ( !quiet ) {
        COMBAT_D->announce(this_object(), "revive");
        set_temp("block_msg/all", 0);
        message("system", HIY "\n慢慢地你终于又有了知觉．．．\n\n" NOR,
                this_object());
    } else
        set_temp("block_msg/all", 0);
}

void die()
{
    object corpse, killer;
    object *inv;
    int i;
    string last_fainted_from;
//    mapping quest;
//    int exp, pot, score;

    if (environment() && environment()->query("alternative_die")) {
        environment()->alternative_die(this_object());
        return;
    }

    if (query_temp("last_fainted_from"))
        last_fainted_from=query_temp("last_fainted_from");

    if ( !living(this_object()) ) revive(1);
    if ( wizardp(this_object()) && query("env/immortal") ) return;

    // Clear all the conditions by death.
    this_object()->clear_condition();

    //needed because last_fainted_from is cleared in revive()
    if (last_fainted_from)
        set_temp("last_fainted_from", last_fainted_from);

    // destroy all self-made fabao here
    inv = all_inventory(this_object());
    for (i=0; i<sizeof(inv); i++) {
        if ( inv[i]->query("owner_id") == getuid(this_object()) ) {
            tell_object(this_object(), HIB+"你看到" + inv[i]->query("name") +
                    HIB + "破空而去，慢慢消失在天际．．．\n"+NOR);
            destruct( inv[i] );
        }
    }

    COMBAT_D->announce(this_object(), "dead");

    if ( (int)this_object()->query("max_gin") > 0 &&
            (int)this_object()->query("max_kee") > 0 &&
            (int)this_object()->query("max_sen") > 0 ) {
        //no damage to self_purged people.

        if ( objectp(killer = query_temp("last_damage_from")) ) {
            set_temp("my_killer", killer->query("id"));
            COMBAT_D->killer_reward(killer, this_object());
            if (userp(this_object()))
                log_file("death",sprintf("[%s] %s is killed by %s.\n",
                            ctime(time()),this_object()->query("id"),
                            killer->query("id")));
        } else {
            //no obvious killer. by mon 8/17/97
            //for example, by poison.
            if (userp(this_object())) {
                string str;
                COMBAT_D->victim_penalty(this_object());
                if (str=this_object()->query_temp("death_msg"))
                    //can set customized death message to death_msg.
                    str=this_object()->name(1)+str;
                else  str=this_object()->name(1)+"莫名其妙地死了。\n";
                COMBAT_D->announce(this_object(), "death_rumor", str);
                log_file("death",sprintf("[%s] %s is killed: %s.\n",
                            ctime(time()),this_object()->query("id"),
                            str));
            }
        }
    }

    remove_ride();

#if 0
    if (killer && objectp(killer)) {
      if (!(quest = killer->query("fy_quest")) ||
          userp(this_object()) ||
          this_object()->query("name") != quest["quest"] ||
          "杀" != quest["quest_type"]) {
      } else if ((int) killer->query("task_time") < time() ) {
        tell_object(killer,"真可惜！你没有在指定的时间内完成！\n");
      } else {
        tell_object(killer,"恭喜你！你又完成了一项任务！\n");      
        exp = quest["exp_bonus"]/2 + random(quest["exp_bonus"]/2)+1;
        if(exp > 150) exp = 150;
        exp = exp * (int) killer->query_temp("quest_number");
        pot = exp / 5 + 1;
        score = 1;
        killer->add("combat_exp",exp);
        killer->add("potential",pot);
        killer->add("score",score);
        tell_object(killer,HIW"你被奖励了：\n" +
        chinese_number(exp) + "点实战经验\n"+
        chinese_number(pot) + "点潜能\n" +
        chinese_number(score)+"点综合评价\n"NOR);
        killer->set("fy_quest", 0 );
      }
    }
#endif

    if ( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
        corpse->move(environment());

    this_object()->remove_all_killer();
    all_inventory(environment())->remove_killer(this_object());

    this_object()->remove_all_fucker();
    all_inventory(environment())->remove_fucker(this_object());

    this_object()->dismiss_team();
    if ( this_object()->self_purge() ) return;


    if ( userp(this_object()) ) {
        set("gin", 1);   set("eff_gin", 1);
        set("kee", 1);   set("eff_kee", 1);
        set("sen", 1);   set("eff_sen", 1);
        ghost = 1;
        this_object()->move(DEATH_ROOM);
        DEATH_ROOM->start_death(this_object());
    } else
        destruct(this_object());
}

void reincarnate()
{
    ghost = 0;
    // drop all, or they could take a ghost out of hell.
    command("drop all");
    set("eff_gin", query("max_gin"));
    set("eff_kee", query("max_kee"));
    set("eff_sen", query("max_sen"));
}

int max_food_capacity() 
{
    int final;
    final=(int)query_weight()/200;
    if (final < 100 ) {
        final=100;
    }
    return final;
}

int max_water_capacity() 
{
    int final;
    final=(int)query_weight()/200;
    if ( final< 100 ) {
        final=100;
    }
    return final; 
}

int heal_up()
{
    int update_flag, i;
    mapping my;

//     if( this_object()->is_fighting() && !userp(this_object())
//       && random(4)!=0 ) return -1;

    update_flag = 0;

    my = query_entire_dbase();

    if ( my["water"] > 0 ) { my["water"] -= 1; update_flag++; }
    if ( my["food"] > 0 ) { my["food"] -= 1; update_flag++; }

    if ( my["water"] < 1 && userp(this_object()) ) return update_flag;

    my["gin"] += my["con"] / 3 + my["atman"] / 10;
    if ( my["gin"] >= my["eff_gin"] ) {
        my["gin"] = my["eff_gin"];
        if ( my["eff_gin"] < my["max_gin"] ) { my["eff_gin"] ++; update_flag++; }
    } else update_flag++;

    my["kee"] += my["con"] / 3 + my["force"] / 10;
    if ( my["kee"] >= my["eff_kee"] ) {
        my["kee"] = my["eff_kee"];
        if ( my["eff_kee"] < my["max_kee"] ) { my["eff_kee"] ++; update_flag++; }
    } else update_flag++;

    my["sen"] += my["con"] / 3 + my["mana"] / 10;
    if ( my["sen"] >= my["eff_sen"] ) {
        my["sen"] = my["eff_sen"];
        if ( my["eff_sen"] < my["max_sen"] ) { my["eff_sen"] ++; update_flag++; }
    } else update_flag++;

    if ( my["food"] < 1 && userp(this_object()) ) return update_flag;

    if ( my["max_atman"] && my["atman"] < my["max_atman"] ) {
        my["atman"] += 1 + (int)this_object()->query_skill("magic", 1) / 2;
        if ( my["atman"] > my["max_atman"] ) my["atman"] = my["max_atman"];
        update_flag++;
    }

    if ( my["max_force"] && my["force"] < my["max_force"] ) {
        my["force"] += 1 + (int)this_object()->query_skill("force", 1) / 2;
        if ( my["force"] > my["max_force"] ) my["force"] = my["max_force"];
        update_flag++;
    }

    if ( my["max_mana"] && my["mana"] < my["max_mana"] ) {
        my["mana"] += 1 + (int)this_object()->query_skill("spells", 1) / 2;
        if ( my["mana"] > my["max_mana"] ) my["mana"] = my["max_mana"];
        update_flag++;
    }

    return update_flag;
}

int sex_inspire(string type, int fire)
{
    int val, max;

    if (fire < 0) error("F_DAMAGE: SA为负值。\n");
    if (type == "libido")
        max = MAX_LIBIDO;
    else if (type == "stamina")
        max = MAX_STAMINA;
    else
        error("F_DAMAGE: 未知的SA种类。\n");

    val = (int)query(type);
    val += fire;
    if (val > max) val = max;
    set(type, val);
    
    set_heart_beat(1);
    return val;
}

int sex_depress(string type, int water)
{
    int val;

    if (water < 0) error("F_DAMAGE: SD为负值。\n");
    if (type != "libido" && type != "stamina")
        error("F_DAMAGE: 未知的SD种类。\n");

    val = (int)query(type);
    val -= water;
    if (val < 0) val = 0;
    set(type, val);
    return val;
}

// faqing: boqi and shirun
void heat()
{
    string gender = query("gender");

    set_temp("sex_heat", 1);
    if (gender == "男性") {
        set_temp("erect", 1);
        SEX_D->announce(this_object(), "erect");
    } else if (gender == "女性") {
        set_temp("wet", 1);
        SEX_D->announce(this_object(), "wet");
    } else
        error("F_DAMAGE: 未知的性别... " + gender + "\n");

    call_out("remove_heat", 20);
}

void remove_heat()
{
    string gender = query("gender");

    remove_call_out("remove_heat");

    if (query("libido") > EFF_LIBIDO) {
        call_out("remove_heat", 20);
        return;
    }

    if (query_temp("ejaculate")) {
        call_out("remove_heat", 20);
        return;
    }

    set_temp("sex_heat", 0);
    if (gender == "男性") {
        delete_temp("erect");
        SEX_D->announce(this_object(), "no_erect");
    } else if (gender == "女性") {
        delete_temp("wet");
        SEX_D->announce(this_object(), "no_wet");
    } else
        error("F_DAMAGE: 未知的性别... " + gender + "\n");
}

// gaochao: shejing and chaochui
void orgasm()
{
    string gender = query("gender");

    if (gender == "男性") {
        message("system", HIR "\n你感到腰眼一麻，下体射出了一道又一道精阳！\n顿时一阵巨大的快感袭入了你的脑海，你不禁一阵眩晕。。。\n\n" NOR, this_object());
        this_object()->disable_player(HIC + " <射精中>" + NOR);
        SEX_D->announce(this_object(), "ejaculate");
        add_temp("ejaculate", random(query("libido") / 10));
        set_temp("block_msg/all", 1);
        call_out("ejaculate", 2);
    } else if (gender == "女性") {
        string org;
        add_temp("orgasm", 1);
        if ((int)query("orgasm") < 2) org = "高潮";
        else org = chinese_number((int)query("orgasm")) + "重高潮";
        message("system", HIR "\n你感到脑中轰的一声，仿佛灵魂已经被抽出了肉体！\n你达到了至高无上的" + org + "！\n\n" NOR, this_object());
        this_object()->disable_player(HIM + " <高潮中>" + NOR);
        SEX_D->announce(this_object(), "orgasm");
        SEX_D->gain_enjoy(this_object(), "orgasm");
        set_temp("block_msg/all", 1);
        call_out("no_orgasm", random(40 - this_object()->query_con()));
    } else
        error("F_DAMAGE: 未知的性别... " + gender + "\n");
}

void ejaculate()
{
    remove_call_out("ejaculate");
    add_temp("ejaculate", -1);
    if ((int)query_temp("ejaculate") > 0) {
        SEX_D->gain_enjoy(this_object(), "ejaculate");
        call_out("ejaculate", 2);
    } else {
        set_temp("ejaculate", 0);
        set_temp("block_msg/all", 0);
        this_object()->enable_player();
        call_out("remove_heat", 1);
    }
}

void no_orgasm()
{
    remove_call_out("no_orgasm");
    this_object()->enable_player();
    set_temp("block_msg/all", 0);
    message("system", HIG "\n随着欲火的消退，你感到灵魂又回到了肉体中！\n\n" NOR, this_object());
}

int sex_refresh()
{
    mapping my;
    string dodge, force, spells;
    int update_flag, sex_per;

    update_flag = 0;
    my = query_entire_dbase();
    if (!mapp(my)) return 0;

    if (my["libido"] > 0) { my["libido"] -= 1; update_flag++; }
    if (my["stamina"] < MAX_STAMINA) { my["stamina"] += 1; update_flag++; }

    /*
    sex_per = my["per"] + query_temp("apply/personality");
    if (query_skill("fascination") > 20)
        sex_per += (query_skill("fascination")-20)/10;
    if (query_skill("fascination") > 100)
        sex_per -= (query_skill("fascination")-80)/10;
    if (sex_per > 40) {
        object env = environment();
        if (objectp(env)) {
            int i = 0;
            object ob = first_inventory(env);
            while (ob) {
                if (ob != this_object() && living(ob)) {
                    ob->sex_inspire("libido", sex_per / 10);
                    update_flag++;
                    i++;
                }
                ob = next_inventory(ob);
            }
            if (i)
                message_vision("$N的身上散发着不可抗拒的魅力，在场众人都不禁怦然心动。\n", this_object());
        }
    }
    */

    return update_flag;
}
