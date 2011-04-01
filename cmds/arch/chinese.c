// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string key, chinz;
    
    if( !arg || arg=="" )
        return notify_fail("指令格式：chinese <英文>==<中文>\n");
    
    if( sscanf(arg, "%s==%s", key, chinz)==2 ) {
        if (chinz != "") {
            CHINESE_D->add_translate(key, chinz);
            write( key + " == " + chinz + "\nOk.\n");
        }
        else {
            CHINESE_D->remove_translate(key);
            write(key + " remove OK.\n");
        }
        return 1;
    }
    
    return 0;
}

int help()
{
    write ( @HELP
增加对照：chinese <英文>==<中文>
删除对照：chinese <英文>==<>
HELP
    );
    return 1 ;
}
