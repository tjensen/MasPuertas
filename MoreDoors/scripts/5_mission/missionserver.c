modded class MissionServer
{
    void MissionServer()
    {
        PrintFormat("Loaded MasPuertas %1", MAS_PUERTAS_VERSION);

        GetRPCManager().AddRPC("MoreDoorConfig", "GetMoreDoorCfg", this, SingeplayerExecutionType.Server);
    }

    override void OnInit()
    {
        super.OnInit();

        Print("[MasPuertas] Server Cfg loading...");

        auto moreDoorConfig = new MoreDoorConfig();
        SetMoreDoorConfig(moreDoorConfig);
    }

    void GetMoreDoorCfg(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Server && sender != null)
        {
            auto config = CurrentMoreDoorConfig();

            Print("[MasPuertas] MissionServer --> Sending instance of cfg to client: " + sender.GetName());
            GetRPCManager().SendRPC(
                "MoreDoorConfig", "MoreDoorStoreConfig", new Param1<MoreDoorConfig>(config), true,
                sender);
        }
    }
};

// vim:ft=enforce
