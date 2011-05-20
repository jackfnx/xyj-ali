// fate.c

#include <dbase.h>

mapping eternal_fates;
static mapping fates;

void start_fate(object ob)
{
    string keyword;
    function f;

    keyword = ob->query("fate_keyword");
    if (!keyword)
        keyword = file_name(ob);

    if (!mapp(fates) || !functionp(f = fates[keyword])) {
        if (!mapp(eternal_fates) || !stringp(eternal_fates[keyword])) return;
        f = (: call_other, FATE_D(eternal_fates[keyword]), "start_fate", this_object() :);
    }
    evaluate(f);
}

void add_fate(mixed ob, function f)
{
    string keyword;

    if (stringp(ob)) keyword = ob;
    else if (objectp(ob)) {
        keyword = ob->query("fate_keyword");
        if (!keyword)
            keyword = file_name(ob);
    } else
        return;

    if (!fates) fates = ([]);
    fates += ([ keyword : f ]);
}

void add_eternal_fate(mixed ob, string fate)
{
    string keyword;
    
    if (stringp(ob)) keyword = ob;
    else if (objectp(ob)) {
        keyword = ob->query("fate_keyword");
        if (!keyword)
            keyword = file_name(ob);
    } else
        return;

    if (!eternal_fates) eternal_fates = ([]);
    eternal_fates += ([ keyword : fate ]);
}

void remove_fate(mixed ob)
{
    string keyword;
    
    if (stringp(ob)) keyword = ob;
    else if (objectp(ob)) {
        keyword = ob->query("fate_keyword");
        if (!keyword)
            keyword = file_name(ob);
    } else
        return;

    map_delete(fates, keyword);
}

void remove_eternal_fate(mixed ob)
{
    string keyword;
    
    if (stringp(ob)) keyword = ob;
    else if (objectp(ob)) {
        keyword = ob->query("fate_keyword");
        if (!keyword)
            keyword = file_name(ob);
    } else
        return;

    map_delete(eternal_fates, keyword);
}