/*
 * ItemMessageHelper.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: swgemu
 */

#include <iostream>
#include <google/protobuf/text_format.h>
#include <RCFProto.hpp>
#include "rpc/generatedpb/InventoryItem.pb.h"
#include "ItemMessageHelper.h"
#include "../../../MMOEngine/include/engine/core/ManagedReference.h"
#include "../../../MMOEngine/include/system/lang/ref/Reference.h"
#include "../../../MMOEngine/include/system/util/ArrayList.h"
#include "../../../MMOEngine/include/system/util/VectorMap.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/resource/ResourceSpawn.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/resource/ResourceContainer.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/structure/StructureObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/managers/player/PlayerManager.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/scene/SceneObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/weapon/WeaponObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/wearables/ArmorObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/factorycrate/FactoryCrate.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/component/Component.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/PharmaceuticalObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/CurePack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/DotPack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/EnhancePack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/RevivePack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/pharmaceutical/WoundPack.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "../../../MMOCoreORB/src/server/zone/objects/manufactureschematic/ingredientslots/IngredientSlot.h"
#include "../../../MMOCoreORB/src/server/zone/objects/manufactureschematic/factoryblueprint/BlueprintEntry.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/intangible/IntangibleObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/TangibleObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/player/PlayerObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/creature/CreatureObject.h"
#include "../../../MMOCoreORB/src/server/zone/objects/creature/BuffAttribute.h"
#include "../../../MMOCoreORB/src/server/zone/objects/creature/CreatureAttribute.h"
#include "../../../MMOCoreORB/src/server/zone/objects/scene/variables/StringId.h"
#include "../../../MMOEngine/include/engine/log/Logger.h"


ItemMessageHelper::ItemMessageHelper() {

}

void ItemMessageHelper::AddBaseDetailsToMessage(server::zone::objects::scene::SceneObject* item,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	inventoryItem->set_portals_file_name(item->getObjectTemplate()->getPortalLayoutFilename().toCharArray());
	inventoryItem->set_appearance_file_name(item->getObjectTemplate()->getAppearanceFilename().toCharArray());
	inventoryItem->set_display_name(item->getDisplayedName().toCharArray());
	inventoryItem->set_object_name(item->getObjectName()->getFullPath().toCharArray());
	inventoryItem->set_description(item->getDetailedDescription().toCharArray());
	inventoryItem->set_object_id(item->getObjectID());
	inventoryItem->set_containment_location(item->getContainmentType());

	if(item->isTangibleObject()) {
		util::ItemMessageHelper::AddTangibleDetailsToMessage(dynamic_cast<TangibleObject*>(item),inventoryItem);
	}
	else if(item->isIntangibleObject()) {
		util::ItemMessageHelper::AddIntangibleDetailsToMessage(dynamic_cast<IntangibleObject*>(item), inventoryItem);
	}
}

void ItemMessageHelper::AddTangibleDetailsToMessage(server::zone::objects::tangible::TangibleObject* item,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	inventoryItem->set_crafter_name(item->getCraftersName().toCharArray());
	inventoryItem->set_serial_number(item->getSerialNumber().toCharArray());
	inventoryItem->set_max_condition(item->getMaxCondition());
	inventoryItem->set_condition(item->getConditionDamage());

	if(item->isArmorObject() || item->isPsgArmorObject()) {
		swgemurpcserver::rpc::util::ItemMessageHelper::AddArmorDetailsToMessage(dynamic_cast<ArmorObject*>(item), inventoryItem);
	}
	else if(item->isWeaponObject()) {
		util::ItemMessageHelper::AddWeaponDetailsToMessage(dynamic_cast<WeaponObject*>(item), inventoryItem);
	}
	else if(item->isResourceContainer()) {
		util::ItemMessageHelper::AddResourceDetailsToMessage(dynamic_cast<ResourceContainer*>(item), inventoryItem);
	}
	else if(item->isFactoryCrate()) {
		util::ItemMessageHelper::AddFactoryCrateDetailsToMessage(dynamic_cast<FactoryCrate*>(item), inventoryItem);
	}
	else if(item->isPharmaceuticalObject()) {
		util::ItemMessageHelper::AddPharmaceuticalDetailsToMessage(dynamic_cast<PharmaceuticalObject*>(item), inventoryItem);
	}
	else if(item->isComponent()) {
		util::ItemMessageHelper::AddComponentDetailsToMessage(dynamic_cast<Component*>(item), inventoryItem);
	}
}

void ItemMessageHelper::AddIntangibleDetailsToMessage(server::zone::objects::intangible::IntangibleObject* item,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	inventoryItem->set_crafter_name("-");
	inventoryItem->set_serial_number("-");
	inventoryItem->set_max_condition(-1);
	inventoryItem->set_condition(-1);

	if(item->isManufactureSchematic()) {
		util::ItemMessageHelper::AddManufactureSchematicDetailsTomessage(dynamic_cast<ManufactureSchematic*>(item),inventoryItem);
	}
}

void ItemMessageHelper::AddArmorDetailsToMessage(server::zone::objects::tangible::wearables::ArmorObject* armorObj,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	if(armorObj == NULL) {
		return;
	}

	ArmorItem* item = new ArmorItem();

	item->set_acid(armorObj->getAcid());
	item->set_action_encumberance(armorObj->getActionEncumbrance());
	item->set_blast(armorObj->getBlast());
	item->set_cold(armorObj->getCold());
	item->set_electricity(armorObj->getElectricity());
	item->set_energy(armorObj->getEnergy());
	item->set_health_encumberance(armorObj->getHealthEncumbrance());
	item->set_heat(armorObj->getHeat());
	item->set_kinetic(armorObj->getKinetic());
	item->set_lighsaber(armorObj->getLightSaber());
	item->set_mind_encumberance(armorObj->getMindEncumbrance());
	item->set_rating(armorObj->getRating());
	item->set_stun(armorObj->getStun());

	if(armorObj->getHitLocation() & 0x01) {
		item->add_hit_location(1);
	}

	if(armorObj->getHitLocation() & 0x02) {
		item->add_hit_location(2);
	}

	if(armorObj->getHitLocation() & 0x04) {
		item->add_hit_location(4);
	}

	if(armorObj->getHitLocation() & 0x08) {
		item->add_hit_location(8);
	}


	inventoryItem->set_allocated_armor_details(item);
}

void ItemMessageHelper::AddWeaponDetailsToMessage(server::zone::objects::tangible::weapon::WeaponObject* weaponObj,
										swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {
	if(weaponObj == NULL) {
		return;
	}

	WeaponItem* item = new WeaponItem();

	item->set_action_attack_cost(weaponObj->getActionAttackCost());
	item->set_armor_piercing(weaponObj->getArmorPiercing());
	item->set_attack_speed(weaponObj->getAttackSpeed());
	item->set_damage_radius(weaponObj->getDamageRadius());
	item->set_damage_type(weaponObj->getDamageType());
	item->set_force_attack_cost(weaponObj->getForceCost());
	item->set_health_attack_cost(weaponObj->getHealthAttackCost());
	item->set_ideal_accuracy(weaponObj->getIdealAccuracy());
	item->set_ideal_range(weaponObj->getIdealRange());
	item->set_max_damage(weaponObj->getMaxDamage());
	item->set_max_range(weaponObj->getMaxRange());
	item->set_max_range_accuracy(weaponObj->getMaxRangeAccuracy());
	item->set_min_damage(weaponObj->getMinDamage());
	item->set_mind_attack_cost(weaponObj->getMindAttackCost());
	item->set_point_blank_accuracy(weaponObj->getPointBlankAccuracy());
	item->set_point_blank_range(weaponObj->getPointBlankRange());
	item->set_weapon_type(weaponObj->getWeaponType().toCharArray());
	item->set_wound_ratio(weaponObj->getWoundsRatio());

	inventoryItem->set_allocated_weapon_details(item);

}

void ItemMessageHelper::AddResourceDetailsToMessage(server::zone::objects::resource::ResourceContainer* resourceObj,
														swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {
	if(resourceObj == NULL) {
		return;
	}

	ResourceContainerItem* item = new ResourceContainerItem();

	item->set_name(resourceObj->getSpawnName().toCharArray());
	item->set_type(resourceObj->getSpawnType().toCharArray());
	item->set_resource_id(resourceObj->getSpawnID());
	item->set_count(resourceObj->getQuantity());

	for(int i = 0; i < 8; ++i) {
		if(resourceObj->getSpawnObject()->getClass(i) != "") {
			ResourceSpawnClass* cls = item->add_classes();
			cls->set_class_name(resourceObj->getSpawnObject()->getClass(i).toCharArray());
			cls->set_stf_class(resourceObj->getSpawnObject()->getStfClass(i).toCharArray());
		}

	}

	for(int i = 0; i < 12; ++i) {

		sys::lang::String str = "";
		int val = resourceObj->getSpawnObject()->getAttributeAndValue(str,i);

		if(str != "") {
			ResourceAttribute* attr = item->add_attributes();
			attr->set_name(str.toCharArray());
			attr->set_value(val);
		}
	}

	inventoryItem->set_allocated_resource_details(item);
}

void ItemMessageHelper::AddFactoryCrateDetailsToMessage(server::zone::objects::factorycrate::FactoryCrate* crateObj,
				swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {
	if(crateObj == NULL) {
		return;
	}

	FactoryCrateItem* item = new FactoryCrateItem();
	Reference<TangibleObject*> containedItem = crateObj->getPrototype();
	item->set_count(crateObj->getUseCount());
	item->set_max_items(crateObj->getMaxCapacity());

	CharacterInventoryItem* protoItem = new CharacterInventoryItem();

	util::ItemMessageHelper::AddBaseDetailsToMessage(containedItem.castTo<SceneObject*>().get(), protoItem);
	item->set_allocated_contained_items(protoItem);
	inventoryItem->set_allocated_factory_crate_details(item);

}

void ItemMessageHelper::AddPharmaceuticalDetailsToMessage(server::zone::objects::tangible::pharmaceutical::PharmaceuticalObject* pharmaObj,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	if(pharmaObj == NULL) {
		return;
	}

	PharmaceuticalItem* item = new PharmaceuticalItem();

	item->set_area(pharmaObj->getArea());
	item->set_medicine_required(pharmaObj->getMedicineUseRequired());
	item->set_use_count(pharmaObj->getUseCount());

	if(pharmaObj->isCurePack()) {
		util::ItemMessageHelper::AddCurePackDetailsToMessage(dynamic_cast<CurePack*>(pharmaObj), item);
	}
	else if(pharmaObj->isEnhancePack()) {
		util::ItemMessageHelper::AddEnhancePackDetailsToMessage(dynamic_cast<EnhancePack*>(pharmaObj),item);
	}
	else if(pharmaObj->isRangedStimPack()) {
		util::ItemMessageHelper::AddRangedStimPackDetailsToMessage(dynamic_cast<RangedStimPack*>(pharmaObj),item);
	}
	else if(pharmaObj->isRevivePack()) {
		util::ItemMessageHelper::AddReviviePackDetailsToMessage(dynamic_cast<RevivePack*>(pharmaObj),item);
	}
	else if(pharmaObj->isStimPack()) {
		util::ItemMessageHelper::AddStimPackDetailsToMessage(dynamic_cast<StimPack*>(pharmaObj),item);
	}
	else if(pharmaObj->isWoundPack()) {
		util::ItemMessageHelper::AddWoundPackDetailsToMessage(dynamic_cast<WoundPack*>(pharmaObj),item);
	}
	else {
		item->set_effectiveness(-1);
		item->set_pharma_type(PharmaceuticalItem::UNKNOWN);
	}

	inventoryItem->set_allocated_pharmaceutical_details(item);


}

void ItemMessageHelper::AddCurePackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::CurePack* curePackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(curePackObj == NULL) {
		return;
	}
	pharmaObj->set_pharma_type(PharmaceuticalItem::CUREPACK);
	pharmaObj->set_effectiveness(curePackObj->getEffectiveness());
}

void ItemMessageHelper::AddDotPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::DotPack* dotPackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(dotPackObj == NULL) {
		return;
	}

	pharmaObj->set_pharma_type(PharmaceuticalItem::DOTPACK);
	pharmaObj->set_effectiveness(dotPackObj->getEffectiveness());

	DotPackItem* item = new DotPackItem();
	item->set_disease_unit(dotPackObj->isDiseaseDeliveryUnit());
	item->set_dot_type(dotPackObj->getDotType());
	item->set_duration(dotPackObj->getDuration());
	item->set_poison_unit(dotPackObj->isPoisonDeliveryUnit());
	item->set_pool(CreatureAttribute::getName(dotPackObj->getPool(),true).toCharArray());
	item->set_potency(dotPackObj->getPotency());

	pharmaObj->set_allocated_dot_pack_details(item);

}

void ItemMessageHelper::AddEnhancePackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::EnhancePack* enhancePackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(enhancePackObj == NULL) {
		return;
	}

	pharmaObj->set_pharma_type(PharmaceuticalItem::ENHANCEPACK);
	pharmaObj->set_effectiveness(enhancePackObj->getEffectiveness());

	EnhancePackItem* item = new EnhancePackItem();

	item->set_attribute(BuffAttribute::getName(enhancePackObj->getAttribute(), true).toCharArray());
	item->set_duration(enhancePackObj->getDuration());

	pharmaObj->set_allocated_enhance_pack_details(item);

}

void ItemMessageHelper::AddRangedStimPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::RangedStimPack* rangedStimPackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(rangedStimPackObj == NULL) {
		return;
	}

	pharmaObj->set_pharma_type(PharmaceuticalItem::RANGEDSTIMPACK);
	pharmaObj->set_effectiveness(rangedStimPackObj->getEffectiveness());

	RangedStimPackItem* item = new RangedStimPackItem();
	item->set_range_mod(rangedStimPackObj->getRangeMod());

	pharmaObj->set_allocated_ranged_stim_details(item);
}

void ItemMessageHelper::AddReviviePackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::RevivePack* revivePackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(revivePackObj == NULL) {
		return;
	}

	pharmaObj->set_pharma_type(PharmaceuticalItem::REVIVIEPACK);
	pharmaObj->set_effectiveness(-1);

	RevivePackItem* item = new RevivePackItem();
	item->set_health_healed(revivePackObj->getHealthHealed());
	item->set_health_wound_healed(revivePackObj->getHealthWoundHealed());
	item->set_action_healed(revivePackObj->getActionHealed());
	item->set_action_wound_healed(revivePackObj->getActionWoundHealed());
	item->set_mind_healed(revivePackObj->getMindHealed());
	item->set_mind_wound_healed(revivePackObj->getMindWoundHealed());

	pharmaObj->set_allocated_revivie_pack_details(item);
}

void ItemMessageHelper::AddStimPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::StimPack* stimPackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(stimPackObj == NULL) {
		return;
	}

	pharmaObj->set_pharma_type(PharmaceuticalItem::STIMPACK);
	pharmaObj->set_effectiveness(stimPackObj->getEffectiveness());
}


void ItemMessageHelper::AddWoundPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::WoundPack* woundPackObj,
		swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj) {
	if(woundPackObj == NULL) {
		return;
	}
	pharmaObj->set_pharma_type(PharmaceuticalItem::WOUNDPACK);
	pharmaObj->set_effectiveness(woundPackObj->getEffectiveness());

	WoundPackItem* item = new WoundPackItem();

	item->set_attribute(BuffAttribute::getName(woundPackObj->getAttribute(), true).toCharArray());

	pharmaObj->set_allocated_wound_pack_details(item);

}

void ItemMessageHelper::AddComponentDetailsToMessage(server::zone::objects::tangible::component::Component* component,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	if(component == NULL) {
		return;
	}
	CraftingComponentItem* craftingItem = new CraftingComponentItem();
	inventoryItem->set_allocated_crafting_component_details(craftingItem);
	for(int i = 0; i < component->getPropertyCount(); ++i) {
		sys::lang::String property = component->getProperty(i);
		if(property != "") {
			CraftingComponentAttribute* attr = craftingItem->add_attributes();
			attr->set_id(property.toCharArray());
			attr->set_precision(component->getAttributePrecision(property));
			attr->set_tite(component->getAttributeTitle(property).toCharArray());
			attr->set_value(component->getAttributeValue(property));
			attr->set_hidden(component->getAttributeHidden(property));
		}
	}

}

void ItemMessageHelper::AddManufactureSchematicDetailsTomessage(server::zone::objects::manufactureschematic::ManufactureSchematic* schemObj,
		swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem) {

	if(schemObj == NULL) {
		return;
	}
	//inventoryItem->set_crafter_name(schemObj->getCrafter()->getFirstName().toCharArray());
	ManufacturingSchematicItem* mfgItem = new ManufacturingSchematicItem();
	CharacterInventoryItem* prototype = new CharacterInventoryItem();
	inventoryItem->set_allocated_mfg_schem_details(mfgItem);
	mfgItem->set_allocated_prototype_details(prototype);


	util::ItemMessageHelper::AddBaseDetailsToMessage(dynamic_cast<SceneObject*>(schemObj->getPrototype()), prototype);

	mfgItem->set_manufacture_limit(schemObj->getManufactureLimit());

	for(int i = 0; i < schemObj->getSlotCount(); i++) {
		IngredientSlot* slot = schemObj->getSlot(i);
		IngredientItem* item = mfgItem->add_ingredients();
		item->set_identical(slot->requiresIdentical());
		item->set_ingredient_slot_name(slot->getSlotName().toCharArray());
		item->set_required_quantity(slot->getQuantityNeeded());

		CharacterInventoryItem* ingredient = new CharacterInventoryItem();
		item->set_allocated_ingredient(ingredient);
		util::ItemMessageHelper::AddBaseDetailsToMessage(slot->getFactoryIngredient(), ingredient);
	}

	for(int i = 0; i < schemObj->getBlueprintSize(); i++) {
		BlueprintEntry* entry = schemObj->getBlueprintEntry(i);
		BlueprintEntryItem* entryItem = mfgItem->add_blueprint_entries();
		entryItem->set_display_name(entry->getDisplayedName().toCharArray());
		entryItem->set_identical(entry->needsIdentical());
		entryItem->set_key(entry->getKey().toCharArray());
		entryItem->set_quantity(entry->getQuantity());
		entryItem->set_serial(entry->getSerial().toCharArray());
		entryItem->set_type(entry->getType().toCharArray());
	}
}




