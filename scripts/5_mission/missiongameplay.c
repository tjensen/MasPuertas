modded class MissionGameplay
{
	//Instead of storing the instance of the config in a "global static" place, placing it here is better for two reasons, 
	//1st DayZGame is too early meaning that no RPC calls will ever get to it, 
	//but missionGameplay is perfect as its the entry point of a client when joining a session. 
	//RPCs that you init here work perfectly. 2nd reason is cuz this class gets reloaded when a player rejoins a session, 
	//meaning a config instance is grabbed fresh once again without the need of client restart.

	void MissionGameplay()
	{
		GetRPCManager().AddRPC("MoreDoorConfig", "MoreDoorStoreConfig", this, SingeplayerExecutionType.Client); //Add this RPC as listner to the catch the cfg sent from server.
		GetRPCManager().SendRPC("MoreDoorConfig", "GetMoreDoorCfg", null, true, null); //send RPC to server once this class starts to get cfg. Identity is null in this case becuase we are sending an RPC from client, clients can't target specific identities
	}

	void MoreDoorStoreConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        ref Param1<ref MoreDoorConfig> data;
        if (type == CallType.Client)
		{
			if (!ctx.Read(data)) return; //Return if failed to read data for somereason.

			g_Game.SetMoreDoorConfig( data.param1 );
			Print("[MoreDoors] MissionGameplay --> Got instance of cfg: " + data.param1);
		}
    }
};
