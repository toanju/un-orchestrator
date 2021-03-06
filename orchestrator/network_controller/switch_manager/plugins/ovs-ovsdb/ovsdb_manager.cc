#include "ovsdb_manager.h"

int s = 0;

commands *c = NULL;

//Constructor
OVSDBManager::OVSDBManager()
{
	c = new commands();/*create a new object commands*/
}

//Destroyer
OVSDBManager::~OVSDBManager()
{
}

//implementation of createLsi
CreateLsiOut *OVSDBManager::createLsi(CreateLsiIn cli){
	return c->cmd_editconfig_lsi(cli, s);
}

//implementation of destroyLsi
void OVSDBManager::destroyLsi(uint64_t dpid){
	c->cmd_editconfig_lsi_delete(dpid, s);
}

//implementation of addNFPorts
AddNFportsOut *OVSDBManager::addNFPorts(AddNFportsIn anpi){
	return c->cmd_editconfig_NFPorts(anpi, s);
}

//implementation of addEndpoint
AddEndpointOut *OVSDBManager::addEndpoint(AddEndpointIn aepi){
	return c->cmd_editconfig_endpoint(aepi, s);
}

//implementation of destroyNFPorts
void OVSDBManager::destroyNFPorts(DestroyNFportsIn dnpi){
	c->cmd_editconfig_NFPorts_delete(dnpi, s);
}

//implementation of destroyEndpoint
void OVSDBManager::destroyEndpoint(DestroyEndpointIn depi){
	c->cmd_editconfig_endpoint_delete(depi, s);
}

//implementation of destroyVirtualLink
void OVSDBManager::destroyVirtualLink(DestroyVirtualLinkIn dvli){
	c->cmd_destroyVirtualLink(dvli, s);
}

//implementation of addVirtualLink
AddVirtualLinkOut *OVSDBManager::addVirtualLink(AddVirtualLinkIn avli){
	return c->cmd_addVirtualLink(avli, s);
}

//implementation of checkPhysicalInterfaces
void OVSDBManager::checkPhysicalInterfaces(set<CheckPhysicalPortsIn> cppi){
	/*TODO*/
}

