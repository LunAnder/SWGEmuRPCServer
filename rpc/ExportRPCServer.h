/*
 * ExportRPCServer.h
 *
 *  Created on: Jan 10, 2014
 *      Author: swgemu
 */

#ifndef EXPORTRPCSERVER_H_
#define EXPORTRPCSERVER_H_

#if defined(__GNUC__) && __GNUC__ >= 4
    #ifdef SWGEMURPC_BUILD_DLL
        #define SWGEMURPCSERVER_EXPORT __attribute__((visibility("default")))
    #else
        #define SWGEMURPCSERVER_EXPORT __attribute__((visibility("default")))
    #endif
#elif defined(__GNUC__)
    #ifdef SWGEMURPC_BUILD_DLL
        #define SWGEMURPCSERVER_EXPORT
    #else
        #define SWGEMURPCSERVER_EXPORT
    #endif
#else
    #ifdef SWGEMURPC_BUILD_DLL
        #define SWGEMURPCSERVER_EXPORT __declspec(dllexport)
    #else
        #define SWGEMURPCSERVER_EXPORT
    #endif
#endif

#if defined(SWGEMURPC_BUILD_DLL) && defined(_MSC_VER) && !defined(_DLL)
#error "Error: DLL builds of RCF require dynamic runtime linking. Select one of the DLL options in Properties -> C/C++ -> Code Generation -> Runtime Library."
#endif

#endif /* EXPORTRPCSERVER_H_ */
