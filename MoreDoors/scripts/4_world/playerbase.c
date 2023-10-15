modded class PlayerBase
{
    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);

        AddAction(ActionDestroyMoreDoor, InputActionMap);
    }

    override bool CanClimb(int climbType, SHumanCommandClimbResult climbRes)
    {
        if (climbType == 2 && climbRes.m_GrabPointParent.IsInherited(MoreDoorBase))
        {
            return false;
        }

        return super.CanClimb(climbType, climbRes);
    }

    override void PlacingStartLocal(ItemBase item)
    {
        super.PlacingStartLocal(item);

        if (item && item.IsInherited(MoreDoorKitBase))
        {
            GetItemAccessor().HideItemInHands(true);
        }
    }

    override void PlacingCancelLocal()
    {
        super.PlacingCancelLocal();

        GetItemAccessor().HideItemInHands(false);
    }
};

modded class ModItemRegisterCallbacks
{
    override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterHeavy(pType, pBehavior);

        pType.AddItemInHandsProfileIK(
            "MoreDoorKitBase", "dz/anims/workspaces/player/player_main/player_main_heavy.asi",
            pBehavior, "dz/anims/anm/player/ik/heavy/wooden_crate.anm");
    }
};

// vim:ft=enforce
