/*
 * RPCServerImpl.h
 *
 *  Created on: Jan 10, 2014
 *      Author: swgemu
 */

#ifndef RPCSERVERIMPL_H_
#define RPCSERVERIMPL_H_

#include <RCFProto.hpp>
#include "rpc/implementation/SWGEmuAccountServiceImpl.h"
#include "rpc/implementation/SWGEmuCharacterDetailsServiceImpl.h"
#include "rpc/implementation/SWGEmuStructureItemDetailsServiceImpl.h"
#include "../../MMOCoreORB/src/autogen/server/zone/ZoneServer.h"

/*namespace RCF {
	class RcfProtoServer;
}*/

/*namespace server {
 namespace conf {
 	 class ConfigManager;
 }
}*/

namespace engine {
 namespace log {
 	 class Logger;
 }
}



namespace swgemurpcserver {
	namespace rpc {
		class RPCServerImpl {
			private:
			ManagedReference<ZoneServer*> zoneServer;
			server::conf::ConfigManager* configManager;
			engine::log::Logger* logger;

			RCF::RcfProtoServer* rcfServer;
			SWGEmuAccountServiceImpl* serviceImpl;
			SWGEmuCharacterDetailsServiceImpl* detailsImpl;
			SWGEmuStructureItemDetailsServiceImpl* structDetailsImpl;

			public:
			RPCServerImpl();
			~RPCServerImpl();
			void start(ConfigManager* conf, ZoneServer*);
			void stop();
		};
	}
}

using namespace swgemurpcserver::rpc;

#endif /* RPCSERVERIMPL_H_ */
