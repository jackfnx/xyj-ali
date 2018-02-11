inherit F_DBASE;

#include <ansi.h>

int loading;

string *U2G_SPDIC_DEF = ({
        "/util/U2G_S1.dic",
        "/util/U2G_S2.dic",
});

string *U2G_DIC_DEF = ({
        "/util/U2G_1.dic",
        "/util/U2G_2.dic",
        "/util/U2G_3.dic"
    });

string *G2U_DIC_DEF = ({
        "/util/G2U_0.dic",
        "/util/G2U_1.dic",
        "/util/G2U_2.dic",
        "/util/G2U_3.dic",
        "/util/G2U_4.dic",
        "/util/G2U_5.dic",
        "/util/G2U_6.dic",
        "/util/G2U_7.dic"
    });

mapping U2G_S_dic = ([]);
string *U2G_dic = ({});
mixed *G2U_dic = ({});

string encode_utf8(int *codes);
string encode_gb2312(int *codes);
int *decode_gb2312(string str);
int *decode_utf8(string str);

void create()
{
    seteuid(getuid());   // This is required to pass intermud access check.
    set("channel_id", "内码精灵");

    loading = 1;
    call_out("start_load_dic", 5);
}

void start_load_dic()
{
    message("system",
        HIR "\n你听到有人吆喝了一声：开始更新系统了！用GB码的要乱码一阵子了！忍忍吧！\n\n" NOR,
        users());

    loading = 1;
    U2G_dic = ({});
    G2U_dic = ({});
    CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading has been started...");

    call_out("load_dic_U2G", 1, 0);
}

void load_dic_U2G(int step)
{
    string bytes;
    string *buf;

    if (step < sizeof(U2G_DIC_DEF))
    {
        bytes = read_file(U2G_DIC_DEF[step]);
        buf = allocate(sizeof(bytes)/2);
        for (int i = 0; i < sizeof(bytes) / 2; i++)
        {
            buf[i] = bytes[i*2..i*2+1];
        }
        U2G_dic += buf;

        CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading... U2G step:" + (step + 1));
        call_out("load_dic_U2G", 1, step + 1);
    }
    else
    {
        CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading... U2G compeleted.");
        call_out("load_dic_G2U", 1, 0);
    }
}

void load_dic_G2U(int step)
{
    string *bytes;
    int line_length;
    int lines;


    if (step < sizeof(G2U_DIC_DEF))
    {
        bytes = explode(read_file(G2U_DIC_DEF[step]), "\n");
        line_length = 0xFF - 0x40;
        lines = sizeof(bytes) / line_length;
        for (int i = 0; i < lines; i++)
        {
            string *buf = allocate(line_length);
            for (int j = 0; j < line_length; j++)
            {
                int code = 0;
                int offset = i * line_length + j;
                sscanf(bytes[offset], "%x", code);
                buf[j] = encode_utf8(({ code }));
            }
            G2U_dic += ({ buf });
        }

        CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading... G2U step:" + (step + 1));
        call_out("load_dic_G2U", 1, step + 1);
    }
    else
    {
        CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading... G2U compeleted.");
        call_out("load_dic_U2G_S", 0);
    }
}

void load_dic_U2G_S(int step)
{
    string *lines;

    if (step < sizeof(U2G_SPDIC_DEF))
    {
        lines = explode(read_file(U2G_SPDIC_DEF[step]), "\n");
        for (int i = 0; i < sizeof(lines); i++)
        {
            string key, value;
            sscanf(lines[i], "%s:%s", key, value);
            U2G_S_dic[key] = value;
        }


        CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading... U2G_s step:" + (step + 1));
        call_out("load_dic_U2G_S", 1, step + 1);
    }
    else
    {
        CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading... U2G_s compeleted.");
        call_out("load_dic_complete", 1);
    }
}

void load_dic_complete()
{
    CHANNEL_D->do_channel(this_object(), "sys", " Chinese DIC Loading all compeleted.");
    loading = 0;
    message("system",
        HIR "\n你听到那个声音又吆喝了一声：完事了！继续用吧！\n\n" NOR,
        users());
}

/// UTF8字符串解码成UCS2整形数组
int *decode_utf8(string str)
{
    int *codes = ({});

    for (int i = 0; i < strlen(str); i++) {
        int code = str[i];
        if (str[i] < 0x80) { // [0xxxxxxx ~ 10xxxxxx)
            // ascii
        } else if (str[i] < 0xC0) { // [10xxxxxx ~ 110xxxxx)
            // error
        } else if (str[i] < 0xE0) { // [110xxxxx ~ 1110xxxx)
            code = str[i] - 0xC0;
            code *= 0x40;
            code += str[i + 1] - 0x80;
            i += 1;
        } else if (str[i] < 0xF0) { // [1110xxxx ~ 11110xxx)
            code = str[i] - 0xE0;
            code *= 0x40;
            code += str[i + 1] - 0x80;
            code *= 0x40;
            code += str[i + 2] - 0x80;
            i += 2;
        } else if (str[i] < 0xF8) { // [11110xx ~ 111110xx)
            code = str[i] - 0xE0;
            code *= 0x40;
            code += str[i + 1] - 0x80;
            code *= 0x40;
            code += str[i + 2] - 0x80;
            code *= 0x40;
            code += str[i + 3] - 0x80;
            i += 3;
        } else { // [111110xx ~ )
            // error
        }
        codes += ({ code });
    }

    return codes;
}

/// GB2312字符串解码成GB2312整形数组
int *decode_gb2312(string str)
{
    int *codes = ({});

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int code = str[i];
        if (str[i] < 0x80) { // [0xxxxxxx ~ 10xxxxxx)
            // ascii
        } else {
            // gb2312
            code = str[i];
            code *= 0x100;
            code += str[i + 1];
            i += 1;
        }

        codes += ({ code });
    }
    return codes;
}

/// GB2312内码整形数组编码成GB2312字符串
string encode_gb2312(int *codes)
{
    string str = "";

    for (int i = 0; i < sizeof(codes); i++)
    {
        if (codes[i] < 0x80) { // [0xxxxxxx ~ 10xxxxxx)
            // ascii
            string buf = " ";
            buf[0] = codes[i];
            str += buf;
        } else {
            string buf = "  ";
            if (codes[i] / 0x100 == 0 || codes[i] % 0x100 == 0) {
                buf[0] = 0x23;
                buf[1] = 0x23;
            } else {
                buf[0] = codes[i] / 0x100;
                buf[1] = codes[i] % 0x100;            }
            str += buf;
        }
    }
    return str;
}

/// UCS2内码整形数组编码成UTF8字符串
string encode_utf8(int *codes)
{
    string str = "";

    for (int i = 0; i < sizeof(codes); i++)
    {
        if (codes[i] <= 0x7F)
        {
            // * U-00000000 - U-0000007F:  0xxxxxxx
            string buf = " ";
            buf[0] = codes[i];
            str += buf;
        }
        else if (codes[i] >= 0x00000080 && codes[i] <= 0x000007FF )
        {
            // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
            string buf = "  ";
            buf[1] = codes[i] % 0x40 + 0x80;
            buf[0] = codes[i] / 0x40 + 0xC0;
            str += buf;
        }
        else if (codes[i] >= 0x00000800 && codes[i] <= 0x0000FFFF)
        {
            // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
            string buf = "   ";
            buf[2] = codes[i] % 0x40 + 0x80;
            buf[1] = codes[i] / 0x40 % 0x40 + 0x80;
            buf[0] = codes[i] / 0x1000 + 0xE0;
            str += buf;
        }
        else if (codes[i] >= 0x00010000 && codes[i] <= 0x001FFFFF)
        {
            // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            string buf = "    ";
            buf[3] = codes[i] % 0x40 + 0x80;
            buf[2] = codes[i] / 0x40 % 0x40 + 0x80;
            buf[1] = codes[i] / 0x1000 % 0x40 + 0x80;
            buf[0] = codes[i] / 0x040000 + 0xF0;
            str += buf;
        }
        else if (codes[i] >= 0x00200000 && codes[i] <= 0x03FFFFFF)
        {
            // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            string buf = "     ";
            buf[4] = codes[i] % 0x40 + 0x80;
            buf[3] = codes[i] / 0x40 % 0x40 + 0x80;
            buf[2] = codes[i] / 0x1000 % 0x40 + 0x80;
            buf[1] = codes[i] / 0x040000 % 0x40 + 0x80;
            buf[0] = codes[i] / 0x01000000 + 0xF8;
            str += buf;
        }
        else if (codes[i] >= 0x04000000 && codes[i] <= 0x7FFFFFFF)
        {
            // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            string buf = "      ";
            buf[5] = codes[i] % 0x40 + 0x80;
            buf[4] = codes[i] / 0x40 % 0x40 + 0x80;
            buf[3] = codes[i] / 0x1000 % 0x40 + 0x80;
            buf[2] = codes[i] / 0x040000 % 0x40 + 0x80;
            buf[1] = codes[i] / 0x01000000 % 0x40 + 0x80;
            buf[0] = codes[i] / 0x40000000 + 0xFC;
            str += buf;
        }
    }
    return str;
}

string UTF8toGB2312(string arg)
{
    int *utf8_codes = decode_utf8(arg);
    string gb_str = "";

    if (loading)
        return arg;

    for (int i = 0; i < sizeof(utf8_codes); i++)
    {
        int c = utf8_codes[i];
        if (c <= 0x9DFF && c >= 0x4E00)
            gb_str += U2G_dic[c - 0x4E00];
        else if (c <= 0xFFFE && c >= 0x0100)
        {
            string key = sprintf("%x", c);
            gb_str += U2G_S_dic[key];
        }
        else
        {
            string buf = " ";
            buf[0] = c;
            gb_str += buf;
        }
    }
    return gb_str;
}

string GB2312toUTF8(string arg)
{
    int *gb_codes = decode_gb2312(arg);
    string utf8_str = "";

    if (loading)
        return arg;

    for (int i = 0; i < sizeof(gb_codes); i++)
    {
        int c = gb_codes[i];
        int b1 = c / 0x100;
        int b2 = c % 0x100;
        if (b1 >= 0x81 && b1 <= 0xFE && b2 >= 0x40 && b2 <= 0xFE)
            utf8_str += G2U_dic[b1-0x81][b2-0x40];
        else
        {
            string buf = " ";
            buf[0] = c;
            utf8_str += buf;
        }
    }
    return utf8_str;
}

string output(string str, object me)
{
    if (!str || !me)
        return str;

    if (!loading && me->query_encoding() == 1)
    {
        return UTF8toGB2312(str);
    }
    return str;
}

string input(string str, object me)
{
    if (!str || !me)
        return str;

    if (!loading && me->query_encoding() == 1)
    {
        return GB2312toUTF8(str);
    }
    return str;
}

string *getDic()
{
    return U2G_dic;
}
