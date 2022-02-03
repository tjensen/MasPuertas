class MoreDoorBase extends Fence
{
    //protected bool            m_DismantleDisabled;

    // void MoreDoorBase()
    // {
    //  RegisterNetSyncVariableBool( "m_DismantleDisabled" );
    // }

    // bool DismantleDisabled()
    // {
    //  return m_DismantleDisabled;
    // }

    // void SetDismantleAbility( bool state )
    // {
    //  m_DismantleDisabled = state;
    //  SetSynchDirty();
    // }

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

    override void AfterStoreLoad()
    {
        SetGateState( true );
        SetBaseState( true );
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
        if ( GetGame().IsServer() )
        {
            SetAnimationPhase( "Wall_Gate_Rotate",                  2 );
            SetOpenedState( true );

            //regenerate navmesh
            GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false );

            //synchronize
            SynchronizeBaseState();
        }

        //client or single player
        if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
        {
            //play sound
            SoundGateOpenStart();
        }
    }

    override void SetPartsAfterStoreLoad()
    {
        //update server data
        SetPartsFromSyncData();

        //set base state
        SetBaseState( true ) ;

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

    override bool CanDisplayAttachmentCategory( string category_name )
    {
        return true;
    }

    override bool CanReceiveAttachment( EntityAI attachment, int slotId )
    {
        return true;
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

    // override void OnStoreSave( ParamsWriteContext ctx )
    // {
    //  super.OnStoreSave( ctx );

    //  //write
    //  ctx.Write( m_DismantleDisabled );
    // }

    // override bool OnStoreLoad( ParamsReadContext ctx, int version )
    // {
    //  if ( !super.OnStoreLoad( ctx, version ) )
    //      return false;

    //  //is opened
    //  if ( !ctx.Read( m_IsOpened ) )
    //  {
    //      m_IsOpened = false;
    //      return false;
    //  }

    //  if ( !ctx.Read( m_DismantleDisabled ) )
    //  {
    //      m_DismantleDisabled = false;
    //      return false;
    //  }

    //  return true;
    // }

    // override void EEItemDetached ( EntityAI item, string slot_name )
    // {
    //  super.EEItemDetached ( item, slot_name );

    //  if(DismantleDisabled())
    //  {
    //      SetDismantleAbility(false);
    //  }
    // }

};

class MoreDoorVault extends MoreDoorBase
{
    const string SOUND_SAFE_OPEN_START      = "MoreDoor_doorMetalSlideLargeOpen_SoundSet";
    const string SOUND_SAFE_CLOSE_START     = "MoreDoor_doorMetalSlideLargeClose_SoundSet";
    const string SOUND_SAFE_CLOSE_END       = "MoreDoor_doorMetalGateClose_SoundShader";

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

    override void SetActions()
    {
        super.SetActions();

        RemoveAction(ActionOpenMoreDoor);
        AddAction(ActionOpenFence);
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

    // override bool CanReceiveAttachment( EntityAI attachment, int slotId )
    // {
    //  int slot_id = InventorySlots.GetSlotIdFromString("Material_MetalSheets");
    //  ItemBase slotCast = ItemBase.Cast( GetInventory().FindAttachment(slot_id) );
    //  ItemBase m_attachment = ItemBase.Cast(attachment);

    //  int j_Count = slotCast.GetQuantity();
    //  int attachmentQuantity = m_attachment.GetQuantity();
    //  int remainingSlots = 3 - attachmentQuantity;

    //  if ( j_Count >= 3 || attachmentQuantity >= remainingSlots )
    //  {
    //      return false;
    //  }

    //  return true;
    // }

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
    const string SOUND_SAFE_OPEN_START          = "MoreDoor_doorMetalSmallOpen_SoundSet";
    const string SOUND_SAFE_CLOSE_START     = "MoreDoor_doorMetalSmallClose_SoundSet";
    const string SOUND_SAFE_CLOSE_END       = "combinationlock_close_SoundSet";

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionTakeItemToHands);
    }

    override bool CanDisplayAttachmentCategory(string category_name)
    {
        if (category_name != "Attachments")
        {
            return false;
        }

        return super.CanDisplayAttachmentCategory(category_name);
    }

    override bool CanPutInCargo( EntityAI parent )
    {
        if ( GetNumberOfItems() == 0 && !IsOpened() && !IsLocked() )
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
        if ( GetNumberOfItems() == 0 && !IsOpened() && !IsLocked() )
        {
            return true;
        }
        return false;
    }

    override bool IsPlayerInside( PlayerBase player, string selection )
    {
        return true;
    }

    override bool CanRemoveFromCargo( EntityAI parent )
    {
        return true;
    }

    override void OpenFence()
    {
        super.OpenFence();
        GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
    }

    override void CloseFence()
    {
        super.CloseFence();
        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);

    }

    override void AfterStoreLoad()
    {
        SetGateState( true );
        SetBaseState( true );
        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
    }

    override void EEItemAttached ( EntityAI item, string slot_name )
    {
        super.EEItemAttached ( item, slot_name );

        if ( slot_name == "Att_CombinationLock" )
        {
            CloseFence();
        }
    }

    override void EEItemDetached ( EntityAI item, string slot_name )
    {
        super.EEItemDetached ( item, slot_name );

        if ( slot_name == "Att_CombinationLock" )
        {
            OpenFence();
        }

    }

    override bool AllowDestruction()
    {
        return false;
    }

    override void EEInit()
    {
        super.EEInit();

        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
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
