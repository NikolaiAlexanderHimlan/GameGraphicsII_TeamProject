/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include <vector>
//Contains the functions needed to handle directX window interactions
class d3dDevice
{
public:
	static std::vector<d3dDevice*> s_d3dDeviceList;

	static void allDeviceLost();
	static void allDeviceReset();

	//virtual bool checkDeviceCaps() = 0;
	virtual void onLostDevice() = 0;
	virtual void onResetDevice() = 0;
};

