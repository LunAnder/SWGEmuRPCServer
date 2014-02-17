/*
 * SWGEmuStructureItemDetailsServiceImpl.cpp
 *
 *  Created on: Jan 14, 2014
 *      Author: swgemu
 */
#include <iostream>
#include <RCFProto.hpp>
#include "SWGEmuStructureItemDetailsServiceImpl.h"
#include "../../../MMOEngine/include/system/lang/ref/Reference.h"
#include "../../../MMOEngine/include/system/util/ArrayList.h"
#include "../../../MMOEngine/include/system/util/VectorMap.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/Zone.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/resource/ResourceContainer.h"
#include "../../../MMOCoreORB/src/server/zone/objects/scene/variables/DeltaVector.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/cell/CellObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/building/BuildingObject.h"
#include "../../../MMOCoreORB/src/server/zone/objects/installation/HopperList.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/installation/InstallationObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/structure/StructureObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/managers/player/PlayerManager.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/scene/SceneObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/tangible/TangibleObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/player/PlayerObject.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/objects/creature/CreatureObject.h"
#include "../../../MMOCoreORB/src/server/zone/objects/scene/variables/StringId.h"
#include "../../../MMOEngine/include/engine/log/Logger.h"
#include "rpc/util/StructureMessageHelper.h"


SWGEmuStructureItemDetailsServiceImpl::SWGEmuStructureItemDetailsServiceImpl() {
	zoneServer = NULL;
	logger = new engine::log::Logger("SWGEmuStructureItemDetailsServiceImpl");
}


void SWGEmuStructureItemDetailsServiceImpl::setZoneServer(engine::core::ManagedReference<server::zone::ZoneServer*> server) {
	logger->info("set zone server",true);
	zoneServer = server;
}

void SWGEmuStructureItemDetailsServiceImpl::GetStructureItemDetails(::google::protobuf::RpcController* controller,
	                       const ::swgemurpcserver::rpc::GetStructureItemDetailsRequest* request,
	                       ::swgemurpcserver::rpc::GetStructureItemDetailsResponse* response,
	                       ::google::protobuf::Closure* done) {

	logger->info("GetStructureItemDetails",true);

	try {

	if(request->has_object_id() && request->has_owner_object_id()) {
		Reference<SceneObject*> obj = zoneServer->getObject(request->object_id());
		if(obj != NULL) {
			Reference<StructureObject*> structure = obj.castTo<StructureObject*>();
			if(structure != NULL) {
				util::StructureMessageHelper::AddStructureDetailsToMessage(structure.get(),response->add_structures());
			}
		}
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
