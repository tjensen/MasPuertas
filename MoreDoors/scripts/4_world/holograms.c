modded class Hologram
{
    override string ProjectionBasedOnParent()
    {
        MoreDoorKitBase item_in_hands = MoreDoorKitBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

        if ( item_in_hands )
        {
            return item_in_hands.j_Door();
        }

        return super.ProjectionBasedOnParent();
    }

    override void EvaluateCollision(ItemBase action_item = null)
    {
        ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

        if ( item_in_hands && item_in_hands.IsInherited( MoreDoorKitBase ))
        {
            SetIsColliding(false);
            return;
        }

        super.EvaluateCollision();
    }
};

// vim:ft=enforce
