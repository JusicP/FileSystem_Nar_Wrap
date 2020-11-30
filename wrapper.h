/*
wrapper.cpp -- an ultimate VInterface wrapper for Source Tegra port
Copyright (C) 2017 a1batross
Licensed under WTFPL license.
Thanks to Valve for SDK, me for idea.
Please, don't punish, Mr. Newell. :)
*/

#pragma once

#include <stdlib.h>

#ifdef ANDROID
#include <dlfcn.h>
#include <android/log.h>
#include <stdio.h>
#define TAG "SourceSDK2013"
#define PRIO ANDROID_LOG_DEBUG
#define LogPrintf(...) do { __android_log_print(PRIO, TAG, __VA_ARGS__); printf( __VA_ARGS__); } while( 0 );
#else
#include <stdio.h>
#define LogPrintf(...) printf(__VA_ARGS__)
#endif

// don't link tier1
#include "Interface/interface.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#undef DLLEXPORT
#define DLLEXPORT extern "C" __attribute__((visibility("default")))

class Module
{
public:
	Module() : m_szName(NULL), m_pLibrary(NULL), CreateInterface(NULL) {}
	~Module() { Unload(); }

	bool Load(const char* name, bool isModule = true)
	{
		m_szName = name;
		m_pLibrary = Sys_LoadModule(name);
		if (!m_pLibrary)
		{
#ifdef POSIX
			LogPrintf("Module::Load: Failed to load %s: %s\n", name, dlerror());
#else
			LogPrintf("Module::Load: Failed to load %s: %d\n", name, GetLastError());
#endif
			return false;
		}


		if (isModule)
		{
			CreateInterface = (void* (*)(const char*, int*))Resolve("CreateInterface");
			if (!CreateInterface)
			{
				return false;
			}
		}

		return true;
	}

	void Unload()
	{
		if (m_pLibrary)
		{
			Sys_FreeModule(m_pLibrary);
		}

		m_pLibrary = NULL;
		CreateInterface = NULL;
		m_szName = NULL;
	}

	IBaseInterface* GetInterface(const char* pName, int* pReturnCode) const
	{
		if (CreateInterface)
			return (IBaseInterface*)CreateInterface(pName, pReturnCode);

		return NULL;
	}

	void* Resolve(const char* name) const
	{
#ifdef POSIX
		void* ret = dlsym(m_pLibrary, name);
#else
		void* ret = GetProcAddress((HMODULE)m_pLibrary, name);
#endif
		if (!ret)
		{
#ifdef POSIX
			LogPrintf("Module::Resolve: Failed to resolve %s from %s: %s\n", name, m_szName, dlerror());
#else
			LogPrintf("Module::Resolve: Failed to resolve %s from %s: %d\n", name, m_szName, GetLastError());
#endif
		}
		return ret;
	}

	const char* Name(void) const
	{
		return m_szName;
	}

	const void* GetHandle(void) const
	{
		return m_pLibrary;
	}

private:
	const char* m_szName;
	HINTERFACEMODULE m_pLibrary;
	void* (*CreateInterface)(const char* pName, int* pReturnCode);
};

struct Loader
{
	Loader(void);
	~Loader(void);

	void LoadAllLibraries(void);

	struct LoaderPrivate* p;
};
extern struct Loader g_Loader;

typedef void (*WrapInitFn)(Module* module);

// Used to wrap classes.
struct WrapInterfaceReg
{
	WrapInterfaceReg(const char* pModuleName, const char* pName, IBaseInterface** iface, WrapInitFn fn = NULL, WrapInitFn fnDestruct = NULL);
	WrapInterfaceReg(const char* pModuleName, bool isModule = true, WrapInitFn fn = NULL, WrapInitFn fnDestruct = NULL);
	~WrapInterfaceReg();

	IBaseInterface** m_pIface;
	const char* m_szModuleName;
	const char* m_szName;
	bool					m_bIsModule;
	WrapInitFn				m_pfn;
	WrapInitFn				m_pfnDestruct;

	WrapInterfaceReg* m_pNext; // For the global list.
	static WrapInterfaceReg* s_pInterfaceRegs;
};

#define VA_ARGS(...) , ##__VA_ARGS__

#define GET_INTERFACE_PTR(szReadableName, pModule, pName, iface, ...) \
	static WrapInterfaceReg __g_Wrap##szReadableName##_reg((pModule), (pName), (IBaseInterface**)(iface) VA_ARGS(__VA_ARGS__) )
#define WRAP_LIBRARY( szReadableName, pModule, ... )	static WrapInterfaceReg __g_Wrap##szReadableName##_reg(pModule, false VA_ARGS(__VA_ARGS__) )
#define WRAP_MODULE( szReadableName, pModule, ... )	static WrapInterfaceReg __g_Wrap##szReadableName##_reg(pModule, true VA_ARGS(__VA_ARGS__) )