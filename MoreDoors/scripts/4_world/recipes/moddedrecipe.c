modded class PluginRecipesManagerBase
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new craft_MoreDoorSmall);
        RegisterRecipe(new craft_MoreDoorMetalSmall);
        RegisterRecipe(new craft_MoreDoorShanty);
        RegisterRecipe(new craft_MoreDoorBarricade);
    }
}
