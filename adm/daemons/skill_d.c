// ALI by NewX 
// skill_d.c

mapping skill_list;

void create()
{
    string *infolist;

    infolist = explode(read_file("/daemon/skill_list"), "\n");
    skill_list = allocate_mapping(sizeof(infolist));
    for (int i = 0; i < sizeof(infolist); i++)
    {
        string skill, type;
        if (infolist[i][0] == '#') continue;
        if (sscanf(infolist[i], "%s %s", skill, type) == 2) {
            skill_list[skill] = "/daemon/skill/" + type + "/"+ skill;
        }
    }
}

mixed find_skill(string skill)
{
    string path = skill_list[skill];
    if (!stringp(path)) {
        path = "/daemon/skill/" + skill;
    }
    return path;
//    return load_object(path);
}
