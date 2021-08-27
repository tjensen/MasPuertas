modded class Hatchet extends ToolBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionDismantleMoreDoor);
		AddAction(ActionUpgradeBarricade);
	}
};

modded class Crowbar
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionDismantleMoreDoor);
	}
};

modded class Hammer
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionUpgradeBarricade);
	}
};
