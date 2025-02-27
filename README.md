CORNERED (Unreal Engine 5)

Cornered © 2024 by Tamas Gregus is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International 

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

I made the model in Blender and exported that as FBX into Unreal. 

The BP_PlayerCharacter is the Pawn of the MainScene. It is using ABP_PlayerCharacter2 Animation Blueprint, inherited from UPlayerCharacterAnimInstance. The Animation Blueprint is using State Machines for animating the arm and leg movements. Its AnimGraph is using Inertialization to blend the leg and arm animations together. The cornered_character_Skeleton is using Sockets (BodySocket, RightArmSocketPistol, RightArmSocketShotgun) for visualizing AEquippedWeapon instances on the Pawn.  

MainMenu level doesn't use a Pawn, so it's World Settings override the GameMode class with its own BP_MainMenuGameMode. It has its own BP_MainMenuPlayerController to visualize mouse cursor the whole time while MainMenu level is visible. 

ACorneredObjectPool is an Object Pool, and is able to manage different types of Actors. its being used by ABeltController to manage ABeltElements. 

For Input, I have used the Enhanced Input. The InputAction and InputMappingContext assets are used from ACorneredPlayerController. 

Managing gameplay progression happens with BP_ProgressionGameState, which is referred in the BP_CorneredGameMode. For simplicity, there's an integer member variable (UnlockLevel), which gets stepped, when the player unlocks the next group of features. It can be saved and loaded later, when the gameplay needs to preserve progression. 

AI works with State Tree, because that's the successor of Behavior Tree. I wrote custom conditions and states to manage the BP_EnemyCharacter. These are FShootPositionEnemyCondition, FShootPositionEnemyState and FDefendPositionEnemyCondition, FDefendPositionEnemyState. AI also uses UPawnSensingComponent to detect the player pawn, when the conditions are correct to shoot him. To support AI behavior, I have also added an Actor Component called UHideSpotFinder. This makes multiple line tracing from the BP_PlayerCharacter in different angles around the player. Searches for a specific trace channel to find obstacles, and when there's a collision, checks along the line in certain distances, to see where the obstacle ends. Then it projects the line point onto the navmesh, and checks if it is not visible by the BP_PlayerCharacter's Camera component. Multiple line traces (coming from the player) will find potential hiding spots, and I select the middle one (this will be the best hiding spot of the obstacle), because that's the exact behind spot. I find the selected hiding spot in a way that I sort these best hiding spot of different obstacles based on distances from the enemy character. That will be selected the hiding spot for the enemy character to take cover from the player. 

Character damage is using the UE5 built-in Damage System. I use UGameplayStatics::ApplyDamage and AActor::TakeDamage functions. 

The AMixingMachine uses AMixingItemDetector to detect and manage the input ingredients. This machine uses UMixingMachineAbility UActorComponents to modify EItemState of the ingredients via AMixingItemDetector. These can be Burned or Freezed. 
Based on pre-defined recipes, which can be modified by a game designer in the Config_Recipe, are generated onto the BP_RecipeShower. The player can check the actual recipes and use them with the AMixingMachine. 
The AMixingItemDetector can also convert the ingredients and destroy them to create a new ingredient based on the current recipes. These new ingredients will be a subclass of AIngredient called AProduct, which can be equipped, not just picked up and dropped like the parent class. These products can be weapons, shields or equippable abilities. 
After defeating an enemy, new possible recipes get unlocked, and new mixing machine abilities get added to the mixing machine, which can transform the ingredients into new states for the recipes. 

After defeating an enemy, an ASoul gets generated. This is an undestroyable actor, which is existing for future game design reasons. The soul finds an ASoulRoute in the level, which contains an USplineComponent. The soul goes upwards to go away from the body, goes to the spline's closest position (which is not necessarily the beginning of the spline), goes along the spline, and from the end of the spline it goes to an actor called ASoulSniffer. After reaching that, there are Actor Sequences played, to show that the ejected soul can increase a counter. Every level has a limit of soul count, which can be reached and surpassed. The surpassed souls have a punishing mechanic in the later planned levels. 

For 2D sounds (Main menu and gameplay background sounds) I have used AHUD subclasses (BP_MainMenuHUD, BP_GameplayHUD). MainMenuHUD subscribes to MainMenu userwidget button click events, and since they are Actors, they are using UAudioComponents to manage these sounds. Conveyor belt sound comes from AmbientSound Actors.  For randomizing weapon sounds, I have used MetaSound, because its a more modern approach of handling audio compared to using SoundCue. 

///////////////////////////////////////////////////

Architectural examples:

AIngredient, AProduct, AShieldProduct, AWeaponProduct, AAdditionalProduct are meant to make the different kinds of ingredients separately manageable. For example, all ingredients are pickable. But only the products (shields, weapons, possibly new products added in the future) are equipable and usable in character inventories. UCharacterWeapon is managed by both player and the enemy (AI). The unique behaviors are in UPlayerWeapon and UEnemyWeapon. The player weapon processes inputs to shoot, and he can shoot every single time, when there isn't happening any cooldown. But the enemy shooting input comes from the AI. And while it can shoot, when the weapon cooled down, it will only shoot, when it has direct "eye contact" with the player.

///////////////////////////////////////////////////

External libraries:

I haven't used any. 

///////////////////////////////////////////////////

Game Design decisions:

In this game, there are bossfights. The player needs to defeat an enemy multiple times. To avoid repetition, I made the player to be able to assemble his own equipment for each fight. The equipment contain a mandatory weapon, and an optional shield and/or extra abilities. These can be assembled from an infinite conveyor belt, which generates ingredients for these equipments with various random chance values as set by the designer. The recipes are printed on the walls, which are also configurable by the designer. The in-game recipe list automatically gets regenerated if the recipes get changed. Stronger weapons and stronger shields need more time to assemble, because they need more ingredients. To make the player be able prepare for the fight, I have added a timer, which can be reset. I wanted to add some chance to use tactics in fight, so I have added an enemy equipment hint, which can help the player to construct his weapon and shield more effectively. To allow the fights have some variations, after defeating an enemy, new recipes become available. I also wanted to give the player an ultimate goal. So during the preparing times, the player can either invest time into assembling stronger equipments, or he can hold the exit door button for a period of time. It increases the percentage of the exit door opening, so he can finish the game, once it has been fulfilled.
