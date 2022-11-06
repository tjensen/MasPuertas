modded class Hologram
{
    override string ProjectionBasedOnParent()
    {
        MoreDoorKitBase item_in_hands = MoreDoorKitBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());

        if (item_in_hands)
        {
            return item_in_hands.j_Door();
        }

        return super.ProjectionBasedOnParent();
    }

    override EntityAI PlaceEntity(EntityAI entity_for_placing)
    {
        entity_for_placing = super.PlaceEntity(entity_for_placing);

        if (entity_for_placing.IsInherited(MoreDoorBase))
        {
            entity_for_placing.SetPosition(m_Projection.GetPosition());
            entity_for_placing.SetOrientation(m_Projection.GetOrientation());
        }

        return entity_for_placing;
    }

    override void EvaluateCollision(ItemBase action_item = null)
    {
        ItemBase item_in_hands = ItemBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());

        if (item_in_hands && item_in_hands.IsInherited(MoreDoorKitBase))
        {
            SetIsColliding(false);
            return;
        }

        super.EvaluateCollision(action_item);
    }
};

// vim:ft=enforce
