all: libSWGEmuRPCServer.a

AccountRequest.pb.cc:
	protoc ../rpc/proto/AccountRequest.proto --proto_path=../rpc/proto --cpp_out=../rpc/generatedpb

CharacterDetails.pb.cc:
	protoc ../rpc/proto/CharacterDetails.proto --proto_path=../rpc/proto --cpp_out=../rpc/generatedpb

StructureDetails.pb.cc:
	protoc ../rpc/proto/StructureDetails.proto --proto_path=../rpc/proto --cpp_out=../rpc/generatedpb

InventoryItem.pb.cc:
	protoc ../rpc/proto/InventoryItem.proto --proto_path=../rpc/proto --cpp_out=../rpc/generatedpb
	
RCF.o: 
	g++ -fPIC -c -ggdb ../rcf/RCF/src/RCF/RCF.cpp -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I/usr/local/include -I/home/swgemu/boost_1_55_0 -I../rcf -I../rcf/RCF/include -g

RCFProto.o: 
	g++ -fPIC -c -ggdb ../rcf/RCFProto.cpp -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I/usr/local/include -I/home/swgemu/boost_1_55_0 -I../rcf -I../rcf/RCF/include -g

AccountRequest.o: AccountRequest.pb.cc
	g++ -fPIC -c -ggdb ../rpc/generatedpb/AccountRequest.pb.cc -I/usr/local/include -I../rpc/generatedpb

InventoryItem.o: InventoryItem.pb.cc
	g++ -fPIC -c -ggdb ../rpc/generatedpb/InventoryItem.pb.cc -I/usr/local/include -I../rpc/generatedpb

CharacterDetails.o: CharacterDetails.pb.cc
	g++ -fPIC -c -ggdb ../rpc/generatedpb/CharacterDetails.pb.cc -I/usr/local/include -I../rpc/generatedpb

StructureDetails.o: StructureDetails.pb.cc
	g++ -fPIC -c -ggdb ../rpc/generatedpb/StructureDetails.pb.cc -I/usr/local/include -I../rpc/generatedpb
	
ItemMessageHelper.o: CharacterDetails.o InventoryItem.o
	g++ -fPIC -c -ggdb ../rpc/util/ItemMessageHelper.cpp -DRCF_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar
	
StructureMessageHelper.o: CharacterDetails.o InventoryItem.o
	g++ -fPIC -c -ggdb ../rpc/util/StructureMessageHelper.cpp -DRCF_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar
	
SWGEmuAccountServiceImpl.o: AccountRequest.o
	g++ -fPIC -c -ggdb ../rpc/implementation/SWGEmuAccountServiceImpl.cpp -DRCF_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar

SWGEmuCharacterDetailsServiceImpl.o: StructureDetails.o ItemMessageHelper.o
	g++ -fPIC -c -ggdb ../rpc/implementation/SWGEmuCharacterDetailsServiceImpl.cpp -DRCF_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar

SWGEmuStructureItemDetailsServiceImpl.o: StructureDetails.o
	g++ -fPIC -c -ggdb ../rpc/implementation/SWGEmuStructureItemDetailsServiceImpl.cpp -DRCF_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar

RPCServerImpl.o: SWGEmuAccountServiceImpl.o SWGEmuCharacterDetailsServiceImpl.o SWGEmuStructureItemDetailsServiceImpl.o
	g++ -fPIC -c -ggdb ../rpc/RPCServerImpl.cpp -DRCF_BUILD_DLL -DSWGEMURPC_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar

RPCServer.o: RPCServerImpl.o
	g++ -fPIC -c -ggdb ../rpc/RPCServer.cpp -DRCF_BUILD_DLL -DSWGEMURPC_BUILD_DLL -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -I../../MMOCoreORB/src -I../../MMOCoreORB/src/autogen -I../../MMOCoreORB/utils/gmock-1.6.0/include -I../../MMOCoreORB/utils/gtest-1.6.0/include -I../../MMOEngine/include -I/usr/include/lua5.1 -I/usr/include/mysql -I/usr/local/BerkeleyDB.5.0/include -I/usr/include/db5.0 -Wno-multichar

RCFProto_NET_impl.o:
	g++ -fPIC -c ../rcf/swig/RCFProto_NET_impl.cpp ../rcf/RCFProto_NET_impl.rc -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I/home/swgemu/boost_1_55_0 -I../../src -I../../src/RCF/include -I../rcf/swig -I../rcf/RCF/include

test : RCF.o RCFProto.o AccountRequest.o CharacterDetails.o StructureDetails.o InventoryItem.o
	g++ -oTestRPCClient ../testRPCClient.cpp RCFProto.o RCF.o AccountRequest.pb.o InventoryItem.pb.o CharacterDetails.pb.o StructureDetails.pb.o -I/usr/local/include -I.. -I../rcf -I../rcf/RCF/include -Wno-multichar -lpthread -lprotobuf -ldl

libSWGEmuRPCServer.so:  RCF.o RCFProto.o AccountRequest.o InventoryItem.o SWGEmuAccountServiceImpl.o CharacterDetails.o SWGEmuCharacterDetailsServiceImpl.o StructureMessageHelper.o RPCServerImpl.o RPCServer.o
	g++ -shared -ggdb -o libSWGEmuRPCServer.so RCFProto.o RCF.o AccountRequest.pb.o InventoryItem.pb.o CharacterDetails.pb.o SWGEmuAccountServiceImpl.o ItemMessageHelper.o StructureMessageHelper.o SWGEmuCharacterDetailsServiceImpl.o StructureDetails.pb.o SWGEmuStructureItemDetailsServiceImpl.o RPCServerImpl.o RPCServer.o -lpthread -lprotobuf -ldl

libRCFProto_NET_impl.so: RCFProto.o RCF.o RCFProto_NET_impl.o
	g++ -shared -o libRCFProto_NET_impl.so RCFProto.o RCF.o RCFProto_NET_impl.o -lpthread -lprotobuf -ldl

libSWGEmuRPCServer.a: RCF.o RCFProto.o AccountRequest.o InventoryItem.o SWGEmuAccountServiceImpl.o CharacterDetails.o SWGEmuCharacterDetailsServiceImpl.o StructureMessageHelper.o RPCServerImpl.o RPCServer.o
	ar rcs libSWGEmuRPCServer.a RCFProto.o RCF.o AccountRequest.pb.o InventoryItem.pb.o CharacterDetails.pb.o SWGEmuAccountServiceImpl.o ItemMessageHelper.o StructureMessageHelper.o SWGEmuCharacterDetailsServiceImpl.o StructureDetails.pb.o SWGEmuStructureItemDetailsServiceImpl.o RPCServerImpl.o RPCServer.o
