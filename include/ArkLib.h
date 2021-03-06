////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Ark Library Wrapper class
/// 
/// @author   parkkh
/// @date     Thursday, January 07, 2010  11:18:16 AM
/// 
/// Copyright(C) 2009-2010 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ARK_LIB_H_
#define _ARK_LIB_H_

#include "Ark.h"


#ifdef _WIN64
#	ifdef _DEBUG
#		define ARK_DLL_FILE_NAME		_T("Ark64_d.dll")
#	else
#		define ARK_DLL_FILE_NAME		_T("Ark64.dll")
#	endif
#	define ARK_DLL_RELEASE_FILE_NAME	_T("Ark64.dll")
#elif defined(_WIN32)
#	ifdef _DEBUG
#		define ARK_DLL_FILE_NAME		_T("Ark32_d.dll")
#	else
#		define ARK_DLL_FILE_NAME		_T("Ark32.dll")
#	endif
#	define ARK_DLL_RELEASE_FILE_NAME	_T("Ark32.dll")
#endif

#ifndef _WIN32
#	if defined(__x86_64__) || defined(__ia64__) || defined(_M_AMD64) || defined(_M_IA64) || defined(_WIN64) || defined(__alpha__) || defined(__s390__)
#		define ARK_DLL_FILE_NAME	"/usr/local/lib/libark64.so"
#	else
#		define ARK_DLL_FILE_NAME	"/usr/local/lib/libark32.so"
#	endif
#	define ARK_DLL_RELEASE_FILE_NAME	ARK_DLL_FILE_NAME
#endif


#define ARK_EXPORTED_FUNCTION_NAME				"CreateArk"
#define ARKCOMPRESSOR_EXPORTED_FUNCTION_NAME	"CreateArkCompressor"

#ifndef _WIN32
#	include <dlfcn.h>
#	define HMODULE	void*
#	define LoadLibrary(name)				dlopen(name, RTLD_NOW | RTLD_GLOBAL)
#	define GetProcAddress(handle, func)		dlsym(handle, func)
#	define FreeLibrary(handle)				dlclose(handle)
#	include <string>
#endif



#ifndef _INC_TCHAR
#	ifdef _UNICODE
#		define _T(x)		L##x
#	else
#		define _T(x)	x
#	endif
#endif

#ifdef _UNICODE
	typedef  const wchar_t* LPCTSTR;
#else
	typedef  const char* LPCTSTR;
#endif

typedef IArk*			(*LPCREATEARK)(UINT32 version);
typedef IArkCompressor* (*LPCREATEARKCOMPRESSOR)(UINT32 version);

#ifndef ASSERT
#   include <stdio.h>
#	define ASSERT(x)	printf("Assert at %s %d\n", __FILE__, __LINE__)
#endif




class CArkLib : public IArk
{
public :
	CArkLib()
	{
		m_hDll = NULL;
		m_pCreateArk = NULL;
		m_pCreateArkCompressor = NULL;
		m_pArk = NULL;
	}

	~CArkLib()
	{
		Destroy();
	}

#ifndef _ARK_USE_AS_LIB
	// .dll 로 사용하는 경우
	ARKERR	 Create(LPCTSTR szDllPathName)
	{
		if(m_hDll) {ASSERT(0); return ARKERR_ALREADY_DLL_CREATED;}

		// check os version
#ifdef _WIN32
		OSVERSIONINFO osv;
		osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (GetVersionEx(&osv)==FALSE || 
			osv.dwPlatformId <=VER_PLATFORM_WIN32_WINDOWS)		// does not support 98
		{
			return ARKERR_UNSUPPORTED_OS;
		}
#endif

		m_hDll = LoadLibrary(szDllPathName);
		if(m_hDll==NULL)
		{
			m_hDll = LoadLibrary(ARK_DLL_RELEASE_FILE_NAME);
			if(m_hDll==NULL)
			{
				#ifndef _WIN32
				printf("Load %s failed.(Reason: '%s')\n", szDllPathName, dlerror());
				#endif
				ASSERT(0);
				return ARKERR_LOADLIBRARY_FAILED;
			}
		}

		m_pCreateArk = (LPCREATEARK)GetProcAddress(m_hDll, ARK_EXPORTED_FUNCTION_NAME);
		m_pCreateArkCompressor = (LPCREATEARKCOMPRESSOR)GetProcAddress(m_hDll, ARKCOMPRESSOR_EXPORTED_FUNCTION_NAME);

		if(m_pCreateArk==NULL)
		{
			#ifndef _WIN32
			printf("dlsym() failed.(Reason: '%s')\n", dlerror());
			#endif

			ASSERT(0);
			FreeLibrary(m_hDll);
			m_hDll = NULL;
			return ARKERR_GETPROCADDRESS_FAILED;
		}

		m_pArk = (m_pCreateArk)(ARK_LIBRARY_VERSION);
		if(m_pArk==NULL)
		{
			ASSERT(0);
			FreeLibrary(m_hDll);
			m_hDll = NULL;
			return ARKERR_INVALID_VERSION;
		}

		return ARKERR_NOERR;
	}
#endif	//

	IArkCompressor* CreateCompressor()
	{
		return m_pCreateArkCompressor ? m_pCreateArkCompressor(ARK_LIBRARY_VERSION) : NULL;
	}

	IArk*			GetIArk()
	{
		return m_pArk;
	}


#ifdef _ARK_USE_AS_LIB
	// .lib 로 사용하는 경우
	ARKERR	 CreateLib()
	{
		m_pArk = CreateArkLib(ARK_LIBRARY_VERSION);
		if(m_pArk==NULL)
		{
			ASSERT(0);
			return ARKERR_INVALID_VERSION;
		}
		return ARKERR_NOERR;
	}
#endif

	BOOL	IsCreated()
	{
		return m_pArk ? TRUE : FALSE;
	}

	void	Destroy()
	{
		if(m_pArk)
			m_pArk->Release();
		m_pArk = NULL;
		m_pCreateArk = NULL;
		if(m_hDll) FreeLibrary(m_hDll);
		m_hDll = NULL;
	}

public :				// IArk
	ARKMETHOD(void)				Release() 
	{
		Destroy();
	}

#ifndef _WIN32
	// posix 용 std::string 인터페이스
	ARKMETHOD(BOOL) Open(std::string name, std::string pass){ return Open(name.c_str(), pass.c_str()); }
	ARKMETHOD(BOOL) Open(std::string name, const char* pass){ return Open(name.c_str(), pass); }
	ARKMETHOD(BOOL)	ExtractOneTo(int index,std::string dest){ return ExtractOneTo(index, dest.c_str()); };
	ARKMETHOD(BOOL)	ExtractAllTo(std::string dest)			{ return ExtractAllTo(dest.c_str()); };
	ARKMETHOD(BOOL)	ExtractMultiFileTo(std::string dest)	{ return ExtractMultiFileTo(dest.c_str()); }
	ARKMETHOD(ARK_FF)	CheckFormat(std::string name) const	{ return CheckFormat(name.c_str()); }
#endif


	ARKMETHOD(BOOL)  			Open(LPCSTR  szFilePathName, LPCSTR szPassword=NULL)
	{
		return m_pArk ? m_pArk->Open(szFilePathName, szPassword) : FALSE;
	}
	ARKMETHOD(BOOL)  			Open(LPCWSTR szFilePathName, LPCSTR szPassword=NULL)
	{
		return m_pArk ? m_pArk->Open(szFilePathName, szPassword) : FALSE;
	}

	ARKMETHOD(void)				Close()
	{
		if(m_pArk) m_pArk->Close();
	}

	ARKMETHOD(BOOL)				TestArchive()
	{
		return m_pArk ? m_pArk->TestArchive() : FALSE;
	}

	ARKMETHOD(ARK_FF)  			CheckFormat(LPCSTR  filePath) const
	{
		return  m_pArk ? m_pArk->CheckFormat(filePath) : ARK_FF_UNKNOWN;
	}
	ARKMETHOD(ARK_FF)  			CheckFormat(LPCWSTR filePath) const
	{
		return  m_pArk ? m_pArk->CheckFormat(filePath) : ARK_FF_UNKNOWN;
	}
	ARKMETHOD(ARK_FF)  			CheckFormat(const unsigned char* buffer, int bufLen) const
	{
		return  m_pArk ? m_pArk->CheckFormat(buffer, bufLen) : ARK_FF_UNKNOWN;
	}

	ARKMETHOD(void)				SetPassword(LPCSTR password)
	{
		if(m_pArk) m_pArk->SetPassword(password);
	}

	ARKMETHOD(int)				GetFileItemCount() const
	{
		return m_pArk ? m_pArk->GetFileItemCount() : 0;
	}

	ARKMETHOD(const SArkFileItem*)	GetFileItem(int index) const
	{
		return m_pArk ? m_pArk->GetFileItem(index) : NULL;
	}

	ARKMETHOD(ARK_FF)				GetFileFormat() const
	{
		return m_pArk ? m_pArk->GetFileFormat() : ARK_FF_UNKNOWN;
	}

	ARKMETHOD(BOOL)				IsBrokenArchive() const
	{
		return m_pArk ? m_pArk->IsBrokenArchive() : FALSE;
	}

	ARKMETHOD(BOOL)				IsEncryptedArchive() const
	{
		return m_pArk ? m_pArk->IsEncryptedArchive() : FALSE;
	}

	ARKMETHOD(BOOL)				IsSolidArchive() const
	{
		return m_pArk ? m_pArk->IsSolidArchive() : FALSE;
	}

	ARKMETHOD(BOOL)				IsOpened() const
	{
		return m_pArk ? m_pArk->IsOpened() : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractAllTo(LPCSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractAllTo(szDestPath) : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractAllTo(LPCWSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractAllTo(szDestPath) : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractAllTo(IArkSimpleOutStream* pOutStream)
	{
		return m_pArk ? m_pArk->ExtractAllTo(pOutStream) : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractOneTo(int index, LPCSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, szDestPath) : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractOneTo(int index, LPCWSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, szDestPath) : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractOneTo(int index, IArkSimpleOutStream* pOutStream)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, pOutStream) : FALSE;
	}

	ARKMETHOD(BOOL)				ExtractOneAs(int index, LPCWSTR filePathName)
	{
		return m_pArk ? m_pArk->ExtractOneAs(index, filePathName) : FALSE;
	}


	ARKMETHOD(BOOL)				AddIndex2ExtractList(int nIndex)
	{
		return m_pArk ? m_pArk->AddIndex2ExtractList(nIndex) : FALSE;
	}

	ARKMETHOD(void)				ClearExtractList()
	{
		if(m_pArk) m_pArk->ClearExtractList();
	}

	ARKMETHOD(int)				GetExtractListCount() const
	{
		return m_pArk ? m_pArk->GetExtractListCount() : 0;
	}

	ARKMETHOD(BOOL)				ExtractMultiFileTo(LPCSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractMultiFileTo(szDestPath) : FALSE;
	}
	ARKMETHOD(BOOL)				ExtractMultiFileTo(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL)
	{
		return m_pArk ? m_pArk->ExtractMultiFileTo(szDestPath, szPath2Remove) : FALSE;
	}
	ARKMETHOD(BOOL)				ExtractMultiFileTo(IArkSimpleOutStream* pOutStream)
	{
		return m_pArk ? m_pArk->ExtractMultiFileTo(pOutStream) : FALSE;
	}


	ARKMETHOD(BOOL)				SetEvent(IArkEvent* pProgress)
	{
		return m_pArk ? m_pArk->SetEvent(pProgress) : FALSE;
	}

	ARKMETHOD(ARKERR)			GetLastError() const
	{
		return m_pArk ? m_pArk->GetLastError() : ARKERR_LIBRARY_NOT_LOADED ;
	}

	ARKMETHOD(void)				SetCodePage(int n)
	{
		if(m_pArk) m_pArk->SetCodePage(n);
	}

	ARKMETHOD(LPCWSTR)			EncryptionMethod2Str(ARK_ENCRYPTION_METHOD method) const
	{
		return m_pArk ? m_pArk->EncryptionMethod2Str(method) : NULL;
	}

	ARKMETHOD(LPCWSTR)			CompressionMethod2Str(ARK_COMPRESSION_METHOD method) const
	{
		return m_pArk ? m_pArk->CompressionMethod2Str(method) : NULL;
	}

	ARKMETHOD(LPCWSTR)			FileFormat2Str(ARK_FF ff) const
	{
		return m_pArk ? m_pArk->FileFormat2Str(ff) : NULL;
	}

	ARKMETHOD(void)				SetGlobalOpt(BOOL bPrintAssert)
	{
		if(m_pArk) m_pArk->SetGlobalOpt(bPrintAssert);
	}

	ARKMETHOD(INT64)			GetArchiveFileSize() const
	{
		return m_pArk ? m_pArk->GetArchiveFileSize() : 0;
	}
	ARKMETHOD(INT64)			GetArchiveStartPos() const 
	{
		return m_pArk ? m_pArk->GetArchiveStartPos() : 0;
	}

	ARKMETHOD(LPCWSTR)			GetFilePathName() const
	{
		return m_pArk ? m_pArk->GetFilePathName() : NULL;
	}
	ARKMETHOD(int)				FindIndex(LPCWSTR szFileNameW, LPCSTR szFileNameA, BOOL bCaseSensitive) const
	{
		return m_pArk ? m_pArk->FindIndex(szFileNameW, szFileNameA, bCaseSensitive) : -1;
	}

	ARKMETHOD(LPCWSTR)			GetArchiveComment() const
	{
		return m_pArk ?m_pArk->GetArchiveComment() : NULL;
	}

	ARKMETHOD(ARK_MULTIVOL_STYLE) GetMultivolStyle() const
	{
		return m_pArk ?m_pArk->GetMultivolStyle() : ARK_MULTIVOL_STYLE_NONE;
	}

	//////////////////////////
	// undocumented 
	ARKMETHOD(LPCWSTR)			_GetAlias()
	{
		return m_pArk ? m_pArk->_GetAlias() : NULL;
	}

	ARKMETHOD(void)				_SetAlias(LPCWSTR szAlias)
	{
		if(m_pArk) m_pArk->_SetAlias(szAlias);
	}

	ARKMETHOD(const void*)		_GetBondFileInfo()
	{
		return m_pArk ? m_pArk->_GetBondFileInfo() : 0;
	}

	ARKMETHOD(void)				_SetUserKey(void* key)
	{
		if(m_pArk) m_pArk->_SetUserKey(key);
	}

	ARKMETHOD(UINT32)  				_CheckCRC32(LPCWSTR filePath)
	{
		return  m_pArk ? m_pArk->_CheckCRC32(filePath) : 0;
	}

	ARKMETHOD(void*)				_GetExtractor()
	{
		return  m_pArk ? m_pArk->_GetExtractor(): NULL;
	}

	ARKMETHOD(void)				_Test()
	{
		if(m_pArk) m_pArk->_Test();
	}

	ARKMETHOD(BOOL)				_DisableFile(int index)
	{
		return m_pArk ?m_pArk->_DisableFile(index) : FALSE;
	}

private :
	HMODULE					m_hDll;
	LPCREATEARK				m_pCreateArk;
	LPCREATEARKCOMPRESSOR	m_pCreateArkCompressor;
	IArk*					m_pArk;
};


#endif // _ARK_LIB_H_

