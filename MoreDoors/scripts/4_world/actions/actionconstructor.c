modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionNextCombinationLockDialOnMoreDoor);
        actions.Insert(ActionCloseMoreDoor);
        actions.Insert(ActionOpenMoreDoor);
        actions.Insert(ActionDialCombinationLockOnMoreDoor);
        actions.Insert(ActionDestroyMoreDoor);
        actions.Insert(ActionDismantleMoreDoor);
        actions.Insert(ActionDestroyCombinationLockMoreDoor);
        actions.Insert(ActionUpgradeBarricade);
    }
};

// vim:ft=enforce
