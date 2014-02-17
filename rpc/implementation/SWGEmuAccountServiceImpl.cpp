/*
 * SWGEmuInterfaceServiceImpl.cpp
 *
 *  Created on: Jan 5, 2014
 *      Author: swgemu
 */

#include <iostream>
#include <RCFProto.hpp>
#include "SWGEmuAccountServiceImpl.h"
#include "../../../MMOEngine/include/engine/db/ResultSet.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/managers/player/PlayerManager.h"
#include "../../../MMOCoreORB/src/autogen/server/login/account/Account.h"
#include "../../../MMOCoreORB/src/server/login/objects/CharacterList.h"
#include "../../../MMOCoreORB/src/server/login/objects/CharacterListEntry.h"
#include "../../../MMOEngine/include/engine/log/Logger.h"
#include "../../../MMOEngine/include/engine/db/Database.h"
#include "../../../MMOCoreORB/src/server/db/ServerDatabase.h"
#include "../../../MMOEngine/include/system/security/Crypto.h"


SWGEmuAccountServiceImpl::SWGEmuAccountServiceImpl()
{
	zoneServer = NULL;
	logger = new engine::log::Logger("SWGEmuAccountServiceImpl");
}


void SWGEmuAccountServiceImpl::setZoneServer(engine::core::ManagedReference<server::zone::ZoneServer*> server) {
	zoneServer = server;
}

void SWGEmuAccountServiceImpl::setDBSecret(const char* secret) {
	dbSecret = std::string(secret);
}

void SWGEmuAccountServiceImpl::setDBSecret(std::string secret) {
	dbSecret = secret;
}

void SWGEmuAccountServiceImpl::GetAccount(
		google::protobuf::RpcController * controller,
		const GetAccountRequest * request,
		GetAccountResponse * response,
		google::protobuf::Closure * done) {

	try {

		server::login::account::Account* foundAccount = NULL;

		if(request->search_type() == swgemurpcserver::rpc::GetAccountRequest::ACCOUNTNAME && request->has_user_name()) {

			foundAccount = zoneServer->getPlayerManager()->getAccount(request->user_name().c_str());
		}
		else if(request->search_type() == swgemurpcserver::rpc::GetAccountRequest::ACCOUNTID && request->has_account_id()) {
			foundAccount = zoneServer->getPlayerManager()->getAccount(request->account_id());
		}


		if(foundAccount != NULL) {

			bool credentailsMatch = false;
			if(request->has_password()) {
				logger->info("has password, checking...",true);
				const sys::lang::String userName = sys::lang::String(request->user_name().c_str());
				const sys::lang::String password = sys::lang::String(request->password().c_str());

				std::stringstream query;
				query << "SELECT a.account_id, a.username, a.password, a.salt FROM accounts a WHERE a.username = '" << request->user_name().c_str() << "';";

				ResultSet* result = ServerDatabase::instance()->executeQuery(query.str().c_str());

				uint accountID = -1;
				if(result == NULL || result->size() <= 0 || !result->next()) {
					logger->info("result from db is null or empty", true);

				}
				else {
					accountID = result->getUnsignedInt(0);
				}

				if(accountID != foundAccount->getAccountID()) {
					logger->info("found account id does not match the account retrieved from the database",true);
				}
				else {
					sys::lang::String pwHash = result->getString(2);
					sys::lang::String pwSalt = result->getString(3);
					sys::lang::String hashedProvidedPW;

					if(pwSalt == "") {
						hashedProvidedPW = Crypto::SHA1Hash(sys::lang::String(request->password().c_str()));
					} else {
						hashedProvidedPW = Crypto::SHA256Hash(sys::lang::String((dbSecret + request->password()).c_str()) + pwSalt);
					}


					if(pwHash != hashedProvidedPW) {
						logger->info("invalid password",true);
						done->Run();
					}
					else {
						credentailsMatch = true;
					}
				}
			}

			if(foundAccount != NULL && (!request->has_password() || credentailsMatch)) {
				swgemurpcserver::rpc::SWGEmuAccount* resAccount = response->add_accounts();
				resAccount->set_account_id(foundAccount->getAccountID());
				resAccount->set_user_name(foundAccount->getUsername().toCharArray());
				resAccount->set_active(foundAccount->isActive());
				resAccount->set_created_time(foundAccount->getTimeCreated());

				CharacterList* characters = foundAccount->getCharacterList();

				resAccount->set_character_count(characters->size());

				if(characters->size() > 0) {
					for(int i = 0; i < characters->size(); i++) {
						swgemurpcserver::rpc::SWGEmuAccountCharacter* character = resAccount->add_characters();
						CharacterListEntry* entry = &characters->get(i);
						character->set_account_id(entry->getAccountID());
						character->set_object_id(entry->getObjectID());
						character->set_galaxy_id(entry->getGalaxyID());
						character->set_create_time(entry->getCreationDate().getMiliTime());
						character->set_gender(entry->getGender());
						character->set_race(entry->getRace());
						character->set_first_name(entry->getFirstName().toCharArray());
						character->set_sur_name(entry->getSurName().toCharArray());
						character->set_galaxy_name(entry->getGalaxyName().toCharArray());

					}
				}
			}
			else {
				logger->info("no account found",true);
			}
		}
		else {
			logger->info("no account found",true);
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
