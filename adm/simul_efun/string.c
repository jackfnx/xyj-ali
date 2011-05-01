string ansi_filter(string str)
{
    str = replace_string(str, "$BLK$", "");
    str = replace_string(str, "$RED$", "");
    str = replace_string(str, "$GRN$", "");
    str = replace_string(str, "$YEL$", "");
    str = replace_string(str, "$BLU$", "");
    str = replace_string(str, "$MAG$", "");
    str = replace_string(str, "$CYN$", "");
    str = replace_string(str, "$WHT$", "");
    str = replace_string(str, "$HIR$", "");
    str = replace_string(str, "$HIG$", "");
    str = replace_string(str, "$HIY$", "");
    str = replace_string(str, "$HIB$", "");
    str = replace_string(str, "$HIM$", "");
    str = replace_string(str, "$HIC$", "");
    str = replace_string(str, "$HIW$", "");
    str = replace_string(str, "$NOR$", "");
    return str;
}