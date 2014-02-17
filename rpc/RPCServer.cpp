/*
 * RPCServer.cpp
 *
 *  Created on: Jan 5, 2014
 *      Author: swgemu
 */


#include "RPCServerImpl.h"
#include "RPCServer.h"

RPCServer::RPCServer() {
	rpcServerImpl = new RPCServerImpl();
}

RPCServer::~RPCServer() {
	rpcServerImpl = NULL;
}

void RPCServer::start(server::conf::ConfigManager* config, server::zone::ZoneServer* zone) {
	rpcServerImpl->start(config, zone);
}

void RPCServer::stop() {
	rpcServerImpl->stop();
}
