#include <windows.h>
#include <stdio.h>

#include "Interface/Interface.h"
#include "Interface/IFileSystem.h"

class CFileSystemNar : public IFileSystem
{
	virtual void Mount(void)
	{
		printf("Mount\n");
	}
	virtual void Unmount(void)
	{
		printf("Unmount\n");
	}
	virtual void RemoveAllSearchPaths(void)
	{

	}
	virtual void AddSearchPath(const char* pPath, const char* pathID = 0)
	{

	}
	virtual bool RemoveSearchPath(const char* pPath)
	{
		return false;
	}
	virtual void RemoveFile(const char* pRelativePath, const char* pathID = 0)
	{

	}
	virtual void CreateDirHierarchy(const char* path, const char* pathID = 0)
	{

	}
	virtual bool FileExists(const char* pFileName)
	{
		return false;
	}
	virtual bool IsDirectory(const char* pFileName)
	{
		return false;
	}
	virtual FileHandle_t Open(const char* pFileName, const char* pOptions, const char* pathID = 0)
	{
		return NULL;
	}
	virtual void Close(FileHandle_t file)
	{

	}
	virtual void Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType)
	{

	}
	virtual unsigned Tell(FileHandle_t file)
	{
		return 0;
	}
	virtual unsigned Size(FileHandle_t file)
	{
		return 0;
	}
	virtual unsigned Size(const char* pFileName)
	{
		return 0;
	}
	virtual long GetFileTime(const char* pFileName)
	{
		return 0;
	}
	virtual void FileTimeToString(char* pStrip, int maxCharsIncludingTerminator, long fileTime)
	{

	}
	virtual bool IsOk(FileHandle_t file)
	{
		return false;
	}
	virtual void Flush(FileHandle_t file)
	{

	}
	virtual bool EndOfFile(FileHandle_t file)
	{
		return false;
	}
	virtual int Read(void* pOutput, int size, FileHandle_t file)
	{
		return 0;
	}
	virtual int Write(void const* pInput, int size, FileHandle_t file)
	{
		return 0;
	}
	virtual char* ReadLine(char* pOutput, int maxChars, FileHandle_t file)
	{
		return NULL;
	}
	virtual int FPrintf(FileHandle_t file, char* pFormat, ...)
	{
		return 0;
	}
	virtual char* GetReadBuffer(FileHandle_t file, char* pBuffer)
	{
		return NULL;
	}
	virtual void ReleaseReadBuffer(FileHandle_t file, char* pBuffer)
	{

	}
	virtual const char* FindFirst(const char* pWildCard, FileFindHandle_t* pHandle, const char* pathID = 0)
	{
		return NULL;
	}
	virtual const char* FindNext(FileFindHandle_t handle)
	{
		return NULL;
	}
	virtual bool FindIsDirectory(FileFindHandle_t handle)
	{
		return false;
	}
	virtual void FindClose(FileFindHandle_t handle)
	{

	}
	virtual void GetLocalCopy(const char* pFileName)
	{

	}
	virtual const char* GetLocalPath(const char* pFileName, char* pLocalPath, int maxlen)
	{
		return NULL;
	}
	virtual char* ParseFile(char* data, char* token, bool* wasquoted)
	{
		return NULL;
	}
	virtual bool FullPathToRelativePath(const char* pFullpath, char* pRelative)
	{
		return false;
	}
	virtual bool GetCurrentDirectory(char* pDirectory, int maxlen)
	{
		return false;
	}
	virtual void PrintOpenedFiles(void)
	{

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
		return false;
	}
	virtual void AddPackFile(const char* pPath, const char* pathID = 0)
	{
	
	}
	virtual void* OpenFromCacheForRead(const char* pFileName, const char* pOptions, const char* pathID = 0)
	{
		return NULL;
	}
};

EXPOSE_INTERFACE(CFileSystemNar, IFileSystem, FILESYSTEM_INTERFACE_VERSION)
