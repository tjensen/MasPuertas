modded class VicinityItemManager
{
    override bool IsObstructed (Object filtered_object)
    {
        if ( filtered_object.CanUseConstruction() )
        {
            MoreDoorBase moredoor = MoreDoorBase.Cast( filtered_object );
            if ( moredoor )
            {
                return false;
            }
        }
        
        return super.IsObstructed (filtered_object);
    }
};