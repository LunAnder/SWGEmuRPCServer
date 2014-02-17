/*
 * StructureMessageHelper.h
 *
 *  Created on: Jan 18, 2014
 *      Author: swgemu
 */

#ifndef STRUCTUREMESSAGEHELPER_H_
#define STRUCTUREMESSAGEHELPER_H_

namespace swgemurpcserver {
namespace rpc {

class SWGEmuStructureItemDetails;
}}

namespace server {
namespace zone {
namespace objects {
namespace structure {

class StructureObject;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace building {

class BuildingObject;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace installation {

class InstallationObject;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace installation {
namespace harvester {

class HarvesterObject;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace installation {
namespace factory {

class FactoryObject;
}}}}}

namespace swgemurpcserver {
	namespace rpc {
		namespace util {
			class StructureMessageHelper {
			private:
				StructureMessageHelper();
			public:
				static void AddStructureDetailsToMessage(server::zone::objects::structure::StructureObject* structreObj,
						swgemurpcserver::rpc::SWGEmuStructureItemDetails* structDetails);
				static void AddBuildingDetailsToMessage(server::zone::objects::building::BuildingObject* buildingObj,
						swgemurpcserver::rpc::SWGEmuStructureItemDetails* structDetails);
				static void AddInstallationDetailsToMessage(server::zone::objects::installation::InstallationObject* instObj,
						swgemurpcserver::rpc::SWGEmuStructureItemDetails* structDetails);
				static void AddHarvesterDetailsToMessage(server::zone::objects::installation::harvester::HarvesterObject* instObj,
						swgemurpcserver::rpc::InstallationItemDetails* instItemDetails);
				static void AddFactoryDetailsToMessage(server::zone::objects::installation::factory::FactoryObject* factoryObj,
						swgemurpcserver::rpc::InstallationItemDetails* instItemDetails);
			};
		}
	}
}

using namespace swgemurpcserver::rpc::util;

#endif /* STRUCTUREMESSAGEHELPER_H_ */
