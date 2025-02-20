CORNERED (Unreal Engine 5)

An open-source portfolio project by Tamas Gregus.

Visually not polished, but REFACTORED branch: 
https://github.com/gregtom6/CorneredUE5/tree/master

Most up-to-date branch, have more features, visually nice, but NOT REFACTORED yet: 
https://github.com/gregtom6/CorneredUE5/tree/visual_upgrade

Optimized AI (NOT REFACTORED, have more features):
https://github.com/gregtom6/CorneredUE5/tree/optimizing_AI/

AI code is: Private/Characters/ActorComponents/HideSpotFinder.cpp

https://www.youtube.com/watch?v=zcvlouoBm9U

///////////////////////////////////////////////////

Input: Enhanced Input

Audio: MetaSound

AI: State Tree

Particles: Niagara System

Render Pipeline: Deferred rendering pipeline

Unreal Engine: 5.4.1

///////////////////////////////////////////////////

Naming conventions:

Prefixes in names:

Config_: DataAsset related file names are started with these

Postfixes in names:

DevSettings: UDeveloperSettings related file names are ended with these

///////////////////////////////////////////////////

Architecture:

To maintain ratios of the Unity project, I have converted the transforms of many Unity-made shapes into Unreal measurement unit. To use the pawn of the player from Unity the way Unreal would better support it, I made the model in Blender and exported that in FBX into Unreal. 

The BP_PlayerCharacter is the Pawn of the MainScene. It is using ABP_PlayerCharacter2 Animation Blueprint, inherited from UPlayerCharacterAnimInstance. The Animation Blueprint is using State Machines for animating the arm and leg movements. Its AnimGraph is using Inertialization to blend the leg and arm animations together. In the State Machines I have used similar States and variables, which are used in the Unity project's relevant Animators. The cornered_character_Skeleton is using Sockets (BodySocket, RightArmSocket) for visualizing AEquippedWeapon instances on the Pawn.  

MainMenu level doesn't use a Pawn, so it's World Settings override the GameMode class with its own BP_MainMenuGameMode. It has its own BP_MainMenuPlayerController to visualize mouse cursor the whole time while MainMenu level is visible. 

ACorneredObjectPool is an Object Pool, and is able to manage different types of Actors. its being used by ABeltController to manage ABeltElements. 

For Input, I have used the Enhanced Input. The InputAction and InputMappingContext assets are used from ACorneredPlayerController. 

Managing gameplay progression happens with BP_ProgressionGameState, which is referred in the BP_CorneredGameMode. For simplicity, there's an integer member variable (UnlockLevel), which gets stepped, when the player unlocks the next group of features. It can be saved and loaded later, when the gameplay needs to preserve progression. 

AI works with State Tree, because that's the successor of Behavior Tree. I wrote custom conditions and states to manage the BP_EnemyCharacter. These are FShootPositionEnemyCondition, FShootPositionEnemyState and FDefendPositionEnemyCondition, FDefendPositionEnemyState. AI also uses UPawnSensingComponent to detect the player pawn, when the conditions are correct to shoot him. To support AI behavior, I have also added an Actor Component called UHideSpotFinder. This makes multiple line tracing from the BP_PlayerCharacter in different angles. Finds a specific trace channel and checks the trace in the same direction. It tries to find a location along that direction on the navmesh, which is not visible by the BP_PlayerCharacter's Camera component. That will be selected the hiding spot for the enemy character to take cover from the player. Character damage is using UGameplayStatics::ApplyDamage and AActor::TakeDamage functions. 

2D sounds (Main menu and gameplay background sounds) I have used AHUD subclasses (BP_MainMenuHUD, BP_GameplayHUD). MainMenuHUD subscribes to MainMenu userwidget button click events, and since they are Actors, they are using UAudioComponents to manage these sounds. Conveyor belt sound comes from AmbientSound Actors.  For randomizing weapon sounds, I have used MetaSound, because its a more modern approach of handling audio compared to using SoundCue. 

///////////////////////////////////////////////////

Architectural examples:

AIngredient, AProduct, AShieldProduct, AWeaponProduct, AAdditionalProduct are meant to make the different kinds of ingredients separately manageable. For example, all ingredients are pickable. But only the products (shields, weapons, possibly new products added in the future) are equipable and usable in character inventories. UCharacterWeapon is managed by both player and the enemy (AI). The unique behaviors are in UPlayerWeapon and UEnemyWeapon. The player weapon processes inputs to shoot, and he can shoot every single time, when there isn't happening any cooldown. But the enemy shooting input comes from the AI. And while it can shoot, when the weapon cooled down, it will only shoot, when it has direct "eye contact" with the player.

///////////////////////////////////////////////////

External libraries:

I haven't used any. 

///////////////////////////////////////////////////

Game Design decisions:

In this game, there are bossfights. The player needs to defeat an enemy multiple times. To avoid repetition, I made the player to be able to assemble his own equipment for each fight. The equipment contain a mandatory weapon, and an optional shield and/or extra abilities. These can be assembled from an infinite conveyor belt, which generates ingredients for these equipments with various random chance values as set by the designer. The recipes are printed on the walls, which are also configurable by the designer. The in-game recipe list automatically gets regenerated if the recipes get changed. Stronger weapons and stronger shields need more time to assemble, because they need more ingredients. To make the player be able prepare for the fight, I have added a timer, which can be reset. I wanted to add some chance to use tactics in fight, so I have added an enemy equipment hint, which can help the player to construct his weapon and shield more effectively. To allow the fights have some variations, after defeating an enemy, new recipes become available. I also wanted to give the player an ultimate goal. So during the preparing times, the player can either invest time into assembling stronger equipments, or he can hold the exit door button for a period of time. It increases the percentage of the exit door opening, so he can finish the game, once it has been fulfilled.
