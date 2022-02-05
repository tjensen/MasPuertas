class ActionNextCombinationLockDialOnMoreDoor : ActionNextCombinationLockDialOnTarget
{
    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT * 2);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        if (targetObject && targetObject.CanUseConstruction())
        {
            MoreDoorBase fence = MoreDoorBase.Cast(targetObject);

            if (fence && fence.IsLocked() && !player.GetItemInHands() && fence.CanBeInteractedWithBy(player))
            {
                string selection = fence.GetActionComponentName(target.GetComponentIndex());

                    ConstructionActionData construction_action_data = player.GetConstructionActionData();
                    construction_action_data.SetCombinationLock(fence.GetCombinationLock());

                    return true;

            }
        }

        return false;
    }
};

// vim:ft=enforce
