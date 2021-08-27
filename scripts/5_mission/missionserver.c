modded class MissionServer
{
    private ref MoreDoorConfig m_MoreDoorConfig;

    void MissionServer()
    {
        GetRPCManager().AddRPC("MoreDoorConfig", "GetMoreDoorCfg", this, SingeplayerExecutionType.Server);
    }

    override void OnInit()
    {
        super.OnInit();
        
        Print("[MoreDoorConfig] Server Cfg loading..."); 
       
        m_MoreDoorConfig = new MoreDoorConfig();
        g_Game.SetMoreDoorConfig( m_MoreDoorConfig );
    }

    void GetMoreDoorCfg(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server && sender != null) //Verify that sender is still around so we don't send a null RPC ( sending and RPC with null target will send it to all players in the session )
        {
            Print("[MoreDoors] MissionServer --> Sending instance of cfg to client: " + sender.GetName());
            GetRPCManager().SendRPC("MoreDoorConfig", "MoreDoorStoreConfig", new Param1<ref MoreDoorConfig>( m_MoreDoorConfig ), true, sender);
        }
    }

};
