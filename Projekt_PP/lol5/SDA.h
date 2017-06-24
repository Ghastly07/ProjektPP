
#pragma once
#include<iostream>
#include<math.h>
#include <iomanip>
#include<Windows.h>
#using <mscorlib.dll>
using namespace System::Threading;
using namespace System;
using namespace System::IO;

//[ComVisibleAttribute(true)]
//[HostProtectionAttribute(SecurityAction::LinkDemand, Synchronization = true,
//	ExternalThreading = true)]

class SDA {
private:

public:
	SDA() {};
	static array< double, 2 >^SDA_disc(array< double, 2 >^%mac, int sx, int sy, double r, int mode, int min_roznica);
	static array< double, 2 >^SDA_cross(array< double, 2 >^%mac, int sx, int sy, double r, int mode, int min_roznica);
	static void ThreadProcMode0(Object^ stateInfo);
	static void ThreadProcMode1(Object^ stateInfo);
	static void ThreadProcCrossMod0(Object^ stateInfo);
	static void ThreadProcCrossMod1(Object^ stateInfo);
	static int MaxCPU;
	static int Mac2MacMargUshort(array< double, 2 >^%macin, int sx, int sy, int Marg, array< double, 2 >^%macout);
	static int remaining;


};