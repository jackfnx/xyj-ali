
inherit ROOM;

void setup()
{
    string *ways;
    
    set("short", "海底迷宫");
    set("long", @LONG

海水又变的清澈了，但你已经很难找到方向了。
四周的景物好象都一样，要是没人引路的话看来
很难出去了。
LONG );

    ways = query("ways");
    if (!query("exits/east")) set("exits/east", ways[random(sizeof(ways))]);
    if (!query("exits/west")) set("exits/west", ways[random(sizeof(ways))]);
    if (!query("exits/north")) set("exits/north", ways[random(sizeof(ways))]);
    if (!query("exits/south")) set("exits/south", ways[random(sizeof(ways))]);

    if (!query("objects")) {
        set("objects", ([
            __DIR__"xiaoyu" : 1,
        ]));
    }

    ::setup();
}

void init()
{
    if (this_player()->query("id") == "xiao hong yu"
    ||  this_player()->query("id") == "xiao qing yu"
    ||  this_player()->query("id") == "xiao lan yu"
    ||  this_player()->query("id") == "xiao bai yu"
    ||  this_player()->query("id") == "xiao hua yu"
    ||  this_player()->query("id") == "xiao jin yu"
    )
        message_vision("$N游了过来。\n", this_player());
}

int valid_leave(object me, string dir)
{
    if (this_player()->query("id") == "xiao hong yu"
    ||  this_player()->query("id") == "xiao qing yu"
    ||  this_player()->query("id") == "xiao lan yu"
    ||  this_player()->query("id") == "xiao bai yu"
    ||  this_player()->query("id") == "xiao hua yu"
    ||  this_player()->query("id") == "xiao jin yu"
    )
        message_vision("$N摆着尾巴游走了。\n", this_player());
    return ::valid_leave(me, dir);
}
