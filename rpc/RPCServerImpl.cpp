/*
 * RPCServerImpl.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: swgemu
 */


#include <RCFProto.hpp>
//#include <RCF/ThreadPool.hpp>
#include <exception>
#include <map>
#include <ostream>
//#include <RCF/NamedPipeEndpoint.hpp>

#include "RPCServerImpl.h"
#include "../../MMOCoreORB/src/server/conf/ConfigManager.h"
#include "../../MMOEngine/include/engine/log/Logger.h"
#include "../../MMOEngine/include/system/lang/String.h"
#include "../../MMOEngine/include/engine/orb/DistributedObjectBroker.h"

RPCServerImpl::RPCServerImpl() {
	configManager = NULL;
	//const char* loggerName = "RPCServerImpl";
	logger = new engine::log::Logger(sys::lang::String("RPCServerImpl"));
	serviceImpl = new swgemurpcserver::rpc::SWGEmuAccountServiceImpl();
	detailsImpl = new swgemurpcserver::rpc::SWGEmuCharacterDetailsServiceImpl();
	structDetailsImpl = new swgemurpcserver::rpc::SWGEmuStructureItemDetailsServiceImpl();
	//threadPoolPtr = new RCF::ThreadPoolPtr(new RCF::ThreadPool(5));
}

RPCServerImpl::~RPCServerImpl() {
	logger->info("destroyed", true);
	configManager = NULL;
	delete logger;
	delete serviceImpl;
	delete detailsImpl;
	delete structDetailsImpl;
}

void RPCServerImpl::start(server::conf::ConfigManager* config, server::zone::ZoneServer* zone) {
	configManager = config;
	zoneServer = zone;
	try
	{
		logger->info("RCF Init start",true);

		RCF::init();

		const std::string logPath (configManager->getRPCLogPath().toCharArray());

		logger->info((std::string("RPC log path: ") + logPath).c_str(),true);

		RCF::enableLogging(RCF::LogToFile(logPath), RCF::LogLevel_4, "");

		serviceImpl->setZoneServer(zoneServer);
		serviceImpl->setDBSecret(configManager->getDBSecret().toCharArray());
		detailsImpl->setZoneServer(zoneServer);
		structDetailsImpl->setZoneServer(zoneServer);

		std::string endpointType (configManager->getRPCEndpointType().toCharArray());

		logger->info((std::string("RPC Server Type is: ") + endpointType).c_str(),true);

		std::cout << " endpointAddr " << configManager->getRPCEndpointAddress().toCharArray() << std::endl;

		std::string ip(configManager->getRPCEndpointAddress().toCharArray());

		logger->info((std::string("RPC Server Address is: ") + ip).c_str(),true);

		rcfServer = new RCF::RcfProtoServer(RCF::TcpEndpoint("0.0.0.0",44471));

		/*if(endpointType == "tcp") {
			rcfServer = new RCF::RcfProtoServer(RCF::TcpEndpoint(ip, configManager->getRPCEndpointPort()));
		}
		else if(endpointType == "udp") {
			rcfServer = new RCF::RcfProtoServer(RCF::UdpEndpoint(ip, configManager->getRPCEndpointPort()));
		}
		else if(endpointType == "http") {
			rcfServer = new RCF::RcfProtoServer(RCF::HttpEndpoint(ip, configManager->getRPCEndpointPort()));
		}
		else if(endpointType == "https") {
			rcfServer = new RCF::RcfProtoServer(RCF::HttpsEndpoint(ip, configManager->getRPCEndpointPort()));
		}
		else {
			logger->error("No valid RPC server type in config");
			return;
		}*/

		logger->info("binding service",true);
		rcfServer->bindService(serviceImpl, std::string("SWGEmuAccountService"));
		rcfServer->bindService(detailsImpl, std::string("SWGEmuCharacterDetailsService"));
		rcfServer->bindService(structDetailsImpl, std::string("SWGEmuStructureItemDetailsService"));
		rcfServer->setThreadPool(RCF::ThreadPoolPtr(new RCF::ThreadPool(5)));

		rcfServer->start();
		logger->info("server started",true);

	}
	catch(const RCF::Exception & e) {
		logger->error((std::string("RCF Exception: ") + e.getErrorString()).c_str());
	}
	catch(std::exception & e) {
		logger->error((std::string("Exception: ") + std::string(e.what())).c_str());
	}

}

void RPCServerImpl::stop() {
	logger->info("stop",true);
	if(rcfServer != NULL) {
		rcfServer->stop();
		rcfServer = NULL;
	}

	//rcfServer.stop();
}
