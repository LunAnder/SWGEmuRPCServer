/*
 * SWGEmuInterfaceServiceImpl.h
 *
 *  Created on: Jan 5, 2014
 *      Author: swgemu
 */

#ifndef SWGEMUINTERFACESERVICEIMPL_H_
#define SWGEMUINTERFACESERVICEIMPL_H_

#include "rpc/generatedpb/AccountRequest.pb.h"
#include "../../../MMOEngine/include/engine/core/ManagedReference.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/ZoneServer.h"

namespace engine {
 namespace log {
 	 class Logger;
 }
}


namespace swgemurpcserver {
	namespace rpc {
		class SWGEmuAccountServiceImpl : public swgemurpcserver::rpc::SWGEmuAccountService {
		private:
			engine::core::ManagedReference<server::zone::ZoneServer*> zoneServer;
			engine::log::Logger* logger;
			std::string dbSecret;
		public:
			SWGEmuAccountServiceImpl();
			virtual void GetAccount(
					google::protobuf::RpcController * controller,
					const swgemurpcserver::rpc::GetAccountRequest * request,
					swgemurpcserver::rpc::GetAccountResponse * response,
					google::protobuf::Closure * done);

			void setZoneServer(engine::core::ManagedReference<server::zone::ZoneServer*> server);
			void setDBSecret(const char* dbSecret);
			void setDBSecret(std::string dbSecret);
		};
	}
}

using namespace swgemurpcserver::rpc;

#endif /* SWGEMUINTERFACESERVICEIMPL_H_ */
