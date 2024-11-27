modded class CombinationLock
{
    override bool IsLockAttached()
    {
        if (!super.IsLockAttached())
        {
            return false;
        }

        InventoryLocation il = new InventoryLocation();
        GetInventory().GetCurrentInventoryLocation(il);

        return il.GetType() == InventoryLocationType.ATTACHMENT;
    }
};

// vim:ft=enforce
