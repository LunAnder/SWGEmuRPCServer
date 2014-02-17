/*
 * RPCServer.h
 *
 *  Created on: Jan 4, 2014
 *      Author: swgemu
 */

#ifndef RPCSERVER_H_
#define RPCSERVER_H_

#include "ExportRPCServer.h"

namespace engine {
 namespace log {
 	 class Logger;
 }
}

namespace server {
 namespace conf {
 	 class ConfigManager;
 }
 namespace zone {
 	 class ZoneServer;
 }
}


namespace swgemurpcserver {
	namespace rpc {

		class RPCServerImpl;

		class SWGEMURPCSERVER_EXPORT RPCServer {
			private:
			engine::log::Logger* logger;
			RPCServerImpl* rpcServerImpl;

			public:
			RPCServer();
			~RPCServer();
			void start(ConfigManager* conf, ZoneServer* zone);
			void stop();
		};
	}
}

using namespace swgemurpcserver::rpc;


#endif /* RPCSERVER_H_ */
