class ActionUpgradeBarricadeCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( 5 );
	}
};

class ActionUpgradeBarricade: ActionContinuousBase
{
	void ActionUpgradeBarricade()
	{
		m_CallbackClass = ActionUpgradeBarricadeCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;		
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
	}
		
	override string GetText()
	{
		return "Upgrade";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object target_object = target.GetObject();
		MoreDoorBarricade base_building = MoreDoorBarricade.Cast( target_object );
		if ( base_building )
		{
			if (base_building.hasTheGoodStuff())
			{
				return true;	
			}
		}
        
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		MoreDoorBase base_building = MoreDoorBase.Cast( action_data.m_Target.GetObject() );
        vector pos = base_building.GetPosition();
        vector ori = base_building.GetOrientation();

		base_building.Delete();

        MoreDoorMetalBarricade upgrade = MoreDoorMetalBarricade.Cast( GetGame().CreateObject("MoreDoorMetalBarricade", pos, false ));
		upgrade.SetPosition( pos );
		upgrade.SetOrientation( ori );
	}
	
};