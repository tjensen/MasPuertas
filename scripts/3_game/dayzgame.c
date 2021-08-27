modded class DayZGame
{
    private ref MoreDoorConfig m_MoreDoorConfig;

    ref MoreDoorConfig GetMoreDoorConfig()
    {
        if (m_MoreDoorConfig)
        {
            return m_MoreDoorConfig;
        }

        Print("[MoreDoors] DayZGame --> Cannot Locate MoreDoors Config File...");
	    return null;
    }

    void SetMoreDoorConfig(ref MoreDoorConfig cfg)
	{
		m_MoreDoorConfig = cfg;
	}
}