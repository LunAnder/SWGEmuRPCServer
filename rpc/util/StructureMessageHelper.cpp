/*
 * StructureMessageHelper.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: swgemu
 */

#include <iostream>
#include <google/protobuf/text_format.h>
#include <RCFProto.hpp>
#include "rpc/generatedpb/StructureDetails.pb.h"
#include "StructureMessageHelper.h"
#include "../../../MMOCoreORB/src/server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "../../../MMOEngine/include/engine/core/ManagedReference.h"
#include "../../../MMOEngine/include/system/lang/ref/Reference.h"
#include "../../../MMOEngine/include/system/util/ArrayList.h"
#include "../../../MMOEngine/include/system/util/VectorMap.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/Zone.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/resource/ResourceContainer.h"
#include "../../../MMOCoreORB/src/server/zone/objects/scene/variables/DeltaVector.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/cell/CellObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/building/BuildingObject.h"
#include "../../../MMOCoreORB/src/server/zone/objects/installation/HopperList.h"
#include "../../../MMOCoreORB/src/server/zone/templates/SharedObjectTemplate.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/installation/factory/FactoryObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/installation/harvester/HarvesterObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/installation/InstallationObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/structure/StructureObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/managers/player/PlayerManager.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/scene/SceneObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/TangibleObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/player/PlayerObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/creature/CreatureObject.h"
#include "../../../MMOCoreORB/src/server/zone/objects/scene/variables/StringId.h"
#include "ItemMessageHelper.h"

StructureMessageHelper::StructureMessageHelper() {

}

void StructureMessageHelper::AddStructureDetailsToMessage(server::zone::objects::structure::StructureObject* structreObj,
						swgemurpcserver::rpc::SWGEmuStructureItemDetails* structDetails) {

	if(structreObj == NULL) {
		return;
	}

	structDetails->set_portals_file_name(structreObj->getObjectTemplate()->getPortalLayoutFilename().toCharArray());
	structDetails->set_template_file_name(structreObj->getObjectTemplate()->getTemplateFileName().toCharArray());
	structDetails->set_appearance_file_name(structreObj->getObjectTemplate()->getAppearanceFilename().toCharArray());
	structDetails->set_display_name(structreObj->getDisplayedName().toCharArray());
	structDetails->set_object_id(structreObj->getObjectID());
	structDetails->set_object_name(structreObj->getObjectName()->getFullPath().toCharArray());
	structDetails->set_owner_display_name(structreObj->getOwnerCreatureObject()->getDisplayedName().toCharArray());
	structDetails->set_owner_object_id(structreObj->getOwnerCreatureObject()->getObjectID());
	structDetails->set_world_x(structreObj->getWorldPositionX());
	structDetails->set_world_y(structreObj->getWorldPositionY());
	structDetails->set_world_z(structreObj->getWorldPositionZ());
	structDetails->set_zone(structreObj->getZone()->getZoneName().toCharArray());
	structDetails->set_power(structreObj->getSurplusPower());
	structDetails->set_maintenance(structreObj->getSurplusMaintenance());
	structDetails->set_decay_percent(structreObj->getDecayPercentage());
	structDetails->set_lot_size(structreObj->getLotSize());

	PlayerObject* onwerPlayer = dynamic_cast<PlayerObject*>(structreObj->getOwnerCreatureObject());

	if(onwerPlayer != NULL) {
		structDetails->set_owner_account_id(onwerPlayer->getAccountID());
	}

	SharedStructureObjectTemplate* structTempalte = dynamic_cast<SharedStructureObjectTemplate*>(structreObj->getObjectTemplate());

	for(int i = 0; i < structTempalte->getTotalAllowedZones(); i++ ) {
		structDetails->add_buildable_zones(structTempalte->getAllowedZone(i).toCharArray());
	}


	if(structreObj->isBuildingObject()) {
		util::StructureMessageHelper::AddBuildingDetailsToMessage(dynamic_cast<BuildingObject*>(structreObj), structDetails);
	}
	else if(structreObj->isInstallationObject()) {
		util::StructureMessageHelper::AddInstallationDetailsToMessage(dynamic_cast<InstallationObject*>(structreObj), structDetails);
	}
}

void StructureMessageHelper::AddBuildingDetailsToMessage(server::zone::objects::building::BuildingObject* buildingObj,
		swgemurpcserver::rpc::SWGEmuStructureItemDetails* structDetails) {

	BuildingItemDetails* buildingDetails = new BuildingItemDetails();
	for(int i = 1; i < buildingObj->getTotalCellNumber(); i++ ) {
		CellObject* cell = buildingObj->getCell(i);
		if(cell != NULL) {
			for(int i = 0; i < cell->getContainerObjectsSize(); i++) {
				Reference<SceneObject*> containedItem = cell->getContainerObject(i);
				util::ItemMessageHelper::AddBaseDetailsToMessage(containedItem.get(), buildingDetails->add_contained_items());
			}
		}
	}

	structDetails->set_allocated_building_details(buildingDetails);
}

void StructureMessageHelper::AddInstallationDetailsToMessage(server::zone::objects::installation::InstallationObject* instObj,
		swgemurpcserver::rpc::SWGEmuStructureItemDetails* structDetails) {

	if(instObj == NULL) {
		return;
	}

	InstallationItemDetails* instItemDetails = new InstallationItemDetails();
	instItemDetails->set_actual_rate(instObj->getActualRate());
	instItemDetails->set_operating(instObj->isOperating());
	instItemDetails->set_max_hopper_size(instObj->getHopperSizeMax());

	structDetails->set_allocated_installation_details(instItemDetails);

	if(instObj->isHarvesterObject()) {
		util::StructureMessageHelper::AddHarvesterDetailsToMessage(dynamic_cast<HarvesterObject*>(instObj),instItemDetails);
	}
	else if(instObj->isFactory()) {
		util::StructureMessageHelper::AddFactoryDetailsToMessage(dynamic_cast<FactoryObject*>(instObj), instItemDetails);
	}
}

void StructureMessageHelper::AddHarvesterDetailsToMessage(server::zone::objects::installation::harvester::HarvesterObject* instObj,
		swgemurpcserver::rpc::InstallationItemDetails* instItemDetails) {

	HarvesterItemDetails* harvesterItem = new HarvesterItemDetails();
	instItemDetails->set_allocated_harvester_details(harvesterItem);
	harvesterItem->set_extraction_rate(instObj->getExtractionRate());

	HopperList* hopper = instObj->getHopperList();
	for(int i = 0; i < hopper->size(); i++) {
		ManagedReference<ResourceContainer*> resource = hopper->get(i);
		util::ItemMessageHelper::AddBaseDetailsToMessage(resource.castTo<SceneObject*>().get(), instItemDetails->add_hopper_items());
	}

}

void StructureMessageHelper::AddFactoryDetailsToMessage(server::zone::objects::installation::factory::FactoryObject* factoryObj,
		swgemurpcserver::rpc::InstallationItemDetails* instItemDetails) {

	FactoryItemDetails* factoryDetails = new FactoryItemDetails();
	instItemDetails->set_allocated_factory_details(factoryDetails);

	ManagedReference<SceneObject*> schematic = factoryObj->getContainerObject(0);
	if(schematic != NULL && schematic->isManufactureSchematic()) {
		CharacterInventoryItem* schemItem = new CharacterInventoryItem();
		schemItem->set_crafter_name("");
		schemItem->set_serial_number("");
		factoryDetails->set_allocated_schematic(schemItem);
		util::ItemMessageHelper::AddBaseDetailsToMessage(schematic.get(), schemItem);
	}

	ManagedReference<SceneObject*> outputHopper = factoryObj->getSlottedObject("output_hopper");

	for(int i = 0; i < outputHopper->getContainerObjectsSize(); i++) {
		swgemurpcserver::rpc::util::ItemMessageHelper::AddBaseDetailsToMessage(outputHopper->getContainerObject(i).get(),
				instItemDetails->add_hopper_items());
	}
	ManagedReference<SceneObject*> inputHopper = factoryObj->getSlottedObject("ingredient_hopper");

	for(int i = 0; i < inputHopper->getContainerObjectsSize(); i++) {
		swgemurpcserver::rpc::util::ItemMessageHelper::AddBaseDetailsToMessage(inputHopper->getContainerObject(i).get(),
				factoryDetails->add_ingredient_items());
	}

}
