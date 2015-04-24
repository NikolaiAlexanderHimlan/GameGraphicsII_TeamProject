/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "d3dDevice.h"

std::vector<d3dDevice*> d3dDevice::s_d3dDeviceList;

#define ALL_DEVICE(deviceFunc) int deviceCount = s_d3dDeviceList.size();\
for (size_t i = 0; i < s_d3dDeviceList.size(); i++)\
{\
	d3dDevice* curDevice = dynamic_cast<d3dDevice*>(s_d3dDeviceList[i]);\
	if (NULL != curDevice)/*valid device, call function*/\
	{\
		s_d3dDeviceList[i]->deviceFunc;\
	}\
	else /*invalid device, remove from device list*/\
	{\
		s_d3dDeviceList.erase(s_d3dDeviceList.begin() + i);\
		i--;/*go back an index so the "next" device isn't skipped*/\
	}\
}\

void d3dDevice::allDeviceLost()
{
	ALL_DEVICE(onLostDevice())
}

void d3dDevice::allDeviceReset()
{
	ALL_DEVICE(onResetDevice())
}
