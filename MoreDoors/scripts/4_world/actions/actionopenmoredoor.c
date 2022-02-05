class ActionOpenMoreDoor : ActionOpenFence
{
    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT * 2);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        if (targetObject && targetObject.CanUseConstruction())
        {
            MoreDoorBase fence = MoreDoorBase.Cast(targetObject);

            if (fence && fence.CanOpenFence() && fence.CanBeInteractedWithBy(player))
            {
                return true;
            }
        }

        return false;
    }
};

// vim:ft=enforce
