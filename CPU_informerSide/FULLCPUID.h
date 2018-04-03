/********************************************************
*
* CPU INFORMER is GPLv3 licenced source code.
*
* (C) Vertver, 2018
*
* CPU INFORMER Source Code is free software:
* You can redistribute it and/or modify it.
*
* FULLCPUID.h - CPUID with all CPU instructions.
* search the instructions via scanning ECX and
* 
*********************************************************/
#pragma once
#include "stdafx.h"

class CPUID
{
	// forward declarations  
	class CPUID_Internal;

public:
	// vendor and brand of CPU
	static std::string Vendor	(void) { return CPU_Rep.vendor_; }
	static std::string ModelCPU	(void) { return CPU_Rep.brand_; }

	// MMX Instuctions
	static bool MMX				(void) { return CPU_Rep.f_1_EDX_[23]; }
	static bool MMXEXT			(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }

	// 3DNow! Instructions
	static bool _3DNOWEXT		(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
	static bool _3DNOW			(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

	// SSE instructions
	static bool SSE				(void) { return CPU_Rep.f_1_EDX_[25]; }
	static bool SSE2			(void) { return CPU_Rep.f_1_EDX_[26]; }
	static bool SSE3			(void) { return CPU_Rep.f_1_ECX_[0]; }
	static bool SSSE3			(void) { return CPU_Rep.f_1_ECX_[9]; }
	static bool SSE41			(void) { return CPU_Rep.f_1_ECX_[19]; }
	static bool SSE42			(void) { return CPU_Rep.f_1_ECX_[20]; }
	static bool SSE4a			(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }

	// Thermal monitors
	static bool MONITOR			(void) { return CPU_Rep.f_1_ECX_[3]; }
	static bool TM2				(void) { return CPU_Rep.f_1_ECX_[8]; }

	// FMA3 Instructions
	static bool FMA				(void) { return CPU_Rep.f_1_ECX_[12]; }

	// AES Instructions
	static bool AES				(void) { return CPU_Rep.f_1_ECX_[25]; }

	// AVX Instructions
	static bool AVX				(void) { return CPU_Rep.f_1_ECX_[28]; }
	static bool AVX2			(void) { return CPU_Rep.f_7_EBX_[5]; }
	static bool AVX512F			(void) { return CPU_Rep.f_7_EBX_[16]; }
	static bool AVX512PF		(void) { return CPU_Rep.f_7_EBX_[26]; }
	static bool AVX512ER		(void) { return CPU_Rep.f_7_EBX_[27]; }
	static bool AVX512CD		(void) { return CPU_Rep.f_7_EBX_[28]; }

	// RTM Instructions
	static bool RTM				(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }

	// SHA! TAA! Instructions
	static bool SHA				(void) { return CPU_Rep.f_7_EBX_[29]; }

	// System instructions
	static bool HT				(void) { return CPU_Rep.f_81_ECX_[28];}
	static bool AMD				(void) { return CPU_Rep.isAMD_; }
	static bool SYSCALL			(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
	static bool RDTSCP			(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
	static int  CORES			(void) {}


private:
	static const CPUID_Internal CPU_Rep;

	class CPUID_Internal
	{
	public:
		CPUID_Internal()
			: nIds_		{ 0 },
			nExIds_		{ 0 },
			isIntel_	{ false },
			isAMD_		{ false },
			f_1_ECX_	{ 0 },
			f_1_EDX_	{ 0 },
			f_7_EBX_	{ 0 },
			f_7_ECX_	{ 0 },
			f_81_ECX_	{ 0 },
			f_81_EDX_	{ 0 },
			data_		{},
			extdata_	{}
		{
			std::array<int, 4> cpui;

			// Calling __cpuid with 0x0 as the function_id argument  
			__cpuid(cpui.data(), 0);
			nIds_ = cpui[0];

			for (int i = 0; i <= nIds_; ++i)
			{
				__cpuidex(cpui.data(), i, 0);
				data_.push_back(cpui);
			}

			// Capture vendor string  
			char vendor[0x20];
			memset(vendor, 0, sizeof	(vendor));
			*reinterpret_cast<int*>		(vendor)		= data_[0][1];
			*reinterpret_cast<int*>		(vendor + 4)	= data_[0][3];
			*reinterpret_cast<int*>		(vendor + 8)	= data_[0][2];
										 vendor_		= vendor;

			if (vendor_ == "AuthenticAMD")
			{
				isAMD_ = true;
			}
			else
			{
				isIntel_ = true;
			}

			// We're loading bitset with flags...
			if (nIds_ >= 1)					
			{								// 0x00000001  
				f_1_ECX_ = data_[1][2];
				f_1_EDX_ = data_[1][3];
			}
			if (nIds_ >= 7)					
			{								// 0x00000007
				f_7_EBX_ = data_[7][1];
				f_7_ECX_ = data_[7][2];
			}

			// Calling __cpuid with 0x80000000 as the function_id argument  
			__cpuid(cpui.data(), 0x80000000);
			nExIds_ = cpui[0];
			char modelCPU[0x40];
			memset(modelCPU, 0, sizeof(modelCPU));


			for (int i = 0x80000000; i <= nExIds_; ++i)
			{
				__cpuidex(cpui.data(), i, 0);
				extdata_.push_back(cpui);
			}
			if (nExIds_ >= 0x80000001)		
			{								// 0x80000001  
				f_81_ECX_ = extdata_[1][2];
				f_81_EDX_ = extdata_[1][3];
			}

			// Print the string of CPU
			if (nExIds_ >= 0x80000004)
			{
				memcpy(modelCPU,	  extdata_[2].data(), sizeof(cpui));
				memcpy(modelCPU + 16, extdata_[3].data(), sizeof(cpui));
				memcpy(modelCPU + 32, extdata_[4].data(), sizeof(cpui));
				brand_ = modelCPU;
			}
			unsigned long long pa_mask_save, sa_mask_stub = 0;
			GetProcessAffinityMask(GetCurrentProcess(), &pa_mask_save, &sa_mask_stub);
			SYSTEM_INFO sysInfo;
			GetSystemInfo(&sysInfo);
			auto n_threads = sysInfo.dwNumberOfProcessors;
			auto affinity_mask = unsigned(pa_mask_save);
			auto n_cores = (CPUID::HT) ? (n_threads / 2) : (n_threads);

		};

		int nIds_;
		int nExIds_;
		bool isIntel_;
		bool isAMD_;
		std::string vendor_;
		std::string brand_;
		std::bitset<32> f_1_ECX_;
		std::bitset<32> f_1_EDX_;
		std::bitset<32> f_7_EBX_;
		std::bitset<32> f_7_ECX_;
		std::bitset<32> f_81_ECX_;
		std::bitset<32> f_81_EDX_;
		std::vector<std::array<int, 4>> data_;
		std::vector<std::array<int, 4>> extdata_;
};
};