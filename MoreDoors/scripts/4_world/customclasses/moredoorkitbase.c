class MoreDoorKitBase extends ItemBase
{
    ref protected EffectSound m_DeployLoopSound;

    string slotNails = "Material_Nails";
    string slotPlanks = "Material_WoodenPlanks";
    string slotMetal = "Material_MetalSheets";
    string slotLogs = "Material_WoodenLogs";
    string slotWire = "Material_MetalWire";

    int slot_id;
    int slot_id2;
    int slot_id3;
    int slot_id4;

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

    bool HasRequiredComponents()
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

    private bool DropExcessQuantity(Man player, ItemBase item, int cost)
    {
        if (item && item.GetQuantity() > cost)
        {
            item.AddQuantity(-cost);

            return GetInventory().DropEntity(InventoryMode.SERVER, player, item);
        }

        return false;
    }

    void DropExcessComponents(Man player)
    {
        DropExcessQuantity(
            player, ItemBase.Cast(GetInventory().FindAttachmentByName(slotNails)), nailCost);
        DropExcessQuantity(
            player, ItemBase.Cast(GetInventory().FindAttachmentByName(slotPlanks)), plankCost);
        DropExcessQuantity(
            player, ItemBase.Cast(GetInventory().FindAttachmentByName(slotMetal)), metalCost);
        DropExcessQuantity(
           player, ItemBase.Cast(GetInventory().FindAttachmentByName(slotLogs)), logCost);
        DropExcessQuantity(
           player, ItemBase.Cast(GetInventory().FindAttachmentByName(slotWire)), wireCost);
    }

    //================================================================
    // ADVANCED PLACEMENT
    //================================================================

    override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
    {
        super.OnPlacementComplete(player);

        if (GetGame().IsServer())
        {
            DropExcessComponents(player);

            GetGame().ObjectDelete(this);
        }

        SetIsDeploySound(true);
    }

    override bool CanBePlaced(Man player, vector position)
    {
        if (!HasRequiredComponents())
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

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionTogglePlaceObject);
        AddAction(ActionDeployObject);
    }
};

class MoreDoorVaultKit extends MoreDoorKitBase
{
    override bool HasRequiredComponents()
    {
        return true;
    }

    override string j_Door()
    {
        if (HasRequiredComponents())
        {
            return "MoreDoorVault";
        }

        return "MoreDoorVaultKit";
    }
};

class MoreDoorSmallKit extends MoreDoorKitBase
{
    void MoreDoorSmallKit()
    {
        plankCost = 10;
        nailCost = 25;
        wireCost = 1;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
        slot_id3 = InventorySlots.GetSlotIdFromString(slotWire);
    }

    override bool HasRequiredComponents()
    {
        auto slotCast = ItemBase.Cast(GetInventory().FindAttachment(slot_id));
        auto slotCast2 = ItemBase.Cast(GetInventory().FindAttachment(slot_id2));
        auto slotCast3 = ItemBase.Cast(GetInventory().FindAttachment(slot_id3));

        if (slotCast != NULL && slotCast2 != NULL && slotCast3 != NULL)
        {
            j_Count = slotCast.GetQuantity();
            j_Count2 = slotCast2.GetQuantity();

            if (j_Count >= nailCost && j_Count2 >= plankCost)
            {
                return true;
            }

            return false;
        }

        return false;
    }

    override string j_Door()
    {
        if (HasRequiredComponents())
        {
            return "MoreDoorSmall";
        }

        return "MoreDoorSmallKit";
    }
};

class MoreDoorSmallMetalKit extends MoreDoorKitBase
{
    void MoreDoorSmallMetalKit()
    {
        plankCost = 20;
        nailCost = 75;
        metalCost = 5;
        wireCost = 1;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
        slot_id3 = InventorySlots.GetSlotIdFromString(slotWire);
        slot_id4 = InventorySlots.GetSlotIdFromString(slotMetal);
    }

    override bool HasRequiredComponents()
    {
        auto slotCast = ItemBase.Cast(GetInventory().FindAttachment(slot_id));
        auto slotCast2 = ItemBase.Cast(GetInventory().FindAttachment(slot_id2));
        auto slotCast3 = ItemBase.Cast(GetInventory().FindAttachment(slot_id3));
        auto slotCast4 = ItemBase.Cast(GetInventory().FindAttachment(slot_id4));

        if (slotCast != NULL && slotCast2 != NULL && slotCast3 != NULL && slotCast4 != NULL)
        {
            j_Count = slotCast.GetQuantity();
            j_Count2 = slotCast2.GetQuantity();
            j_Count4 = slotCast4.GetQuantity();

            if (j_Count >= nailCost && j_Count2 >= plankCost && j_Count4 >=metalCost)
            {
                return true;
            }

            return false;
        }

        return false;
    }

    override string j_Door()
    {
        if (HasRequiredComponents())
        {
            return "MoreDoorSmallMetal";
        }

        return "MoreDoorSmallMetalKit";
    }
};

class MoreDoorSmallShantyKit extends MoreDoorKitBase
{
    void MoreDoorSmallShantyKit()
    {
        plankCost = 5;
        nailCost = 25;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
    }

    override bool HasRequiredComponents()
    {
        auto slotCast = ItemBase.Cast(GetInventory().FindAttachment(slot_id));
        auto slotCast2 = ItemBase.Cast(GetInventory().FindAttachment(slot_id2));

        if (slotCast != NULL && slotCast2 != NULL)
        {
            j_Count = slotCast.GetQuantity();
            j_Count2 = slotCast2.GetQuantity();

            if (j_Count >= nailCost && j_Count2 >= plankCost)
            {
                return true;
            }

            return false;
        }

        return false;
    }

    override string j_Door()
    {
        if (HasRequiredComponents())
        {
            return "MoreDoorSmallShanty";
        }

        return "MoreDoorSmallShantyKit";
    }

    override void ReturnGoodsFromDismantle()
    {
        ItemBase j_goods = ItemBase.Cast(GetInventory().CreateAttachment("WoodenPlank"));
        j_goods.SetQuantity(3);
    }
};

class MoreDoorBarricadeKit extends MoreDoorKitBase
{
    void MoreDoorBarricadeKit()
    {
        plankCost = 3;
        nailCost = 10;

        slot_id = InventorySlots.GetSlotIdFromString(slotNails);
        slot_id2 = InventorySlots.GetSlotIdFromString(slotPlanks);
    }

    override bool HasRequiredComponents()
    {
        auto slotCast = ItemBase.Cast(GetInventory().FindAttachment(slot_id));
        auto slotCast2 = ItemBase.Cast(GetInventory().FindAttachment(slot_id2));

        if (slotCast != NULL && slotCast2 != NULL)
        {
            j_Count = slotCast.GetQuantity();
            j_Count2 = slotCast2.GetQuantity();

            if (j_Count >= nailCost && j_Count2 >= plankCost)
            {
                return true;
            }

            return false;
        }
        return false;
    }

    override string j_Door()
    {
        if (HasRequiredComponents())
        {
            return "MoreDoorBarricade";
        }

        return "MoreDoorBarricadeKit";
    }

    override void ReturnGoodsFromDismantle()
    {
        ItemBase j_goods = ItemBase.Cast(GetInventory().CreateAttachment("WoodenPlank"));
        j_goods.SetQuantity(3);
    }
};

// vim:ft=enforce
