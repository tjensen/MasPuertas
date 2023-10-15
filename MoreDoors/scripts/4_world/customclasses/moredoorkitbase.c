class MoreDoorKitBase extends ItemBase
{
    ref protected EffectSound m_DeployLoopSound;

    const string SLOT_NAILS = "Material_Nails";
    const string SLOT_PLANKS = "Material_WoodenPlanks";
    const string SLOT_METAL = "Material_MetalSheets";
    const string SLOT_WIRE = "Material_MetalWire";

    int plankCost;
    int nailCost;
    int metalCost;
    int wireCost;

    void MoreDoorKitBase()
    {
        RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
    }

    void ~MoreDoorKitBase()
    {
        SEffectManager.DestroyEffect(m_DeployLoopSound);
    }

    private bool HasRequiredComponent(ItemBase item, int cost)
    {
        return cost == 0 || (item && item.GetQuantity() >= cost);
    }

    bool HasRequiredComponents()
    {
        if (!HasRequiredComponent(
                ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_NAILS)), nailCost))
        {
            return false;
        }

        if (!HasRequiredComponent(
                ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_PLANKS)), plankCost))
        {
            return false;
        }

        if (!HasRequiredComponent(
                ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_METAL)), metalCost))
        {
            return false;
        }

        if (!HasRequiredComponent(
                ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_WIRE)), wireCost))
        {
            return false;
        }

        return true;
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
            player, ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_NAILS)), nailCost);
        DropExcessQuantity(
            player, ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_PLANKS)), plankCost);
        DropExcessQuantity(
            player, ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_METAL)), metalCost);
        DropExcessQuantity(
           player, ItemBase.Cast(GetInventory().FindAttachmentByName(SLOT_WIRE)), wireCost);
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
        if (!GetGame().IsDedicatedServer())
        {
            if (!m_DeployLoopSound || !m_DeployLoopSound.IsSoundPlaying())
            {
                m_DeployLoopSound = SEffectManager.PlaySound(
                    GetLoopDeploySoundset(), GetPosition());
            }
        }
    }

    void StopDeployLoopSound()
    {
        if (!GetGame().IsDedicatedServer())
        {
            m_DeployLoopSound.SetSoundFadeOut(0.5);
            m_DeployLoopSound.SoundStop();
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
