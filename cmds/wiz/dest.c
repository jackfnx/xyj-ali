// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// dest.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string option, target, msg;
    object obj, *body, ob, *clones;
    int i;

    if (!arg) return notify_fail("指令格式 : dest <物件之名称或档名>\n" );

    if (sscanf(arg, "%s %s", option, target)!=2) target = arg;
    if (option != "-r" && option != "-p" && option != "-c") target = arg;

    // added by mon. 3/12/97
    if (arg == "-p") {
        body = children(USER_OB);
        for (i=0; i<sizeof(body); i++) {
            ob = body[i];
            if (clonep(ob) && ob->query("max_gin")==0)
                write(getuid(ob)+" "+ob->short()+"\n");
        }
        return 1;
    }

    if (option == "-c") {
        seteuid(geteuid(me));
        clones = children(target);
        if (!clones || !sizeof(clones)) return notify_fail("没有这样物件。\n");
        
        for (i = 0; i<sizeof(clones); i++) {
            ob = clones[i];
            if (environment(ob)) {
                if (environment(ob) == environment(me)) {
                    if (!stringp(msg = me->query("env/msg_dest")))
                        msg = "$N召唤出一个黑洞，将$n吞没了。";
                    message_vision(msg + "\n", me, ob);
                } else {
                    message_vision("虚空中忽然出现了一个黑洞，将$N吞没了。\n", ob);
                }
            }
            printf("摧毁物件：%O ", ob);
            destruct(ob);
            if (ob) write("---> 摧毁失败。\n");
            else write("---> Ok.\n");
        }
        write("Ok.\n");
        return 1;
    }

    if (option == "-r" && (string)SECURITY_D->get_status(me)=="(admin)")
        seteuid(ROOT_UID);
    else
        seteuid(geteuid(me));

    obj = find_object(target);
    if (!obj) obj = present(target, me);
    if (!obj) obj = present(target, environment(me));
    if (!obj) obj = find_object( resolve_path(me->query("cwd"), target));
    if (!obj) return notify_fail("没有这样物件。\n");

    if (environment(me)==environment(obj)) {
        if (!stringp(msg = me->query("env/msg_dest")))
            msg = "$N召唤出一个黑洞，将$n吞没了。";
        message_vision(msg + "\n", me, obj);
    }
    printf("摧毁物件：%O\n", obj);
    destruct(obj);
    if (obj) write("你无法将这个物件摧毁。\n");
    else write("Ok.\n");

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : dest [-r|-c] <物件之名称或档名>
           dest [-p] show damaged player objects.

利用此一指令可将一个物件(object)或物件定义(class)从记忆体中清除，若清除物
件定义(即：指定档名的情况下)则下一次参考到这个物件的时候会重新将它编译。

具有 (admin) 身分的巫师可以用 -r 选项以 ROOT_UID 身分来清除被保护的物件如
使用者。

使用 -c 选项则可以摧毁一个物件的所有clonep物件。

参考资料： destruct()
HELP
    );
    return 1;
}
