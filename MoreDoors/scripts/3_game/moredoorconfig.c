class MoreDoorConfig
{
    static const string MODCONFIG_ROOT_FOLDER = "$profile:MoreDoors/";
    static const string CONFIG_PATH = MODCONFIG_ROOT_FOLDER + "MoorDoors_Settings.json";


    private bool CanDestroyMoreDoor = true;
    private bool CanCutComboLock = true;
    private bool CanCraftDoorKits = true;
    private bool EnableVanillaRaiding = false;
    private ref array<string> MoreDoorRaidTools;
    private int MoreDoorShantyDestroyTime;
    private int MoreDoorDestroyTime;
    private int MoreDoorMetalDestroyTime;
    private int MoreDoorBarricadeDestroyTime;
    private int MoreDoorMetalBarricadeDestroyTime;
    private int MoreDoorDismantleTime;
    private int MoreDoorToolDamage;

    void MoreDoorConfig()
    {
        if (!GetGame().IsServer()) return;

        if (!FileExist(MODCONFIG_ROOT_FOLDER))
        {
            Print("[MasPuertas] '" + MODCONFIG_ROOT_FOLDER + "' does NOT exist, creating directory!");
            MakeDirectory(MODCONFIG_ROOT_FOLDER);
        }

        if (!FileExist(CONFIG_PATH))
        {
            Print("[MasPuertas] '" + CONFIG_PATH + "' does NOT exist, creating default config!");
            Default();
            return;
        }

        Load();
    }

    bool Load()
    {
        if (FileExist(CONFIG_PATH))
        {
            Print("[MasPuertas] '" + CONFIG_PATH + "' found, loading existing config!");
            JsonFileLoader<MoreDoorConfig>.JsonLoadFile(CONFIG_PATH, this);
            return true;
        }
        return false;
    }

    protected void Save()
    {
        JsonFileLoader<MoreDoorConfig>.JsonSaveFile(CONFIG_PATH, this);
    }

    protected void Default()
    {
        CanDestroyMoreDoor = true;
        CanCutComboLock = true;
        CanCraftDoorKits = true;
        EnableVanillaRaiding = false;

        MoreDoorRaidTools = { "Hatchet", "Sledgehammer", "FirefighterAxe", "WoodAxe"};

        MoreDoorShantyDestroyTime = 180; //600
        MoreDoorDestroyTime = 600; //600
        MoreDoorMetalDestroyTime = 1200;    //1200
        MoreDoorBarricadeDestroyTime = 600;
        MoreDoorMetalBarricadeDestroyTime = 1200;
        MoreDoorDismantleTime = 25;
        MoreDoorToolDamage = 25;

        Save();
    }

    bool Get_CanDestroyMoreDoor()
    {
        return CanDestroyMoreDoor;
    }

    bool Get_CanCutComboLock()
    {
        return CanCutComboLock;
    }

    bool Get_CanCraftDoorKits()
    {
        return CanCraftDoorKits;
    }

    bool Get_EnableVanillaRaiding()
    {
        return EnableVanillaRaiding;
    }

    array<string> Get_MoreDoorRaidTools()
    {
        return MoreDoorRaidTools;
    }

    int Get_MoreDoorDestroyTime(string item)
    {
        int destroyTime = -1;
        switch( item )
        {
            case "MoreDoorSmallShanty":
                destroyTime = MoreDoorShantyDestroyTime;
                break;
            case "MoreDoorSmallMetal":
                destroyTime = MoreDoorMetalDestroyTime;
                break;
            case "MoreDoorBarricade":
                destroyTime = MoreDoorBarricadeDestroyTime;
                break;
            case "MoreDoorMetalBarricade":
                destroyTime = MoreDoorMetalBarricadeDestroyTime;
                break;
            default:
                destroyTime = MoreDoorDestroyTime;
                break;
        }
        return destroyTime;
    }

    int Get_MoreDoorDismantleTime()
    {
        return MoreDoorDismantleTime;
    }

    int Get_MoreDoorToolDamage()
    {
        return MoreDoorToolDamage;
    }
};

// vim:ft=enforce
