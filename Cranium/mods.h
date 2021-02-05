#pragma once
#include "finder.h"

inline UObject* gPlaylist;

//TODO: add safety checks in UFuncs.
namespace UFunctions
{
	//same as summon command in-game but from code.
	inline void Summon(const wchar_t* ClassToSummon)
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		ObjectFinder CheatManagerFinder = PlayerControllerFinder.Find(XOR(L"CheatManager"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.CheatManager:Summon"));

		const FString ClassName = ClassToSummon;

		UCheatManager_Summon_Params params;
		params.ClassName = ClassName;

		ProcessEvent(CheatManagerFinder.GetObj(), fn, &params);
		printf("\n[Neoroyale] %ls was summoned!.\n", ClassToSummon);
	}

	inline void TeleportToSpawn()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		ObjectFinder CheatManagerFinder = PlayerControllerFinder.Find(XOR(L"CheatManager"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.CheatManager:BugItGo"));

		UCheatManager_BugItGo_Params params;
		params.X = -156128.36;
		params.Y = -159492.78;
		params.Z = -2996.30;
		params.Pitch = 0;
		params.Yaw = 0;
		params.Roll = 0;

		ProcessEvent(CheatManagerFinder.GetObj(), fn, &params);
	}

	inline void DestroyAllHLODs()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		ObjectFinder CheatManagerFinder = PlayerControllerFinder.Find(XOR(L"CheatManager"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.CheatManager:DestroyAll"));

		const auto HLODSMActor = FindObject<UClass*>(XOR(L"Class /Script/FortniteGame.FortHLODSMActor"));

		UCheatManager_DestroyAll_Params params;
		params.Class = HLODSMActor;

		ProcessEvent(CheatManagerFinder.GetObj(), fn, &params);
	}

	//travel to a url
	inline void Travel(const wchar_t* url)
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.PlayerController:SwitchLevel"));

		const FString URL = url;

		APlayerController_SwitchLevel_Params params;
		params.URL = URL;

		ProcessEvent(PlayerControllerFinder.GetObj(), fn, &params);
	}

	//Simulates the server telling the game that it's ready to start match
	inline void ServerReadyToStartMatch()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerController:ServerReadyToStartMatch"));

		Empty_Params params;

		ProcessEvent(PlayerControllerFinder.GetObj(), fn, &params);
		printf("\n[Neoroyale] Server is ready to start match now!.\n");
	}

	//Read the name lol
	inline void StartMatch()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
		ObjectFinder WorldFinder = GameViewPortClientFinder.Find(L"World");
		ObjectFinder GameModeFinder = WorldFinder.Find(L"AuthorityGameMode");

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.GameMode:StartMatch"));

		Empty_Params params;

		ProcessEvent(GameModeFinder.GetObj(), fn, &params);
		printf("\n[Neoroyale] Match started!.\n");
	}

	inline void SetPlaylist()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
		ObjectFinder WorldFinder = GameViewPortClientFinder.Find(L"World");
		ObjectFinder GameStateFinder = WorldFinder.Find(XOR(L"GameState"));

		const auto CurrentPlaylistInfoOffset = ObjectFinder::FindOffset(XOR(L"Class /Script/FortniteGame.FortGameStateAthena"), XOR(L"CurrentPlaylistInfo"));

		const auto CurrentPlaylistInfo = reinterpret_cast<FPlaylistPropertyArray*>(reinterpret_cast<uintptr_t>(GameStateFinder.GetObj()) + CurrentPlaylistInfoOffset);

		CurrentPlaylistInfo->BasePlaylist = gPlaylist;
		CurrentPlaylistInfo->OverridePlaylist = gPlaylist;

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortGameStateAthena:OnRep_CurrentPlaylistInfo"));

		Empty_Params params;

		ProcessEvent(GameStateFinder.GetObj(), fn, &params);
	}

	inline void SetGamePhase()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
		ObjectFinder WorldFinder = GameViewPortClientFinder.Find(L"World");
		ObjectFinder GameStateFinder = WorldFinder.Find(XOR(L"GameState"));

		const auto GamePhaseOffset = ObjectFinder::FindOffset(XOR(L"Class /Script/FortniteGame.FortGameStateAthena"), XOR(L"GamePhase"));

		EAthenaGamePhase* GamePhase = reinterpret_cast<EAthenaGamePhase*>(reinterpret_cast<uintptr_t>(GameStateFinder.GetObj()) + GamePhaseOffset);

		*GamePhase = EAthenaGamePhase::None;

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortGameStateAthena:OnRep_GamePhase"));

		AFortGameStateAthena_OnRep_GamePhase_Params params;
		params.OldGamePhase = EAthenaGamePhase::Setup;

		ProcessEvent(GameStateFinder.GetObj(), fn, &params);
	}

	/*
	inline void AddItemToInventory(AFortInventory* ParentInventory, UObject* ItemToAdd, int ItemCount, FGuid withGUID)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortInventory:HandleInventoryLocalUpdate"));

		Empty_Params params;

		ProcessEvent(Inventory, fn, &params);

        //This will be used to edit it's entries to set it's GUID
        UFortWorldItem* WorldItemInstance;
        
		//This is the instance to be later used in for the Updated Item List. New WorldItems get added to this...
		TArray<UFortItem*> InventoryItemInstances;

		ParentInventory->HandleInventoryLocalUpdate();

        struct FFortItemEntry TempItemEntry;

		TArray<struct FFortItemEntry> Replicated_Entries;

        TempItemEntry.Count = 1;
		TempItemEntry.ItemDefiniton = ItemToAdd;
		TempItemEntry.Durability = 3232.0000;
		TempItemEntry.LoadedAmmo = 32;
		TempItemEntry.ItemGUID = withGUID;


        //Add the New Item Entry to the Replicated Entries custom variable which is to be later used in setting the ReplicatedEntries in the Inventory Structure...
		Replicated_Entries.Add(TempItemEntry);

        //Create a new FortItem which is to be casted to FortWorldItem later on so the Entry can be set for the GUID,Count,Level,Durability and etc...
		WorldItemInstance = static_cast<UFortWorldItem*>(ItemToAdd->CreateTemporaryItemInstanceBP(ItemCount, 3));
        
		//Set the World Item's Count...
        WorldItemInstance -> ItemEntry.Count = 1;

        //Set the GUID of the WorldItem, I don't know if you could generate a random GUID by calling a function... we might have to do this manually
		WorldItemInstance -> ItemEntry.ItemGUID = withGUID;       

        //Add our new FortWorldItem to tne InventoryItemInstances variable which will then be used as the ItemInstances for the updated ItemList of the Inventory...
        InventoryItemInstances.Add(WorldItemInstance);

       //Adds the FortWorldItem that we had created and set GUID and count to the the ItemInstances Array in the Inventory structure in the Parent Inventory.
		ParentInventory -> Inventory.ItemInstances.Add(WorldItemInstance); 

		//Create a new struct to be later set as the Variable InventoryItemInstances
		struct FFortItemList UpdatedItemList;
		//which is then is later used to be the new ItemList for the inventory
        
		//Finish updating the replicated entries by setting it to our newly updated one.
		UpdatedItemList.ReplicatedEntries = ReplicatedEntries;

		//Set the ItemInstances list to the newly created one.
		UpdatedItemList.ItemInstances = InventoryItemInstances;
         
        //Finish setting the Inventory struct (which is a FFortItemList) to our update ItemList;
		ParentInventory -> Inventory = UpdatedItemList;

        ParentInventory ->HandleInventoryLocalUpdate();
		ParentInventory ->ClientForceWorldInventoryUpdate();
		AFortPlayerState* PawnPlayerState -> static_cast<AFortPlayerState*>(Pawn->PlayerState);
		PawnPlayerState -> OnRep_AccumulatedItems();
		PawnPlayerState -> OnRep_QuickbarEquippedItems();

	}*/

	inline void Play(const wchar_t* EventSequenceMap, const wchar_t* AnimationPlayerFullName)
	{
		/*ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
		ObjectFinder WorldFinder = GameViewPortClientFinder.Find(L"World");
		ObjectFinder NetworkManagerFinder = WorldFinder.Find(XOR(L"NetworkManager"));
		ObjectFinder PersistentLevelFinder = WorldFinder.Find(XOR(L"PersistentLevel"));

		//Loading the level instance in memory
		const auto LoadLevelInstance = FindObject<UFunction*>(XOR(L"Function /Script/Engine.LevelStreamingDynamic:LoadLevelInstance"));
		const auto LevelStreamingDynamic = FindObject<UObject*>(XOR(L"LevelStreamingDynamic /Script/Engine.Default__LevelStreamingDynamic"));

		FRotator WorldRotation;
		WorldRotation.Yaw = 0;
		WorldRotation.Roll = 0;
		WorldRotation.Pitch = 0;

		ULevelStreamingDynamic_LoadLevelInstance_Params LoadLevelInstanceParams;
		LoadLevelInstanceParams.WorldContextObject = WorldFinder.GetObj();
		LoadLevelInstanceParams.LevelName = EventSequenceMap;
		LoadLevelInstanceParams.Location = FVector(0, 0, 0);
		LoadLevelInstanceParams.Rotation = WorldRotation;

		ProcessEvent(LevelStreamingDynamic, LoadLevelInstance, &LoadLevelInstanceParams);
		printf("\n[DEBUG] LEVEL INSTANCE WAS CREATED\n");
		Sleep(5000);

		//Using the game instance object to get it's FName
		UObject* LevelInstance = LoadLevelInstanceParams.ReturnValue;

		const auto GetWorldAssetPackageFName = FindObject<UFunction*>(XOR(L"Function /Script/Engine.LevelStreaming:GetWorldAssetPackageFName"));

		ULevelStreaming_GetWorldAssetPackageFName_Params GetWorldAssetPackageFNameParams;
		ProcessEvent(LevelInstance, GetWorldAssetPackageFName, &GetWorldAssetPackageFNameParams);
		printf("\n[DEBUG] LEVEL FNAME\n");
		
		//We have the name now we call load stream level
		FName MapName = GetWorldAssetPackageFNameParams.ReturnValue;

		const auto LoadStreamLevel = FindObject<UFunction*>(XOR(L"Function /Script/Engine.GameplayStatics:LoadStreamLevel"));

		UGameplayStatics_LoadStreamLevel_Params LoadStreamLevelParams;
		LoadStreamLevelParams.WorldContextObject = WorldFinder.GetObj();
		LoadStreamLevelParams.LevelName = MapName;
		LoadStreamLevelParams.bMakeVisibleAfterLoad = true;
		LoadStreamLevelParams.bShouldBlockOnLoad = false;

		ProcessEvent(NetworkManagerFinder.GetObj(), LoadStreamLevel, &LoadStreamLevelParams);
		printf("\n[DEBUG] LEVEL WAS STREAMED IN\n");
		Sleep(5000);*/

		//Level is streamed inside the map now we start the event sequence
		const auto Play = FindObject<UFunction*>(XOR(L"Function /Script/MovieScene.MovieSceneSequencePlayer:Play"));

		const auto Sequence = FindObject<void*>(AnimationPlayerFullName);

		ProcessEvent(Sequence, Play, nullptr);
		printf("\n[DEBUG] EVENT STARTED\n");
	}

	inline void ConsoleLog(std::wstring message)
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
		ObjectFinder WorldFinder = GameViewPortClientFinder.Find(L"World");
		ObjectFinder GameModeFinder = WorldFinder.Find(L"AuthorityGameMode");

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.GameMode:Say"));

		const FString Msg = message.c_str();
		AGameMode_Say_Params params;
		params.Msg = Msg;

		ProcessEvent(GameModeFinder.GetObj(), fn, &params);
	}
}

namespace Console
{
	//constructs and assigns FortCheatManager to the main console.
	inline bool CheatManager()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		if (!LocalPlayer.GetObj()) return false;

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		ObjectFinder CheatManagerFinder = PlayerControllerFinder.Find(XOR(L"CheatManager"));

		UObject*& pcCheatManager = reinterpret_cast<UObject*&>(CheatManagerFinder.GetObj());

		const auto cCheatManager = FindObject<UClass*>(XOR(L"Class /Script/Engine.CheatManager"));

		if (!pcCheatManager && cCheatManager)
		{
			const auto CheatManager = StaticConstructObject(
				cCheatManager,
				PlayerControllerFinder.GetObj(),
				nullptr,
				RF_NoFlags,
				None,
				nullptr,
				false,
				nullptr,
				false
			);

			pcCheatManager = CheatManager;
			return true;
		}
		return false;
	}

	//unlocks ue4 console with cheat manager
	inline bool Unlock()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder ConsoleClassFinder = EngineFinder.Find(XOR(L"ConsoleClass"));
		ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
		ObjectFinder ViewportConsoleFinder = GameViewPortClientFinder.Find(XOR(L"ViewportConsole"));

		UObject*& ViewportConsole = reinterpret_cast<UObject*&>(ViewportConsoleFinder.GetObj());

		const auto Console = StaticConstructObject(
			static_cast<UClass*>(ConsoleClassFinder.GetObj()),
			reinterpret_cast<UObject*>(GameViewPortClientFinder.GetObj()),
			nullptr,
			RF_NoFlags,
			None,
			nullptr,
			false,
			nullptr,
			false
		);

		ViewportConsole = Console;

		CheatManager();
		return true;
	}
}

//TODO: move this from here
struct Pawn
{
	auto Possess()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.Controller:Possess"));

		AController_Possess_Params params;
		params.InPawn = reinterpret_cast<UObject*>(this);

		ProcessEvent(PlayerControllerFinder.GetObj(), fn, &params);
		printf("\n[Neoroyale] PlayerPawn was possessed!.\n");
	}

	auto StartSkydiving(float height)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawnAthena:TeleportToSkyDive"));

		AFortPlayerPawnAthena_TeleportToSkyDive_Params params;
		params.HeightAboveGround = height;

		ProcessEvent(this, fn, &params);
		printf("\nSkydiving!, Redeploying at %fm.\n", height);
	}

	auto IsJumpProvidingForce()
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.Character:IsJumpProvidingForce"));

		ACharacter_IsJumpProvidingForce_Params params;

		ProcessEvent(this, fn, &params);

		return params.ReturnValue;
	}

	auto IsSkydiving()
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawn:IsSkydiving"));

		ACharacter_IsSkydiving_Params params;

		ProcessEvent(this, fn, &params);

		return params.ReturnValue;
	}

	auto IsParachuteOpen()
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawn:IsParachuteOpen"));

		ACharacter_IsParachuteOpen_Params params;

		ProcessEvent(this, fn, &params);

		return params.ReturnValue;
	}

	auto IsParachuteForcedOpen()
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawn:IsParachuteForcedOpen"));

		ACharacter_IsParachuteForcedOpen_Params params;

		ProcessEvent(this, fn, &params);

		return params.ReturnValue;
	}

	auto Jump()
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.Character:Jump"));

		Empty_Params params;

		ProcessEvent(this, fn, &params);
	}

	auto SetSkeletalMesh()
	{
		ObjectFinder PawnFinder = ObjectFinder::EntryPoint(uintptr_t(this));
		ObjectFinder MeshFinder = PawnFinder.Find(XOR(L"Mesh"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.SkinnedMeshComponent:SetSkeletalMesh"));

		const auto Mesh = FindObject<UObject*>(
			XOR(L"SkeletalMesh /Game/Characters/Player/Male/Medium/Base/SK_M_MALE_Base.SK_M_MALE_Base")
		);

		if (Mesh)
		{
			USkinnedMeshComponent_SetSkeletalMesh_Params params;
			params.NewMesh = Mesh;
			params.bReinitPose = false;

			ProcessEvent(MeshFinder.GetObj(), fn, &params);
		}
	}

	auto ShowSkin()
	{
		ObjectFinder PawnFinder = ObjectFinder::EntryPoint(uintptr_t(this));
		ObjectFinder PlayerStateFinder = PawnFinder.Find(XOR(L"PlayerState"));

		const auto KismetLib = FindObject<UObject*>(XOR(L"FortKismetLibrary /Script/FortniteGame.Default__FortKismetLibrary"));
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortKismetLibrary:UpdatePlayerCustomCharacterPartsVisualization"));

		UFortKismetLibrary_UpdatePlayerCustomCharacterPartsVisualization_Params params;
		params.PlayerState = PlayerStateFinder.GetObj();

		ProcessEvent(KismetLib, fn, &params);
		printf("\nCharacter parts should be visiable now!.\n");
	}

	auto EquipWeapon(const wchar_t* weaponname, const int guid)
	{
		FGuid GUID;
		GUID.A = guid;
		GUID.B = guid;
		GUID.C = guid;
		GUID.D = guid;

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPawn:EquipWeaponDefinition"));

		auto WeaponData = FindObject<UObject*>(weaponname, true);

		if (WeaponData)
		{
			std::wstring objectName = GetObjectFullName(WeaponData);

			if (objectName.starts_with(L"AthenaGadget"))
			{
				const auto FUN_weapondef = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortGadgetItemDefinition:GetWeaponItemDefinition"));

				UFortGadgetItemDefinition_GetWeaponItemDefinition_Params prm_ReturnValue;

				ProcessEvent(WeaponData, FUN_weapondef, &prm_ReturnValue);

				if (prm_ReturnValue.ReturnValue)
				{
					WeaponData = prm_ReturnValue.ReturnValue;
				}
			}

			//weapon found equip it
			AFortPawn_EquipWeaponDefinition_Params params;
			params.WeaponData = WeaponData;
			params.ItemEntryGuid = GUID;

			ProcessEvent(this, fn, &params);

			return params.ReturnValue;
		}
		else
		{
			MessageBoxA(nullptr, XOR("This item doesn't exist!"), XOR("Cranium"), MB_OK);
		}
	}

	auto SetMovementMode(TEnumAsByte<EMovementMode> NewMode, unsigned char CustomMode)
	{
		ObjectFinder PawnFinder = ObjectFinder::EntryPoint(uintptr_t(this));

		ObjectFinder CharMovementFinder = PawnFinder.Find(XOR(L"CharacterMovement"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.CharacterMovementComponent:SetMovementMode"));

		UCharacterMovementComponent_SetMovementMode_Params params;

		params.NewMovementMode = NewMode;
		params.NewCustomMode = CustomMode;

		ProcessEvent(CharMovementFinder.GetObj(), fn, &params);
	}

	auto Fly(bool bIsFlying)
	{
		TEnumAsByte<EMovementMode> NewMode;

		if (!bIsFlying) NewMode = EMovementMode::MOVE_Flying;
		else NewMode = EMovementMode::MOVE_Walking;

		SetMovementMode(NewMode, 0);
	}

	auto SetPawnGravityScale(float GravityScaleInput)
	{
		ObjectFinder PawnFinder = ObjectFinder::EntryPoint(uintptr_t(this));

		ObjectFinder CharMovementFinder = PawnFinder.Find(XOR(L"CharacterMovement"));

		const auto GravityScaleOffset = ObjectFinder::FindOffset(XOR(L"Class /Script/Engine.CharacterMovementComponent"), XOR(L"GravityScale"));

		float* GravityScale = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(CharMovementFinder.GetObj()) + GravityScaleOffset);

		*GravityScale = GravityScaleInput;
	}
	
	auto SetHealth(float SetHealthInput)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPawn:SetHealth"));

		AFortPawn_SetHealth_Params params;

		params.NewHealthVal = SetHealthInput;

		ProcessEvent(this, fn, &params);
	}

	auto SetShield(float SetShieldInput)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPawn:SetShield"));

		AFortPawn_SetShield_Params params;

		params.NewShieldValue = SetShieldInput;

		ProcessEvent(this, fn, &params);
	}

	auto SetMaxHealth(float SetMaxHealthInput)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPawn:SetMaxHealth"));

		AFortPawn_SetMaxHealth_Params params;

		params.NewHealthVal = SetMaxHealthInput;

		ProcessEvent(this, fn, &params);
	}

	auto SetMaxShield(float SetMaxShieldInput)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPawn:SetMaxShield"));

		AFortPawn_SetMaxShield_Params params;

		params.NewValue = SetMaxShieldInput;

		ProcessEvent(this, fn, &params);
	}


	auto SetMovementSpeed(float SetMovementSpeedInput)
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPawn:SetMovementSpeed"));

		AFortPawn_SetMovementSpeedMultiplier_Params params;

		params.NewMovementSpeedVal = SetMovementSpeedInput;

		ProcessEvent(this, fn, &params);
	}

	static auto ToggleInfiniteAmmo()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));

		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		const auto bEnableVoiceChatPTTOffset = ObjectFinder::FindOffset(XOR(L"Class /Script/FortniteGame.FortPlayerController"), XOR(L"bEnableVoiceChatPTT"));

		// TECHNICAL EXPLINATION: (kemo) We are doing this because InfiniteAmmo bool and some other bools live in the same offset
		// the offset has 8 bits, bools are only one bit as it's only 0\1 so we have a struct with 8 bools to be able to edit that specific bool
		const auto PlayerControllerBools = reinterpret_cast<PlayerControllerBoolsForInfiniteAmmo*>(reinterpret_cast<uintptr_t>(PlayerControllerFinder.GetObj()) + bEnableVoiceChatPTTOffset);

		PlayerControllerBools->bInfiniteAmmo = true;
		PlayerControllerBools->bInfiniteMagazine = true;
	}

	auto Skydive()
	{
		if (this->IsSkydiving())
		{
			const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawn:EndSkydiving"));

			ProcessEvent(this, fn, nullptr);
		}

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawn:BeginSkydiving"));

		AFortPlayerPawn_BeginSkydiving_Params params;
		params.bFromBus = true;

		ProcessEvent(this, fn, &params);

		//this->SetMovementMode(EMovementMode::MOVE_Custom, 4);
	}

	auto ForceOpenParachute()
	{
		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerPawn:BP_ForceOpenParachute"));

		Empty_Params params;

		ProcessEvent(this, fn, &params);
	}

	auto IsInAircraft()
	{
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));
		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));

		const auto fn = FindObject<UFunction*>(XOR(L"Function /Script/FortniteGame.FortPlayerController:IsInAircraft"));
		ACharacter_IsInAircraft_Params params;

		ProcessEvent(PlayerControllerFinder.GetObj(), fn, &params);
		return params.ReturnValue;
	}
};

namespace Neoroyale
{
	inline bool bIsInit;
	inline bool bIsStarted;
	inline bool bHasJumped;
	inline bool bHasDeployed;
	inline Pawn* PlayerPawn;

	inline void start(const wchar_t* MapToPlayOn)
	{
		UFunctions::Travel(MapToPlayOn);
		bIsStarted = !bIsStarted;
	}

	inline auto Respawn()
	{
		if (PlayerPawn)
		{
			UFunctions::Summon(L"PlayerPawn_Athena_C");
			PlayerPawn = reinterpret_cast<Pawn*>(ObjectFinder::FindActor(L"PlayerPawn_Athena_C"));

			if (PlayerPawn)
			{
				PlayerPawn->Possess();
				PlayerPawn->ShowSkin();
			}
		}
	}

	inline void thread()
	{
		while (true)
		{
			if (PlayerPawn && GetAsyncKeyState(VK_SPACE))
			{
				if (!bHasJumped)
				{
					bHasJumped = !bHasJumped;
					if (PlayerPawn->IsInAircraft())
					{
						Respawn();
					}
					else
					{
						// Glide
						if (PlayerPawn->IsSkydiving() && !PlayerPawn->IsParachuteOpen() && !PlayerPawn->IsParachuteForcedOpen() && !bHasDeployed)
						{
							PlayerPawn->ForceOpenParachute();
							bHasDeployed = !bHasDeployed;
						}

							// Skydive
						else if (PlayerPawn->IsSkydiving() && PlayerPawn->IsParachuteOpen() && !PlayerPawn->IsParachuteForcedOpen())
						{
							PlayerPawn->Skydive();
						}

							// Jump
						else if (!PlayerPawn->IsJumpProvidingForce())
						{
							PlayerPawn->Jump();
						}
					}
				}
			}
			else bHasJumped = false;

			if (GetAsyncKeyState(VK_F3))
			{
				UFunctions::Travel(FRONTEND);
				bIsStarted = false;
				bIsInit = false;
				PlayerPawn = nullptr;
				break;
			}

			Sleep(1000 / 30);
		}
	}

	inline void init()
	{
		Console::CheatManager();

		UFunctions::DestroyAllHLODs();

		UFunctions::Summon(L"PlayerPawn_Athena_C");

		PlayerPawn = reinterpret_cast<Pawn*>(ObjectFinder::FindActor(L"PlayerPawn_Athena_C"));
		auto PlaylistName = GetObjectFirstName(gPlaylist);

		if (PlayerPawn)
		{
			PlayerPawn->Possess();

			//PlayerPawn->SetSkeletalMesh();

			PlayerPawn->ShowSkin();

			PlayerPawn->ToggleInfiniteAmmo();

			printf("\n[DEBUG] Playlist: %ls\n", PlaylistName.c_str());

			if (!wcsstr(PlaylistName.c_str(), XOR(L"Playlist_Papaya")) &&
				!wcsstr(PlaylistName.c_str(), XOR(L"Playlist_BattleLab")))
			{
				UFunctions::TeleportToSpawn();
			}

			if (gVersion != "12.41")
			{
				UFunctions::SetPlaylist();

				UFunctions::SetGamePhase();
			}

			UFunctions::StartMatch();

			UFunctions::ServerReadyToStartMatch();

			CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&thread), nullptr, NULL, nullptr);
		}

		bIsInit = !bIsInit;
	}
}
