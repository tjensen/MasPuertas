class MoreDoorKitBase extends ItemBase
{
    ref protected EffectSound                       m_DeployLoopSound;
    //protected bool m_hasThings;

    string slotNails = "Material_Nails";
    string slotPlanks = "Material_WoodenPlanks";
    string slotMetal = "Material_MetalSheets";
    string slotLogs = "Material_WoodenLogs";
    string slotWire = "Material_MetalWire";

    int slot_id;
    int slot_id2;
    int slot_id3;
    int slot_id4;

    ItemBase slotCast;
    ItemBase slotCast2;
    ItemBase slotCast3;
    ItemBase slotCast4;

    int plankCost;
    int nailCost;
    int metalCost;
    int logCost;
    int wireCost;

    int j_Count;
    int j_Count2;
    int j_Count3;
    int j_Count4;

    void MoreDoorKitBase()
    {
        RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
    }

    bool hasTheGoodStuff()
    {
        return false;
    }

    string j_Door()
    {
        return "SodaCan_Spite";
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();

        if ( IsDeploySound() )
        {
            PlayDeploySound();
        }

        if ( CanPlayDeployLoopSound() )
        {
            PlayDeployLoopSound();
        }

        if ( m_DeployLoopSound && !CanPlayDeployLoopSound() )
        {
            StopDeployLoopSound();
        }
    }

    override bool CanPutInCargo( EntityAI parent )
    {
        if ( IsEmpty() )
        {
            return true;
        }
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return true;
    }

    override bool CanReceiveItemIntoCargo(EntityAI item)
    {
        return true;
    }

    override bool CanReleaseCargo(EntityAI attachment)
    {
        return true;
    }

    void ReturnGoodsFromDismantle()
    {
        ItemBase j_goods = ItemBase.Cast(GetInventory().CreateAttachment("WoodenPlank" ));
        j_goods.SetQuantity(10);
        ItemBase j_goods2 = ItemBase.Cast(GetInventory().CreateAttachment("Nail" ));
        j_goods2.SetQuantity(10);
        GetInventory().CreateAttachment( "MetalWire" );
    }

    //================================================================
    // ADVANCED PLACEMENT
    //================================================================

    override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
    {
        super.OnPlacementComplete(player);

        if (GetGame().IsServer())
        {
            this.Delete();
        }

        SetIsDeploySound(true);
    }

    override bool CanBePlaced(Man player, vector position)
    {
        if (!hasTheGoodStuff())
        {
            return false;
        }

        return super.CanBePlaced(player, position);
    }

    override bool IsDeployable()
    {
        return true;
    }

    override string GetDeploySoundset()
    {
        return "putDown_FenceKit_SoundSet";
    }

    override string GetLoopDeploySoundset()
    {
        return "BarbedWire_Deploy_loop_SoundSet";
    }

    void PlayDeployLoopSound()
    {
        if ( GetGame().IsMultiplayer() && GetGame().IsClient() || !GetGame().IsMultiplayer() )
        {
            m_DeployLoopSound = SEffectManager.PlaySound( GetLoopDeploySoundset(), GetPosition() );
        }
    }

    void StopDeployLoopSound()
    {
        if ( GetGame().IsMultiplayer() && GetGame().IsClient() || !GetGame().IsMultiplayer() )
        {
            m_DeployLoopSound.SoundStop();
            delete m_DeployLoopSound;
        }
    }

    override bool IsContainer()
    {
        return true;
    }

    // override bool IsHeavyBehaviour()
    // {
    //  return true;
    // }

    // override bool IsTwoHandedBehaviour()
    // {
    //  return true;
    // }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionTogglePlaceObject);
        AddAction(ActionDeployObject);
    }
};

class MoreDoorVaultKit extends MoreDoorKitBase
{
    override bool hasTheGoodStuff()
    {
        return true;
    }

    override string j_Door()
    {
        if ( hasTheGoodStuff() )
        {
            return "MoreDoorVault";
        }
        return "MoreDoorVaultKit";
    }
};

class MoreDoorSmallKit extends MoreDoorKitBase
{
    override bool hasTheGoodStuff()
    {
        plankCost = 10;
        nailCost = 25;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
        slot_id3 = InventorySlots.GetSlotIdFromString(slotWire);
        slotCast = ItemBase.Cast( GetInventory().FindAttachment(slot_id) );
        slotCast2 = ItemBase.Cast( GetInventory().FindAttachment(slot_id2) );
        slotCast3 = ItemBase.Cast( GetInventory().FindAttachment(slot_id3) );
        j_Count = slotCast.GetQuantity();
        j_Count2 = slotCast2.GetQuantity();

        if( slotCast != NULL && slotCast2 != NULL && slotCast3 != NULL )
        {
            if( j_Count >= nailCost && j_Count2 >= plankCost )
            {
                return true;
            }
            return false;
        }
        return false;
    }

    override string j_Door()
    {
        if ( hasTheGoodStuff() )
        {
            return "MoreDoorSmall";
        }
        return "MoreDoorSmallKit";
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
};

class MoreDoorSmallMetalKit extends MoreDoorKitBase
{
    override bool hasTheGoodStuff()
    {
        plankCost = 20;
        nailCost = 75;
        metalCost = 5;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
        slot_id3 = InventorySlots.GetSlotIdFromString(slotWire);
        slot_id4 = InventorySlots.GetSlotIdFromString(slotMetal);
        slotCast = ItemBase.Cast( GetInventory().FindAttachment(slot_id) );
        slotCast2 = ItemBase.Cast( GetInventory().FindAttachment(slot_id2) );
        slotCast3 = ItemBase.Cast( GetInventory().FindAttachment(slot_id3) );
        slotCast4 = ItemBase.Cast( GetInventory().FindAttachment(slot_id4) );

        j_Count = slotCast.GetQuantity();
        j_Count2 = slotCast2.GetQuantity();
        j_Count4 = slotCast4.GetQuantity();

        if( slotCast != NULL && slotCast2 != NULL && slotCast3 != NULL && slotCast4 != NULL)
        {
            if( j_Count >= nailCost && j_Count2 >= plankCost && j_Count4 >=metalCost )
            {
                return true;
            }
            return false;
        }
        return false;
    }

    override string j_Door()
    {
        if ( hasTheGoodStuff() )
        {
            return "MoreDoorSmallMetal";
        }
        return "MoreDoorSmallMetalKit";
    }
};

class MoreDoorSmallShantyKit extends MoreDoorKitBase
{
    override bool hasTheGoodStuff()
    {
        plankCost = 5;
        nailCost = 25;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
        slotCast = ItemBase.Cast( GetInventory().FindAttachment(slot_id) );
        slotCast2 = ItemBase.Cast( GetInventory().FindAttachment(slot_id2) );
        j_Count = slotCast.GetQuantity();
        j_Count2 = slotCast2.GetQuantity();

        if( slotCast != NULL && slotCast2 != NULL )
        {
            if( j_Count >= nailCost && j_Count2 >= plankCost )
            {
                return true;
            }
            return false;
        }
        return false;
    }

    override string j_Door()
    {
        if ( hasTheGoodStuff() )
        {
            return "MoreDoorSmallShanty";
        }
        return "MoreDoorSmallShantyKit";
    }

    override void ReturnGoodsFromDismantle()
    {
        ItemBase j_goods = ItemBase.Cast(GetInventory().CreateAttachment("WoodenPlank" ));
        j_goods.SetQuantity(3);
    }
};

class MoreDoorBarricadeKit extends MoreDoorKitBase
{
    override bool hasTheGoodStuff()
    {
        plankCost = 3;
        nailCost = 10;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
        slotCast = ItemBase.Cast( GetInventory().FindAttachment(slot_id) );
        slotCast2 = ItemBase.Cast( GetInventory().FindAttachment(slot_id2) );
        j_Count = slotCast.GetQuantity();
        j_Count2 = slotCast2.GetQuantity();

        if( slotCast != NULL && slotCast2 != NULL )
        {
            if( j_Count >= nailCost && j_Count2 >= plankCost )
            {
                return true;
            }
            return false;
        }
        return false;
    }

    override string j_Door()
    {
        if ( hasTheGoodStuff() )
        {
            return "MoreDoorBarricade";
        }
        return "MoreDoorBarricadeKit";
    }

    override void ReturnGoodsFromDismantle()
    {
        ItemBase j_goods = ItemBase.Cast(GetInventory().CreateAttachment("WoodenPlank" ));
        j_goods.SetQuantity(3);
    }
};

// vim:ft=enforce
