modded class MissionBaseWorld
{
    private ref MoreDoorConfig m_MoreDoorConfig;
    private ref ScriptInvoker m_OnMoreDoorConfigUpdate = new ScriptInvoker();

    static MoreDoorConfig GetMoreDoorConfig()
    {
        auto mission = MissionBaseWorld.Cast(GetGame().GetMission());

        return mission.CurrentMoreDoorConfig();
    }

    MoreDoorConfig CurrentMoreDoorConfig()
    {
        if (m_MoreDoorConfig)
        {
            return m_MoreDoorConfig;
        }

        return null;
    }

    void SetMoreDoorConfig(MoreDoorConfig config)
    {
        m_MoreDoorConfig = config;

        m_OnMoreDoorConfigUpdate.Invoke(config);
    }

    void AddMoreDoorItem(MoreDoorBase item)
    {
        m_OnMoreDoorConfigUpdate.Insert(item.OnConfigUpdate);
    }

    void RemoveMoreDoorItem(MoreDoorBase item)
    {
        m_OnMoreDoorConfigUpdate.Remove(item.OnConfigUpdate);
    }
};

// vim:ft=enforce
