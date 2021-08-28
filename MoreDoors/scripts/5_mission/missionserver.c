modded class MissionServer
{
    private ref MoreDoorConfig m_MoreDoorConfig;

    void MissionServer()
    {
        PrintFormat("Loaded MasPuertas %1", MAS_PUERTAS_VERSION);

        GetRPCManager().AddRPC("MoreDoorConfig", "GetMoreDoorCfg", this, SingeplayerExecutionType.Server);
    }

    override void OnInit()
    {
        super.OnInit();

        Print("[MasPuertas] Server Cfg loading...");

        m_MoreDoorConfig = new MoreDoorConfig();
        g_Game.SetMoreDoorConfig( m_MoreDoorConfig );
    }

    void GetMoreDoorCfg(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Server && sender != null) //Verify that sender is still around so we don't send a null RPC ( sending and RPC with null target will send it to all players in the session )
        {
            Print("[MasPuertas] MissionServer --> Sending instance of cfg to client: " + sender.GetName());
            GetRPCManager().SendRPC("MoreDoorConfig", "MoreDoorStoreConfig", new Param1<MoreDoorConfig>( m_MoreDoorConfig ), true, sender);
        }
    }
};

// vim:ft=enforce
