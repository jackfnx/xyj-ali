// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// more.c

#include <ansi.h>

varargs void more(string cmd, string *text, int line, int force)
{
    int i,j;

    switch(cmd) {
        case "b":
            line = line - 46;
            if (line <- 22 && !force) return;
                write("\n"+ESC+"[1A"+ESC+"[100D"+ESC+"[K\n"+repeat_string("-",100)+"\n");
            for (i = line + 23; line < i; line++)
                write(text[line] + "\n");
            break;
        case "q":
            write(ESC+"[1A"+ESC+"[100D"+ESC+"[K\n");
            return;
        case "":
        case "f":
        default:
            write(ESC+"[1A"+ESC+"[100D"+ESC+"[K");
            for(i = line + 23; line < sizeof(text) && line < i; line++)
                write(text[line] + "\n");
            if (line >= sizeof(text) && !force) return;
            break;
    }
    printf("== 未完继续 " HIY "%d%%" NOR " == ("HIG"q"NOR" 离开，"HIG"b"NOR" 前一页，"HIG"[其他键]"NOR" 继续下一页)",
        (line*100/sizeof(text)));
    input_to("more", text, line);
}

varargs void start_more(string msg, int force)
{
    if (!msg || strlen(msg) < 1) // no messages.
        return;
    //11/13/97 try to prevent crash by mon.

    write("\n");
    more("", explode(msg, "\n"), 0, force);
}
