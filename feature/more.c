// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// more.c

#include <ansi.h>

varargs void more(string cmd, string *text, int line, int force)
{
    int i, len = strlen("" + sizeof(text));

    switch(cmd) {
        case "q":
            write(ESC+"[1A"+ESC+"[100D"+ESC+"[K\n");
            return;
        case "b":
            line = line - 46;
            if (line < -22 && !force) return;
            write("\n"+ESC+"[1A"+ESC+"[100D"+ESC+"[K"+repeat_string("-",100)+"\n");
            for (i = line + 23; line < i; line++)
                if (line >= 0) printf(CYN"%."+len+"d"NOR" %s\n", line, text[line]);
            break;
        case "f":
            write(ESC+"[1A"+ESC+"[100D"+ESC+"[K");
            for(i = line + 23; line < sizeof(text) && line < i; line++)
                printf(CYN"%."+len+"d"NOR" %s\n", line, text[line]);
            if (line >= sizeof(text) && !force) return;
            break;
        case "":
        default:
            write(ESC+"[1A"+ESC+"[100D"+ESC+"[K");
            for(i = line + 1; line < sizeof(text) && line < i; line++)
                printf(CYN"%."+len+"d"NOR" %s\n", line, text[line]);
            if (line >= sizeof(text) && !force) return;
            break;
    }
    printf("== 未完继续 "HIY"%d%%"NOR" == ("HIG"q"NOR" 离开，"HIG"b"NOR" 前一页，"HIG"f"NOR" 后一页，"HIG"[其他键]"NOR" 滚动)",
        (line*100/sizeof(text)));
    input_to("more", text, line);
}

varargs void start_more(string msg, int force)
{
    //11/13/97 try to prevent crash by mon.
    if (!msg || strlen(msg) < 1) // no messages.
        return;

    write("\n");
    more("f", explode(msg, "\n"), 0, force);
}
