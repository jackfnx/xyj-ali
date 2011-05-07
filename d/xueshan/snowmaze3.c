inherit __DIR__"snowmaze";

void create ()
{
    set("points", ({4, 8, 5, 7}));
    set("xmaze", "xmaze3");
    set("maze_exit", ({ __DIR__"xueshan4", __DIR__"xueshan3" }));

    setup();
}
