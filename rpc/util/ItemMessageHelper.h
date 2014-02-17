/*
 * ItemMessageHelper.h
 *
 *  Created on: Jan 17, 2014
 *      Author: swgemu
 */

#ifndef ITEMMESSAGEHELPER_H_
#define ITEMMESSAGEHELPER_H_
namespace swgemurpcserver {
	namespace rpc {
		class CharacterInventoryItem;
	}
}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace wearables {
	class ArmorObject;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {

class TangibleObject;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace weapon {

class WeaponObject;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace resource {

class ResourceContainer;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace factorycrate {

class FactoryCrate;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class PharmaceuticalObject;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class CurePack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class DotPack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class EnhancePack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class RangedStimPack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class RevivePack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class StimPack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace pharmaceutical {

class WoundPack;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace component {

class Component;
}}}}}

namespace server {
namespace zone {
namespace objects {
namespace intangible {

class IntangibleObject;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace manufactureschematic {

class ManufactureSchematic;
}}}}

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}}}}

namespace swgemurpcserver {
	namespace rpc {
		namespace util {
			class ItemMessageHelper {
			private:
				ItemMessageHelper();
			public:
				static void AddBaseDetailsToMessage(server::zone::objects::scene::SceneObject* scene,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddTangibleDetailsToMessage(server::zone::objects::tangible::TangibleObject* item,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddIntangibleDetailsToMessage(server::zone::objects::intangible::IntangibleObject* item,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddArmorDetailsToMessage(server::zone::objects::tangible::wearables::ArmorObject* armorObj,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddWeaponDetailsToMessage(server::zone::objects::tangible::weapon::WeaponObject* weaponObj,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddResourceDetailsToMessage(server::zone::objects::resource::ResourceContainer* resourceObj,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddFactoryCrateDetailsToMessage(server::zone::objects::factorycrate::FactoryCrate* resourceObj,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddPharmaceuticalDetailsToMessage(server::zone::objects::tangible::pharmaceutical::PharmaceuticalObject* resourceObj,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddCurePackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::CurePack* curePackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddDotPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::DotPack* dotPackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddEnhancePackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::EnhancePack* enhancePackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddRangedStimPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::RangedStimPack* rangedStimPackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddReviviePackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::RevivePack* revivePackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddStimPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::StimPack* stimPackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddWoundPackDetailsToMessage(server::zone::objects::tangible::pharmaceutical::WoundPack* woundPackObj,
						swgemurpcserver::rpc::PharmaceuticalItem* pharmaObj);
				static void AddComponentDetailsToMessage(server::zone::objects::tangible::component::Component* component,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);
				static void AddManufactureSchematicDetailsTomessage(server::zone::objects::manufactureschematic::ManufactureSchematic* schemObj,
						swgemurpcserver::rpc::CharacterInventoryItem* inventoryItem);

			};
		}
	}
}

using namespace swgemurpcserver::rpc::util;

#endif /* ITEMMESSAGEHELPER_H_ */
