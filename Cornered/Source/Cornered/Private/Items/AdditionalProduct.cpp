// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Items/AdditionalProduct.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"
#include "Camera/CameraComponent.h"
#include "Configs/DataAssets/Config_Equipment.h"

void AAdditionalProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory, UCameraComponent* camera, UConfig_Equipment* config) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory, camera, config);
}