/*
 * SWGEmuCharacterDetailsServiceImpl.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: swgemu
 */

#include <google/protobuf/text_format.h>
#include <RCFProto.hpp>
#include "SWGEmuCharacterDetailsServiceImpl.h"
#include "../../../MMOEngine/include/system/lang/ref/Reference.h"
#include "../../../MMOEngine/include/system/util/ArrayList.h"
#include "../../../MMOEngine/include/system/util/VectorMap.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/structure/StructureObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/managers/player/PlayerManager.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/scene/SceneObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/wearables/ArmorObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/TangibleObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/player/PlayerObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/creature/CreatureObject.h"
#include "../../../MMOCoreORB/src/server/zone/objects/scene/variables/StringId.h"
#include "../../../MMOEngine/include/engine/log/Logger.h"
#include "rpc/util/ItemMessageHelper.h"

SWGEmuCharacterDetailsServiceImpl::SWGEmuCharacterDetailsServiceImpl() {
	zoneServer = NULL;
	logger = new engine::log::Logger("SWGEmuCharacterDetailsServiceImpl");
}

void SWGEmuCharacterDetailsServiceImpl::setZoneServer(engine::core::ManagedReference<server::zone::ZoneServer*> server) {
	logger->info("zone server set", true);
	zoneServer = server;
}

void SWGEmuCharacterDetailsServiceImpl::GetCharacterDetails(
			::google::protobuf::RpcController* controller,
					   const ::swgemurpcserver::rpc::GetCharacterDetailsRequest* request,
					   ::swgemurpcserver::rpc::GetCharacterDetailsResponse* response,
					   ::google::protobuf::Closure* done) {
	logger->info("GetCharacterDetails");
	try {


	Reference<CreatureObject*> creatureObj = zoneServer->getPlayerManager()->getPlayer(sys::lang::String(request->first_name().c_str()));

	if(creatureObj == NULL && request->has_object_id()) {
		Reference<SceneObject* > creatureByObjID =  zoneServer->getObject(request->object_id());
		logger->info("found object by object id.. trying to cast", true);
		if(creatureByObjID != NULL) {

			logger->info("cast successful",true);

			creatureObj = creatureByObjID.castTo<CreatureObject*>();

		}
	}


	if(creatureObj != NULL) {
		SWGEmuCharacterDetail* detail = response->add_character_details();
		logger->info(sys::lang::String("found character with name ") + creatureObj->getFirstName(),true);
		Reference<PlayerObject *> playerObj = creatureObj->getPlayerObject();
		logger->info("getting player object", true);
		if(playerObj != NULL) {

			detail->set_account_id(playerObj->getAccountID());
			detail->set_first_name(creatureObj->getFirstName().toCharArray());
			detail->set_sur_name(creatureObj->getLastName().toCharArray());
			detail->set_object_id(creatureObj->getObjectID());
			detail->set_biography(playerObj->getBiography().toString().toCharArray());
			detail->set_bank_credits(creatureObj->getBankCredits());
			detail->set_cash_credits(creatureObj->getCashCredits());
			detail->set_base_health(creatureObj->getBaseHAM(0));
			detail->set_base_action(creatureObj->getBaseHAM(1));
			detail->set_base_mind(creatureObj->getBaseHAM(2));
			detail->set_remaining_plots(playerObj->getLotsRemaining());
			detail->set_title(playerObj->getTitle().toCharArray());

			int ownedStructureCount = playerObj->getTotalOwnedStructureCount();
			int totalLotsCount = playerObj->getLotsRemaining();

			for(int i = 0; i < ownedStructureCount; i++) {
				long structID = playerObj->getOwnedStructure(i);
				Reference<SceneObject*> ownedStructScene = zoneServer->getObject(structID);
				if(ownedStructScene != NULL) {
					Reference<StructureObject*> ownedStrucutre = ownedStructScene.castTo<StructureObject*>();
					totalLotsCount += ownedStrucutre->getLotSize();
					if(ownedStrucutre != NULL) {
						SWGEmuCharacterStructureItem* structure = detail->add_structures();
						structure->set_object_id(ownedStructScene->getObjectID());
						structure->set_object_name(ownedStructScene->getObjectName()->getFullPath().toCharArray());
						structure->set_display_name(ownedStructScene->getDisplayedName().toCharArray());
					}
				}
			}
			detail->set_maximumim_plots(totalLotsCount);


			ManagedReference<SceneObject*> inventory = creatureObj->getSlottedObject(sys::lang::String("inventory"));

			if(inventory != NULL) {
				VectorMap<unsigned long long, ManagedReference<SceneObject* > >* items = inventory->getContainerObjects();

				if(items != NULL) {
					for(int i = 0; i < items->size(); i++) {
						swgemurpcserver::rpc::util::ItemMessageHelper::AddBaseDetailsToMessage(items->get(i).get(), detail->add_inventory_items());
					}
				}
			}
		}
		else {
			logger->info("player object was null", true);
		}
	}
	else {
		logger->info(sys::lang::String("No character found with requested name: ") + sys::lang::String(request->first_name().c_str()), true);
	}
	}
	catch(const RCF::Exception & e) {
		logger->error((std::string("RCF Exception") + e.getErrorString()).c_str());
	}
	catch(sys::lang::Exception & e) {
		logger->info(sys::lang::String("sys::lang::Exception: ") + e.getMessage().toCharArray(), true);
	}
	catch(std::exception & e) {
		logger->info((std::string("std::exception: ") + e.what()).c_str(), true);
	}
	done->Run();

}

