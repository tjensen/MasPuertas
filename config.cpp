class CfgPatches
{
	class MasPuertas
	{
		units[]=
		{
			"MoreDoorVaultKit",
			"MoreDoorSmallKit",
			"MoreDoorSmallShantyKit",
			"MoreDoorSmallMetalKit",
			"MoreDoorVault",
			"MoreDoorSmall",
			"MoreDoorSmallShanty",
			"MoreDoorSmallMetal",
			"MoreDoorSafe",
			"MoreDoorBarricadeKit",
			"MoreDoorBarricade",
			"MoreDoorMetalBarricade"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Camping",
			"DZ_Scripts"
		};
	};
};
class CfgSlots
{
	class Slot_MetalSheet
	{
		name="MetalSheet";
		displayName="MetalSheet";
		ghostIcon="missing";
		stackMax=3;
	};
};
class CfgMods
{
	class MasPuertas
	{
		type="mod";
		author="spahgettah";
		dir="MasPuertas";
		name="MasPuertas";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"MasPuertas/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"MasPuertas/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"MasPuertas/Scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class Fence;
	class Inventory_Base;
	class Container_Base;
	class MoreDoorBase: Fence
	{
		scope=0;
		displayName="Door";
		descriptionShort="$STR_CfgVehicles_Fence1";
		bounding="BSphere";
		overrideDrawArea="3.0";
		forceFarBubble="true";
		handheld="false";
		lootCategory="Crafted";
		carveNavmesh=1;
		weight=10000;
		itemSize[]={2,3};
		hiddenSelections[]=
		{
			"door1",
			"door2",
			"door3",
			"door4"
		};
		physLayer="item_large";
		createProxyPhysicsOnInit="false";
		createdProxiesOnInit[]=
		{
			"Deployed"
		};
		rotationFlags=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
		attachments[]=
		{
			"Att_CombinationLock"
		};
		class GUIInventoryAttachmentsProps
		{
			class Base
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Base";
				description="";
				attachmentSlots[]=
				{
					"Att_CombinationLock"
				};
				icon="cat_bb_base";
				selection="wall";
			};
			class Attachments
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Attachments";
				description="";
				attachmentSlots[]=
				{
					"Wall_Camonet",
					"Wall_Barbedwire_1",
					"Wall_Barbedwire_2"
				};
				icon="cat_bb_attachments";
				selection="wall";
			};
			class Material
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Materials";
				description="";
				attachmentSlots[]=
				{
					"Material_Nails",
					"Material_WoodenPlanks",
					"Material_MetalSheets",
					"Material_MetalWire"
				};
				icon="cat_bb_material";
				selection="wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class AnimRotate
			{
				source="user";
				component="Door1";
				animPeriod=1;
				initPhase=0;
				initOpened=0.5;
			};
			class Wall_Interact_Rotate: AnimRotate
			{
			};
			class Wall_Barbedwire_1_Mounted_Rotate: AnimRotate
			{
			};
			class Wall_Barbedwire_2_Mounted_Rotate: AnimRotate
			{
			};
			class Wall_Camonet_Rotate: AnimRotate
			{
			};
			class Wall_Gate_Rotate: AnimRotate
			{
			};
			class Wall_Base_Down_Rotate: AnimRotate
			{
			};
			class Wall_Base_Up_Rotate: AnimRotate
			{
			};
			class Wall_Wood_Down_Rotate: AnimRotate
			{
			};
			class Wall_Wood_Up_Rotate: AnimRotate
			{
			};
			class Wall_Metal_Down_Rotate: AnimRotate
			{
			};
			class Wall_Metal_Up_Rotate: AnimRotate
			{
			};
			class Material_WoodenLogs: AnimSourceHidden
			{
			};
			class Material_MetalWire: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_1: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_1_Mounted: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_2: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_2_Mounted: AnimSourceHidden
			{
			};
			class Wall_Camonet: AnimSourceHidden
			{
			};
			class Deployed: AnimSourceHidden
			{
			};
			class Base: AnimSourceHidden
			{
			};
			class Wall_Platform: AnimSourceHidden
			{
			};
			class Wall_Platform_Stairs_Left: AnimSourceHidden
			{
			};
			class Wall_Platform_Stairs_Right: AnimSourceHidden
			{
			};
			class Wall_Gate: AnimSourceHidden
			{
			};
			class Wall_Base_Down: AnimSourceHidden
			{
			};
			class Wall_Base_Up: AnimSourceHidden
			{
			};
			class Wall_Metal_Down: AnimSourceHidden
			{
			};
			class Wall_Metal_Up: AnimSourceHidden
			{
			};
			class Wall_Wood_Down: AnimSourceHidden
			{
			};
			class Wall_Wood_Up: AnimSourceHidden
			{
			};
		};
		class Construction
		{
			class wall
			{
				class wall_gate
				{
					name="$STR_CfgVehicles_Construction_Part_Gate";
					is_gate=1;
					id=5;
					required_parts[]={};
					conflicted_parts[]={};
					collision_data[]={};
					build_action_type=1;
					dismantle_action_type=1;
					material_type=5;
				};
			};
		};
		class PointLights
		{
			class PointLight
			{
				color[]={1,1,1,0.050000001};
				ambient[]={0.0099999998,0.0099999998,0.0099999998,0.0099999998};
				position="light";
				hitpoint="bulb";
				selection="bulb";
				size=0;
				radius=5;
				brightness=0.001;
				dayLight=1;
				heatHazeRadius=0;
				heatHazePower=0;
				fireEffect=0;
				fireEffectOctaves=0;
				fireEffectPersistence=0;
				fireEffectFract=0;
			};
		};
	};
	class MoreDoorKitBase: Container_Base
	{
		scope=0;
		carveNavmesh=1;
		itemSize[]={6,3};
		itemBehaviour=0;
		heavyItem=1;
		physLayer="item_large";
		simulation="inventoryItem";
		rotationFlags=2;
		isMeleeWeapon=0;
		hiddenSelectionsTextures[]={};
		hiddenSelectionsMaterials[]={};
		handheld="true";
		weight=3000;
		useEntityHierarchy="true";
		placement="ForceSlopeOnTerrain";
		absorbency=0;
		attachments[]=
		{
			"Material_Nails",
			"Material_WoodenPlanks",
			"Material_MetalSheets",
			"Material_WoodenLogs",
			"Material_MetalWire"
		};
	};
	class MoreDoorVaultKit: MoreDoorKitBase
	{
		scope=2;
		displayName="Vault Kit";
		descriptionShort="Kit for Building Vault";
		model="\DZ\gear\camping\wooden_case.p3d";
	};
	class MoreDoorSmallKit: MoreDoorKitBase
	{
		scope=2;
		displayName="Small Door Kit";
		descriptionShort="Requires 10 planks, 25 nails, and Metal Wire to build the door. Once the required ingredients are in the slots place the object with the action to build it.";
		model="\DZ\gear\camping\wooden_case.p3d";
	};
	class MoreDoorSmallShantyKit: MoreDoorKitBase
	{
		scope=2;
		displayName="Small Shanty Door Kit";
		descriptionShort="Requires 5 planks and 25 nails to build the door. Once the required ingredients are in the slots place the object with the action to build it.";
		model="\DZ\gear\camping\wooden_case.p3d";
	};
	class MoreDoorSmallMetalKit: MoreDoorKitBase
	{
		scope=2;
		displayName="Small Metal Door Kit";
		descriptionShort="Requires 20 planks, 100 nails, 5 Sheet metal, and Metal Wire to build the door. Once the required ingredients are in the slots place the object with the action to build it.";
		model="\DZ\gear\camping\wooden_case.p3d";
	};
	class MoreDoorBarricadeKit: MoreDoorKitBase
	{
		scope=2;
		displayName="Barricade Kit";
		descriptionShort="Use this to block your windows! Requires 3 planks, 10 nails to place the barricade.";
		model="\DZ\gear\camping\wooden_case.p3d";
	};
	class MoreDoorVault: MoreDoorBase
	{
		scope=2;
		displayName="Vault";
		descriptionShort="Big Vault Door for you to keep the things with the stuff";
		model="MasPuertas\data\Vault\MoreDoor_Vault.p3d";
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class AnimRotate
			{
				source="user";
				component="Selection_Door_Vault";
				animPeriod=5;
				initPhase=0;
				initOpened=0.5;
			};
			class Wall_Interact_Rotate: AnimRotate
			{
			};
			class Wall_Barbedwire_1_Mounted_Rotate: AnimRotate
			{
			};
			class Wall_Barbedwire_2_Mounted_Rotate: AnimRotate
			{
			};
			class Wall_Camonet_Rotate: AnimRotate
			{
			};
			class Wall_Gate_Rotate: AnimRotate
			{
			};
			class Wall_Base_Down_Rotate: AnimRotate
			{
			};
			class Wall_Base_Up_Rotate: AnimRotate
			{
			};
			class Wall_Wood_Down_Rotate: AnimRotate
			{
			};
			class Wall_Wood_Up_Rotate: AnimRotate
			{
			};
			class Wall_Metal_Down_Rotate: AnimRotate
			{
			};
			class Wall_Metal_Up_Rotate: AnimRotate
			{
			};
			class Material_WoodenLogs: AnimSourceHidden
			{
			};
			class Material_MetalWire: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_1: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_1_Mounted: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_2: AnimSourceHidden
			{
			};
			class Wall_Barbedwire_2_Mounted: AnimSourceHidden
			{
			};
			class Wall_Camonet: AnimSourceHidden
			{
			};
			class Deployed: AnimSourceHidden
			{
			};
			class Base: AnimSourceHidden
			{
			};
			class Wall_Platform: AnimSourceHidden
			{
			};
			class Wall_Platform_Stairs_Left: AnimSourceHidden
			{
			};
			class Wall_Platform_Stairs_Right: AnimSourceHidden
			{
			};
			class Wall_Gate: AnimSourceHidden
			{
			};
			class Wall_Base_Down: AnimSourceHidden
			{
			};
			class Wall_Base_Up: AnimSourceHidden
			{
			};
			class Wall_Metal_Down: AnimSourceHidden
			{
			};
			class Wall_Metal_Up: AnimSourceHidden
			{
			};
			class Wall_Wood_Down: AnimSourceHidden
			{
			};
			class Wall_Wood_Up: AnimSourceHidden
			{
			};
		};
	};
	class MoreDoorSmall: MoreDoorBase
	{
		scope=2;
		displayName="Small Door";
		descriptionShort="Small wooden door.";
		model="MasPuertas\data\Wood\MoreDoor_Wood.p3d";
	};
	class MoreDoorSmallShanty: MoreDoorBase
	{
		scope=2;
		displayName="Small Shanty Door";
		descriptionShort="Small rickety door.";
		model="MasPuertas\data\Shanty\MoreDoor_Shanty.p3d";
	};
	class MoreDoorSmallMetal: MoreDoorBase
	{
		scope=2;
		displayName="Small Metal Door";
		descriptionShort="Small metal door.";
		model="MasPuertas\data\Metal\MoreDoor_Metal.p3d";
	};
	class MoreDoorBarricade: MoreDoorBase
	{
		scope=2;
		displayName="Barricade";
		descriptionShort="Just A Barricade, you must be bored if your bothering to read the description on some door...";
		model="MasPuertas\data\windowbarricade\windowbarricade.p3d";
		attachments[]=
		{
			"Material_MetalSheets"
		};
		class GUIInventoryAttachmentsProps
		{
			class Base
			{
				name="Upgrade";
				description="";
				attachmentSlots[]=
				{
					"Material_MetalSheets"
				};
				icon="cat_bb_material";
				selection="wall";
			};
		};
	};
	class MoreDoorMetalBarricade: MoreDoorBase
	{
		scope=2;
		displayName="Metal Barricade";
		descriptionShort="Just A Barricade, you must be bored if your bothering to read the description on some door...";
		model="MasPuertas\data\windowbarricade\windowbarricademetal.p3d";
		class GUIInventoryAttachmentsProps
		{
		};
	};
	class MoreDoorSafe: MoreDoorBase
	{
		scope=2;
		displayName="Small Safe";
		descriptionShort="Just A Safe, you can lock this with a combo lock or codelock";
		model="MasPuertas\data\Safe\MoreDoor_Safe.p3d";
		itemsCargoSize[]={9,9};
		itemSize[]={5,5};
		itemBehaviour=2;
		class Cargo
		{
			itemsCargoSize[]={9,9};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
};
