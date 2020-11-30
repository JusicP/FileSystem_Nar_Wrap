/*
wrapper.cpp -- an ultimate VInterface wrapper for Source Tegra port
Copyright (C) 2017 a1batross
Licensed under WTFPL license.
Thanks to Valve for SDK, me for idea.
Please, don't punish, Mr. Newell. :)
*/

#include "wrapper.h"

struct Loader  g_Loader;
InterfaceReg* InterfaceReg::s_pInterfaceRegs = NULL;
WrapInterfaceReg* WrapInterfaceReg::s_pInterfaceRegs = NULL;

InterfaceReg::InterfaceReg(InstantiateInterfaceFn fn, const char* pName) :
	m_pName(pName)
{
	m_CreateFn = fn;
	m_pNext = s_pInterfaceRegs;
	s_pInterfaceRegs = this;
}

WrapInterfaceReg::WrapInterfaceReg(const char* pModuleName, const char* pName, IBaseInterface** iface, WrapInitFn callback, WrapInitFn fnDestruct) :
	m_szModuleName(pModuleName), m_szName(pName), m_pIface(iface), m_bIsModule(true), m_pfn(callback), m_pfnDestruct(fnDestruct)
{
	m_pNext = s_pInterfaceRegs;
	s_pInterfaceRegs = this;
}

WrapInterfaceReg::WrapInterfaceReg(const char* pModuleName, bool bIsModule, WrapInitFn callback, WrapInitFn fnDestruct) :
	m_szModuleName(pModuleName), m_szName(NULL), m_pIface(NULL), m_bIsModule(bIsModule), m_pfn(callback), m_pfnDestruct(fnDestruct)
{
	m_pNext = s_pInterfaceRegs;
	s_pInterfaceRegs = this;
}

WrapInterfaceReg::~WrapInterfaceReg()
{
	if (m_pfnDestruct)
	{
		m_pfnDestruct(NULL);
	}
}

/*void (*realSDL_AddEventWatch)(void *filter, void *userdata);
void (*realSDL_DelEventWatch)(void *filter, void *userdata);
int Wrapper_EventFilter( void *userdata, void *event )
{
	LogPrintf( "Got event\n" );

	return 0;
}*/

struct LoaderPrivate
{
	LoaderPrivate() { memset(modules, 0, sizeof(modules)); modulesNum = 0; }
	Module* modules[32];
	int modulesNum;
};

Loader::Loader(void)
{
	/*if( !SDL2.Load("libSDL2.so", false) )
		abort();

	realSDL_AddEventWatch = (void(*)(void*, void*))SDL2.Resolve("SDL_AddEventWatch");
	realSDL_DelEventWatch = (void(*)(void*, void*))SDL2.Resolve("SDL_DelEventWatch");

	realSDL_AddEventWatch( (void*)Wrapper_EventFilter, NULL );*/

	p = new LoaderPrivate;
}

void Loader::LoadAllLibraries(void)
{
	static bool initialized = false;

	if (initialized)
		return;

	for (WrapInterfaceReg* pCur = WrapInterfaceReg::s_pInterfaceRegs; pCur; pCur = pCur->m_pNext)
	{
		Module* module;

		// check for twice added modules
		int i = 0;
		for (; i < p->modulesNum; i++)
			if (!strcmp(p->modules[i]->Name(), pCur->m_szModuleName))
				break;

		if (i == p->modulesNum || p->modulesNum == 0)
		{
			module = new Module();
			module->Load(pCur->m_szModuleName, pCur->m_bIsModule);
			if (pCur->m_pfn)
				pCur->m_pfn(module);
			p->modules[p->modulesNum++] = module;
		}
		else
		{
			module = g_Loader.p->modules[i];
		}

		if (pCur->m_pIface && pCur->m_szName)
		{
			if ((*(pCur->m_pIface) = module->GetInterface(pCur->m_szName, NULL)))
			{
				LogPrintf("Got interface pointer to %s from %s\n", pCur->m_szName, module->Name());
			}
		}
		else LogPrintf("Loaded non-module library %s\n", pCur->m_szModuleName);
	}

	initialized = true;
}

Loader::~Loader(void)
{
	// realSDL_DelEventWatch( (void*)Wrapper_EventFilter, NULL );
	for (int i = 0; i < g_Loader.p->modulesNum; i++)
		delete g_Loader.p->modules[i];
	delete p;
}

extern "C" EXPORT_FUNCTION IBaseInterface* CreateInterface(const char* pName, int* pReturnCode)
{
	void* ret;
	LogPrintf("Requested Interface: %s\n", pName);

	// Load all wrappers at first CreateInterface. After all static objects are initialized
	g_Loader.LoadAllLibraries();

	for (InterfaceReg* pCur = InterfaceReg::s_pInterfaceRegs; pCur; pCur = pCur->m_pNext)
	{
		if (!strcmp(pCur->m_pName, pName))
		{
			LogPrintf("Overriden.\n");
			if (pReturnCode) *pReturnCode = IFACE_OK;
			return pCur->m_CreateFn();
		}
	}

	for (int i = 0; i < g_Loader.p->modulesNum; i++)
	{
		ret = g_Loader.p->modules[i]->GetInterface(pName, pReturnCode);
		if (ret)
		{
			LogPrintf("Found in %s\n", g_Loader.p->modules[i]->Name());
			return (IBaseInterface*)ret;
		}
	}

	LogPrintf("Interface %s not found\n", pName);
	if (pReturnCode) *pReturnCode = IFACE_FAILED;

	return NULL;
}

#ifdef _WIN32
HINTERFACEMODULE Sys_LoadModule(const char* pModuleName)
{
	return (HINTERFACEMODULE)LoadLibrary(pModuleName);
}

#else  // LINUX
HINTERFACEMODULE Sys_LoadModule(const char* pModuleName)
{
	// Linux dlopen() doesn't look in the current directory for libraries.
	// We tell it to, so people don't have to 'install' libraries as root.

	char szCwd[1024];
	char szAbsoluteLibFilename[1024];

	getcwd(szCwd, sizeof(szCwd));
	if (szCwd[strlen(szCwd) - 1] == '/')
		szCwd[strlen(szCwd) - 1] = 0;

	sprintf(szAbsoluteLibFilename, "%s/%s", szCwd, pModuleName);

	return (HINTERFACEMODULE)dlopen(szAbsoluteLibFilename, RTLD_NOW);
}

#endif


#ifdef _WIN32
void Sys_FreeModule(HINTERFACEMODULE hModule)
{
	if (!hModule)
		return;

	FreeLibrary((HMODULE)hModule);
}

#else  // LINUX
void Sys_FreeModule(HINTERFACEMODULE hModule)
{
	if (!hModule)
		return;

	dlclose((void*)hModule);
}

#endif