#pragma once
#include "UtilsGlobal.h"
#include <libloaderapi.h>

//template<typename AT>
//inline AT DynAddress(AT address)
//{
//	static_assert(sizeof(AT) == sizeof(uintptr_t), "AT must be pointer sized");
//#ifdef _WIN64
//	return (ptrdiff_t)GetModuleHandle(nullptr) - 0x140000000 + address;
//#else
//	return (ptrdiff_t)GetModuleHandle(nullptr) - 0x400000 + address;
//#endif
//}

template<typename AT>
__declspec(noinline) AT DynAddress(AT address)
{
    static_assert(sizeof(AT) == sizeof(uintptr_t), "AT must be pointer sized");
    static auto Handle = GetModuleHandle(nullptr);

    uintptr_t baseAddr = std::bit_cast<uintptr_t>(Handle);
    uintptr_t inputAddr = std::bit_cast<uintptr_t>(address);

#ifdef _WIN64
    uintptr_t result = baseAddr - 0x140000000ULL + inputAddr;
#else
    uintptr_t result = baseAddr - 0x400000UL + inputAddr;
#endif

    return std::bit_cast<AT>(result);
}
