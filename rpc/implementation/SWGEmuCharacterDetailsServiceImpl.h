/*
 * SWGEmuCharacterDetailsServiceImpl.h
 *
 *  Created on: Jan 13, 2014
 *      Author: swgemu
 */

#ifndef SWGEMUCHARACTERDETAILSSERVICEIMPL_H_
#define SWGEMUCHARACTERDETAILSSERVICEIMPL_H_

#include "rpc/generatedpb/CharacterDetails.pb.h"
#include "../../../MMOEngine/include/engine/core/ManagedReference.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/ZoneServer.h"

namespace engine {
 namespace log {
 	 class Logger;
 }
}


namespace swgemurpcserver {
 	 namespace rpc {
 	 	 class SWGEmuCharacterDetailsServiceImpl : public swgemurpcserver::rpc::SWGEmuCharacterDetailsService {
 	 	 private:
 	 		 engine::core::ManagedReference<server::zone::ZoneServer*> zoneServer;
 	 		 engine::log::Logger* logger;
 	 	 public:
 	 		 SWGEmuCharacterDetailsServiceImpl();
 	 		 virtual void GetCharacterDetails(
 	 				 ::google::protobuf::RpcController* controller,
					 const ::swgemurpcserver::rpc::GetCharacterDetailsRequest* request,
					 ::swgemurpcserver::rpc::GetCharacterDetailsResponse* response,
					 ::google::protobuf::Closure* done);

 	 		 void setZoneServer(engine::core::ManagedReference<server::zone::ZoneServer*> server);
 	 };
 }
}

using namespace swgemurpcserver::rpc;

#endif /* SWGEMUCHARACTERDETAILSSERVICEIMPL_H_ */
