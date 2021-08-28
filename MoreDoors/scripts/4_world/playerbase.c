modded class PlayerBase
{
	override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);

		AddAction(ActionDestroyMoreDoor, InputActionMap);
	}
};

modded class ModItemRegisterCallbacks
{
    override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterHeavy( pType, pBehavior );     
        pType.AddItemInHandsProfileIK("MoreDoorKitBase", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/heavy/wooden_crate.anm");
    }
};  