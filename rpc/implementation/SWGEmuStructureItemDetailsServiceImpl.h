/*
 * SWGEmuStructureItemDetailsService.h
 *
 *  Created on: Jan 14, 2014
 *      Author: swgemu
 */

#ifndef SWGEMUSTRUCTUREITEMDETAILSSERVICEIMPL_H_
#define SWGEMUSTRUCTUREITEMDETAILSSERVICEIMPL_H_

#include "rpc/generatedpb/StructureDetails.pb.h"
#include "../../../MMOEngine/include/engine/core/ManagedReference.h"
#include "../../../MMOCoreORB/src/autogen/server/zone/ZoneServer.h"

namespace engine {
 namespace log {
 	 class Logger;
 }
}


namespace swgemurpcserver {
 	 namespace rpc {
 	class SWGEmuStructureItemDetailsServiceImpl : public swgemurpcserver::rpc::SWGEmuStructureItemDetailsService {

 	private:
 		engine::core::ManagedReference<server::zone::ZoneServer*> zoneServer;
 		engine::log::Logger* logger;

 	public:
 		SWGEmuStructureItemDetailsServiceImpl();
 		void setZoneServer(engine::core::ManagedReference<server::zone::ZoneServer*> server);
 		virtual void GetStructureItemDetails(::google::protobuf::RpcController* controller,
 		                       const ::swgemurpcserver::rpc::GetStructureItemDetailsRequest* request,
 		                       ::swgemurpcserver::rpc::GetStructureItemDetailsResponse* response,
 		                       ::google::protobuf::Closure* done);
 	};
 }
}





using namespace swgemurpcserver::rpc;



#endif /* SWGEMUSTRUCTUREITEMDETAILSSERVICE_H_ */
