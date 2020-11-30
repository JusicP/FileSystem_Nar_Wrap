#include <windows.h>
#include <stdio.h>

#include "Wrapper.h"
#include "Interface/IFileSystem.h"

IFileSystemNar_OLD* realFileSystemNar;

GET_INTERFACE_PTR(FileSystem, "FileSystem_Nar_Orig.dll", FILESYSTEM_INTERFACE_VERSION, &realFileSystemNar);

class CFileSystemNar : public IFileSystem
{
	virtual void Mount(void)
	{
		printf("Mount\n");
		realFileSystemNar->Mount();
	}
	virtual void Unmount(void)
	{
		printf("Unmount\n");
		realFileSystemNar->Unmount();
	}
	virtual void RemoveAllSearchPaths(void)
	{
		realFileSystemNar->RemoveAllSearchPaths();
	}
	virtual void AddSearchPath(const char* pPath, const char* pathID = 0)
	{
		realFileSystemNar->AddSearchPath(pPath, pathID);
	}
	virtual bool RemoveSearchPath(const char* pPath)
	{
		return realFileSystemNar->RemoveSearchPath(pPath);
	}
	virtual void RemoveFile(const char* pRelativePath, const char* pathID = 0)
	{
		realFileSystemNar->RemoveFile(pRelativePath, pathID);
	}
	virtual void CreateDirHierarchy(const char* path, const char* pathID = 0)
	{
		realFileSystemNar->CreateDirHierarchy(path, pathID);
	}
	virtual bool FileExists(const char* pFileName)
	{
		return realFileSystemNar->FileExists(pFileName);
	}
	virtual bool IsDirectory(const char* pFileName)
	{
		return realFileSystemNar->IsDirectory(pFileName);
	}
	virtual FileHandle_t Open(const char* pFileName, const char* pOptions, const char* pathID = 0)
	{
		return realFileSystemNar->Open(pFileName, pOptions, pathID);
	}
	virtual void Close(FileHandle_t file)
	{
		realFileSystemNar->Close(file);
	}
	virtual void Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType)
	{
		realFileSystemNar->Seek(file, pos, seekType);
	}
	virtual unsigned Tell(FileHandle_t file)
	{
		return realFileSystemNar->Tell(file);
	}
	virtual unsigned Size(FileHandle_t file)
	{
		return realFileSystemNar->Size(file);
	}
	virtual unsigned Size(const char* pFileName)
	{
		return realFileSystemNar->Size(pFileName);
	}
	virtual long GetFileTime(const char* pFileName)
	{
		return realFileSystemNar->GetFileTime(pFileName);
	}
	virtual void FileTimeToString(char* pStrip, int maxCharsIncludingTerminator, long fileTime)
	{
		realFileSystemNar->FileTimeToString(pStrip, maxCharsIncludingTerminator, fileTime);
	}
	virtual bool IsOk(FileHandle_t file)
	{
		return realFileSystemNar->IsOk(file);
	}
	virtual void Flush(FileHandle_t file)
	{
		realFileSystemNar->Flush(file);
	}
	virtual bool EndOfFile(FileHandle_t file)
	{
		return realFileSystemNar->EndOfFile(file);
	}
	virtual int Read(void* pOutput, int size, FileHandle_t file)
	{
		return realFileSystemNar->Read(pOutput, size, file);
	}
	virtual int Write(void const* pInput, int size, FileHandle_t file)
	{
		return realFileSystemNar->Write(pInput, size, file);
	}
	virtual char* ReadLine(char* pOutput, int maxChars, FileHandle_t file)
	{
		return realFileSystemNar->ReadLine(pOutput, maxChars, file);
	}
	virtual int FPrintf(FileHandle_t file, char* pFormat, ...)
	{
		va_list args;
		va_start(args, pFormat);

		int retVal = realFileSystemNar->FPrintf(file, pFormat, args);

		va_end(args);
		
		return retVal;
	}
	virtual char* GetReadBuffer(FileHandle_t file, char* pBuffer)
	{
		return realFileSystemNar->GetReadBuffer(file, pBuffer);
	}
	virtual void ReleaseReadBuffer(FileHandle_t file, char* pBuffer)
	{
		realFileSystemNar->ReleaseReadBuffer(file, pBuffer);
	}
	virtual const char* FindFirst(const char* pWildCard, FileFindHandle_t* pHandle, const char* pathID = 0)
	{
		return realFileSystemNar->FindFirst(pWildCard, pHandle, pathID);
	}
	virtual const char* FindNext(FileFindHandle_t handle)
	{
		return realFileSystemNar->FindNext(handle);
	}
	virtual bool FindIsDirectory(FileFindHandle_t handle)
	{
		return realFileSystemNar->FindIsDirectory(handle);
	}
	virtual void FindClose(FileFindHandle_t handle)
	{
		realFileSystemNar->FindClose(handle);
	}
	virtual void GetLocalCopy(const char* pFileName)
	{
		realFileSystemNar->GetLocalCopy(pFileName);
	}
	virtual const char* GetLocalPath(const char* pFileName, char* pLocalPath, int maxlen)
	{
		return realFileSystemNar->GetLocalPath(pFileName, pLocalPath, maxlen);
	}
	virtual char* ParseFile(char* data, char* token, bool* wasquoted)
	{
		return realFileSystemNar->ParseFile(data, token, wasquoted);
	}
	virtual bool FullPathToRelativePath(const char* pFullpath, char* pRelative)
	{
		return realFileSystemNar->FullPathToRelativePath(pFullpath, pRelative);
	}
	virtual bool GetCurrentDirectory(char* pDirectory, int maxlen)
	{
		return realFileSystemNar->GetCurrentDirectory(pDirectory, maxlen);
	}
	virtual bool GetCurrentDirectory2(char* pDirectory, int maxlen)
	{
		return realFileSystemNar->GetCurrentDirectory(pDirectory, maxlen);
	}
	virtual void PrintOpenedFiles(void)
	{
		realFileSystemNar->PrintOpenedFiles();
	}
	virtual void SetWarningFunc(void (*pfnWarning)(const char* fmt, ...))
	{

	}
	virtual void SetWarningLevel(FileWarningLevel_t level)
	{
	
	}
	virtual void LogLevelLoadStarted(const char* name)
	{
	
	}
	virtual void LogLevelLoadFinished(const char* name)
	{
	
	}
	virtual int HintResourceNeed(const char* hintlist, int forgetEverything)
	{
		return 0;
	}
	virtual int PauseResourcePreloading(void)
	{
		return 0;
	}
	virtual int ResumeResourcePreloading(void)
	{
		return 0;
	}
	virtual int SetVBuf(FileHandle_t stream, char* buffer, int mode, long size)
	{
		return 0;
	}
	virtual void GetInterfaceVersion(char* p, int maxlen)
	{
		return realFileSystemNar->GetInterfaceVersion(p, maxlen);
	}
	virtual bool IsFileImmediatelyAvailable(const char* path)
	{
		return false;
	}
	virtual void* WaitForResources(const char* pFileName)
	{
		return NULL;
	}
	virtual bool GetWaitForResourcesProgress(WaitForResourcesHandle_t handle, float* progress, bool* complete)
	{
		return false;
	}
	virtual void CancelWaitForResources(WaitForResourcesHandle_t handle)
	{

	}
	virtual bool IsAppReadyForOfflinePlay(void)
	{
		return true;
	}
	virtual void AddPackFile(const char* pPath, const char* pathID = 0)
	{
	
	}
	virtual void* OpenFromCacheForRead(const char* pFileName, const char* pOptions, const char* pathID = 0)
	{
		return NULL;
	}
	virtual bool Unknown1(const char* pFileName, const char* pathID)
	{
		LogDebug("Unknown1\n");
		return realFileSystemNar->Unknown1(pFileName, pathID);
	}
	virtual void *Unknown2(const char* pFileName)
	{
		LogDebug("Unknown2\n");
		return realFileSystemNar->Unknown2(pFileName);
	}
	virtual void Unknown3(const char* pFileName, char* a1)
	{
		LogDebug("Unknown3\n");
		realFileSystemNar->Unknown3(pFileName, a1);
	}
	virtual void Unknown4()
	{
		LogDebug("Unknown4\n");
	}
	virtual void Unknown5()
	{
		LogDebug("Unknown5\n");
	}
	virtual void Unknown6()
	{
		LogDebug("Unknown6\n");
	}
	virtual void Unknown7()
	{
		LogDebug("Unknown7\n");
	}
	virtual void Unknown8()
	{
		LogDebug("Unknown8\n");
	}
	virtual void Unknown9(void* Src, int a1)
	{
		//realFileSystemNar->Unknown9(Src, a1);
		LogDebug("Unknown9\n");
	}
	virtual void Unknown10()
	{
		LogDebug("Unknown10\n");
	}
	virtual void Unknown11()
	{
		LogDebug("Unknown11\n");
	}
	virtual void Unknown12()
	{
		LogDebug("Unknown12\n");
	}
	virtual void Unknown13()
	{
		LogDebug("Unknown13\n");
	}
	virtual void Unknown14()
	{
		LogDebug("Unknown14\n");
	}
	virtual void Unknown15()
	{
		LogDebug("Unknown15\n");
	}
	virtual void Unknown16()
	{
		LogDebug("Unknown16\n");
	}
	virtual void Unknown17()
	{
		LogDebug("Unknown17\n");
	}
	virtual void Unknown18()
	{
		LogDebug("Unknown18\n");
	}
	virtual void Unknown19()
	{
		LogDebug("Unknown19\n");
	}
};

//EXPOSE_INTERFACE(CFileSystemNar, IFileSystem, FILESYSTEM_INTERFACE_VERSION)

CFileSystemNar gWrapFileSystemNar;
IFileSystem* filesystem = &gWrapFileSystemNar;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CFileSystemNar, IFileSystem, FILESYSTEM_INTERFACE_VERSION, gWrapFileSystemNar);
