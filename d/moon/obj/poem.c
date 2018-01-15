// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// poem.c

inherit ITEM;

void init();
int do_read();

void create()
{
        set_name("断肠集", ({"poem","book","shu"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
   set("long",
   "一本手抄的＂断肠集＂，字迹娟秀，书页上隐隐有一些泪痕．\n");
        set("value", 500);   
        }
}

void init()
{
   add_action("do_read", "read");
   add_action("do_read", "study");
}

int do_read(string arg)
{
   object me;
   int sen_cost, gain;
   string *poem = ({
     "恰如飞鸟倦知还，澹荡梨花深院。",
     "拂拂风前度暗香，月色侵花冷。",
     "不放玉花飞堕地，留在广寒宫阙。