class MoreDoorBase extends Fence
{
    private ref Timer m_deleteTimer = new Timer();

    void MoreDoorBase()
    {
        auto config = MissionBaseWorld.GetMoreDoorConfig();
        if (config)
        {
            OnConfigUpdate(config);
        }
        else
        {
            MissionBaseWorld.Cast(GetGame().GetMission()).AddMoreDoorItem(this);
        }

        SetGateState(GATE_STATE_FULL);
        SetBaseState(true);
    }

    void ~MoreDoorBase()
    {
        if (GetGame() && GetGame().GetMission())
        {
            MissionBaseWorld.Cast(GetGame().GetMission()).RemoveMoreDoorItem(this);
        }
    }

    override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

        if (GetGame().IsMultiplayer() && !GetGame().IsServer())
        {
            return;
        }

        if (newLevel == GameConstants.STATE_RUINED)
        {
            HandleDropAttachment(GetCombinationLock());

            OnDestroyed();
        }
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == ATTACHMENT_SLOT_COMBINATION_LOCK)
        {
            CloseFence();
        }
    }

    void OnDestroyed()
    {
        m_deleteTimer.Run(15, this, "DeleteSave");
    }

    void OnConfigUpdate(MoreDoorConfig config)
    {
        SetAllowDamage(config.Get_EnableVanillaRaiding());
    }

    bool HasGate()
    {
        return true;
    }

    override bool HasHinges()
    {
        return true;
    }

    bool IsMoreDoor()
    {
        return true;
    }

    string j_moreDoorKit()
    {
        return "MoreDoorSmallKit";
    }

    bool AllowDismantle()
    {
        return true;
    }

    bool AllowDestruction()
    {
        return true;
    }

    bool IsMetalDoor()
    {
        return false;
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (IsOpened() || InventorySlots.GetSlotName(slotId) != ATTACHMENT_SLOT_COMBINATION_LOCK)
        {
            return false;
        }

        return true;
    }

    bool CanBeInteractedWithBy(EntityAI entity)
    {
        return vector.Distance(GetPosition(), entity.GetPosition()) <= UAMaxDistances.DEFAULT;
    }

    override bool CanCloseFence()
    {
        if ( IsOpened() )
        {
            return true;
        }

        return false;
    }

    override void OpenFence()
    {
        //server or single player
        if (GetGame().IsServer())
        {
            SetAnimationPhase("Wall_Gate_Rotate", 2);
            SetOpenedState(true);

            //regenerate navmesh
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
                UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false);

            //synchronize
            SynchronizeBaseState();
        }

        //client or single player
        if (!GetGame().IsDedicatedServer())
        {
            //play sound
            SoundGateOpenStart();
        }
    }

    override void CloseFence()
    {
        //server or single player
        if (GetGame().IsServer())
        {
            SetAnimationPhase("Wall_Gate_Rotate", 0);
            SetOpenedState(false);

            //regenerate navmesh
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
                UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false);

            //synchronize
            SynchronizeBaseState();
        }

        //client or single player
        if (!GetGame().IsDedicatedServer())
        {
            //play sound
            SoundGateCloseStart();
        }
    }

    override void SetPartsAfterStoreLoad()
    {
        //update server data
        SetPartsFromSyncData();

        //set base state
        SetBaseState(true);

        //synchronize after load
        SynchronizeBaseState();
    }

    override bool NameOverride(out string output)
    {
        return false;
    }

    override bool CanDisplayAttachmentSlot( string slot_name )
    {
        return true;
    }

    override bool CanDisplayAttachmentCategory(string category_name)
    {
        if (category_name != "Base")
        {
            return false;
        }

        return super.CanDisplayAttachmentCategory(category_name);
    }

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionDialCombinationLockOnMoreDoor);
        AddAction(ActionNextCombinationLockDialOnMoreDoor);
        AddAction(ActionOpenMoreDoor);
        AddAction(ActionCloseMoreDoor);
        RemoveAction(ActionFoldBaseBuildingObject);
        RemoveAction(ActionOpenFence);
        RemoveAction(ActionCloseFence);
    }
};

class MoreDoorVault extends MoreDoorBase
{
    const string SOUND_SAFE_OPEN_START      = "MoreDoor_doorMetalSlideLargeOpen_SoundSet";
    const string SOUND_SAFE_CLOSE_START     = "MoreDoor_doorMetalSlideLargeClose_SoundSet";
    const string SOUND_SAFE_CLOSE_END       = "MoreDoor_doorMetalGateClose_SoundSet";

    override bool CanBeInteractedWithBy(EntityAI entity)
    {
        return vector.Distance(GetPosition(), entity.GetPosition()) <= (UAMaxDistances.DEFAULT * 2);
    }

    override string j_moreDoorKit()
    {
        return "MoreDoorVaultKit";
    }

    override bool AllowDestruction()
    {
        return false;
    }

    override protected void SoundGateOpenStart()
    {
        PlaySoundSet( m_SoundGate_Start, SOUND_SAFE_OPEN_START, 0.1, 0.1 );
    }

    override protected void SoundGateCloseStart()
    {
        PlaySoundSet( m_SoundGate_Start, SOUND_SAFE_CLOSE_START, 0.1, 0.1 );
    }

    override protected void SoundGateCloseEnd()
    {
        PlaySoundSet( m_SoundGate_End, SOUND_SAFE_CLOSE_END, 0.1, 0.1 );
    }

    override bool AllowDismantle()
    {
        return false;
    }
};

class MoreDoorSmall extends MoreDoorBase
{
    override string j_moreDoorKit()
    {
        return "MoreDoorSmallKit";
    }
};

class MoreDoorSmallShanty extends MoreDoorBase
{
    override string j_moreDoorKit()
    {
        return "MoreDoorSmallShantyKit";
    }
};

class MoreDoorSmallMetal extends MoreDoorBase
{
    override string j_moreDoorKit()
    {
        return "MoreDoorSmallMetalKit";
    }

    override bool IsMetalDoor()
    {
        return true;
    }
};

class MoreDoorBarricade extends MoreDoorBase
{
    override string j_moreDoorKit()
    {
        return "MoreDoorBarricadeKit";
    }

    override void SetActions()
    {
    }

    override bool CanDisplayAttachmentCategory(string category_name)
    {
        return true;
    }

    bool hasTheGoodStuff()
    {
        int metalCost = 3;

        int slot_id = InventorySlots.GetSlotIdFromString("Material_MetalSheets");
        ItemBase slotCast = ItemBase.Cast( GetInventory().FindAttachment(slot_id) );

        if( slotCast != NULL )
        {
            int j_Count = slotCast.GetQuantity();
            if( j_Count >= metalCost )
            {
                return true;
            }
            return false;
        }
        return false;
    }

    override void UpdateAttachmentPhysics( string slot_name, bool is_locked )
    {
    }

    override void UpdateAttachmentVisuals( string slot_name, bool is_locked )
    {
    }
};

class MoreDoorMetalBarricade extends MoreDoorBase
{
    override string j_moreDoorKit()
    {
        return "MoreDoorBarricadeKit";
    }

    override void EEItemDetached ( EntityAI item, string slot_name )
    {
    }

    override void SetActions()
    {
    }
};

class MoreDoorSafe extends MoreDoorBase
{
    const string SOUND_SAFE_OPEN_START      = "MoreDoor_doorMetalSmallOpen_SoundSet";
    const string SOUND_SAFE_CLOSE_START     = "MoreDoor_doorMetalSmallClose_SoundSet";
    const string SOUND_SAFE_CLOSE_END       = "combinationlock_close_SoundSet";

    override void OnDestroyed()
    {
        MiscGameplayFunctions.DropAllItemsInInventoryInBounds(this, "0.2 0.8 0.3");
    }

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionTakeItemToHands);
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        if (!IsOpened() && GetNumberOfItems() == 0 && GetInventory().AttachmentCount() == 0)
        {
            return true;
        }
        return false;
    }

    override bool IsTwoHandedBehaviour()
    {
        return true;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!IsOpened() && GetNumberOfItems() == 0 && GetInventory().AttachmentCount() == 0)
        {
            return true;
        }
        return false;
    }

    override bool CanDisplayCargo()
    {
        return IsOpened();
    }

    override bool IsPlayerInside(PlayerBase player, string selection)
    {
        return true;
    }

    override bool CanRemoveFromCargo(EntityAI parent)
    {
        return true;
    }

    override void AfterStoreLoad()
    {
        if (IsOpened())
        {
            OpenFence();
        }
        else
        {
            CloseFence();
        }

        UpdateVisuals();
    }

    override bool AllowDestruction()
    {
        return false;
    }

    override void EEInit()
    {
        super.EEInit();

        if (IsOpened())
        {
            OpenFence();
        }
        else
        {
            CloseFence();
        }
    }

    override bool AllowDismantle()
    {
        return false;
    }

    override protected void SoundGateOpenStart()
    {
        PlaySoundSet( m_SoundGate_Start, SOUND_SAFE_OPEN_START, 0.1, 0.1 );
    }

    override protected void SoundGateCloseStart()
    {
        PlaySoundSet( m_SoundGate_Start, SOUND_SAFE_CLOSE_START, 0.1, 0.1 );
    }

    override protected void SoundGateCloseEnd()
    {
        PlaySoundSet( m_SoundGate_End, SOUND_SAFE_CLOSE_END, 0.1, 0.1 );
    }
};

// vim:ft=enforce
