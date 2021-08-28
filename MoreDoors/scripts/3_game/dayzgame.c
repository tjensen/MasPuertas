modded class DayZGame
{
    private ref MoreDoorConfig m_MoreDoorConfig;

    MoreDoorConfig GetMoreDoorConfig()
    {
        if (m_MoreDoorConfig)
        {
            return m_MoreDoorConfig;
        }

        Print("[MasPuertas] DayZGame --> Cannot Locate Config File...");
        return null;
    }

    void SetMoreDoorConfig(MoreDoorConfig cfg)
    {
        m_MoreDoorConfig = cfg;
    }
};

// vim:ft=enforce
