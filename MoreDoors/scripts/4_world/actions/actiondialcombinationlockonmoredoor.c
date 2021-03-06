class ActionDialCombinationLockOnMoreDoor : ActionDialCombinationLockOnTarget
{
    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINotPresent;
        m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT * 2);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        if (targetObject && targetObject.CanUseConstruction())
        {
            MoreDoorBase fence = MoreDoorBase.Cast(targetObject);

            if (fence && fence.IsLocked() && fence.CanBeInteractedWithBy(player))
            {
                ConstructionActionData construction_action_data = player.GetConstructionActionData();
                construction_action_data.SetCombinationLock(fence.GetCombinationLock());

                return true;
            }
        }

        return false;
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        //set dialed number
        ConstructionActionData construction_action_data = action_data.m_Player.GetConstructionActionData();
        CombinationLock combination_lock =  construction_action_data.GetCombinationLock();
        if (combination_lock)
        {
            combination_lock.DialNextNumber();

            //check for unlock state
            if (!combination_lock.IsLockedOnGate())
            {
                EntityAI target_entity = EntityAI.Cast(action_data.m_Target.GetObject());

                // Unlock inventory before detaching lock to prevent inventory desync
                target_entity.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);

                combination_lock.UnlockServer(action_data.m_Player, target_entity);
            }
        }
    }
};

// vim:ft=enforce
