/*
 * Copyright (c) 2017 syscl/lighting/Yating Zhou. All rights reserved.
 *
 * Courtesy to vit9696's Lilu => https://github.com/vit9696/Lilu/
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial
 * 4.0 Unported License => http://creativecommons.org/licenses/by-nc/4.0
 */

#ifndef __ENABLE_LIDWAKE_HPP__
#define __ENABLE_LIDWAKE_HPP__

#include <Headers/kern_patcher.hpp>

#include "syscl_lib.h"

#define kHSW   0
#define kSKL   1
#define kKBL   2


struct KextPatch {
    KernelPatcher::LookupPatch patch;
    uint32_t minKernel;
    uint32_t maxKernel;
};

class LidWake
{
public:
	bool init();
	void deinit();
	
private:
	/**
	 *  Patch kext if needed and prepare other patches
	 *
	 *  @param patcher KernelPatcher instance
	 *  @param index   kinfo handle
	 *  @param address kinfo load address
	 *  @param size    kinfo memory size
	 */
	void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size);
    
    /**
     *  Apply kext patches for loaded kext index
     *
     *  @param patcher    KernelPatcher instance
     *  @param index      kinfo index
     *  @param patches    patch list
     *  @param patchesNum patch number
     */
    void applyPatches(KernelPatcher &patcher, size_t index, const KextPatch *patches, size_t patchesNum);
	
	/**
	 *  Current progress mask
	 */
	struct ProcessingState {
		enum {
			NothingReady = 0,
			EverythingDone = 1,
		};
	};
    auto progressState {ProcessingState::NothingReady};
};

#endif
