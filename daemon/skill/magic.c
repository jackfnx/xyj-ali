// magic.c

inherit SKILL;

string name() { return "本命神通"; }

string conjure_magic_file(string magic)
{
    return "/daemon/class/magic/" + magic;
}
