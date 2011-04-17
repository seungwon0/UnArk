////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
///                                      Ark Library 3
/// 
/// ※ 만일 컴파일 오류등으로 인해서 이 파일을 수정하여야 하는 경우가 발생할 경우 
///    관련 내용을 꼭 알려주시기 바랍니다. 
///    알려주시면 매번 업데이트마다 사용자님이 헤더파일을 수정하는 불편이 발생하지 않도록 
///    전처리기등을 추가하도록 하겠습니다.
///
/// @author   parkkh
/// @date     Tuesday, December 22, 2009  9:22:23 AM
/// 
/// Copyright(C) 2008-2011 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _ARK_H_
#define _ARK_H_

// ArkLibrary 버전 (Ark.h 와 ArkXX.dll 파일의 버전이 동일한지 여부 판단용)
#define ARK_LIBRARY_VERSION								0x20110117


// 에러코드
enum ARKERR 
{
	ARKERR_NOERR										= 0x00,
	ARKERR_CANT_OPEN_FILE								= 0x01,		// 파일 열기 실패
	ARKERR_CANT_READ_SIG								= 0x02,		// signature 읽기 실패
	ARKERR_AT_READ_CONTAINER_HEADER						= 0x03,		// 컨테이너 헤더가 손상되었음
	ARKERR_INVALID_FILENAME_LENGTH						= 0x04,		// 파일명 길이에 문제
	ARKERR_READ_FILE_NAME_FAILED						= 0x05,		// 파일이름 읽기 실패
	ARKERR_INVALID_EXTRAFIELD_LENGTH					= 0x06,		// extra field 읽기
	ARKERR_READ_EXTRAFILED_FAILED						= 0x07,		// extra field 읽기 실패
	ARKERR_CANT_READ_CENTRAL_DIRECTORY_STRUCTURE		= 0x08,		// (zip) Central Directory 정보를 읽는데 실패하였음
	ARKERR_INVALID_FILENAME_SIZE						= 0x09,		// 파일명 길이 정보가 잘못되었음
	ARKERR_INVALID_EXTRAFIELD_SIZE						= 0x10,		// (zip) ExtraField 정보 길이가 잘못되었음
	ARKERR_INVALID_FILECOMMENT_SIZE						= 0x11,		// Comment 정보 길이가 잘못되었음
	ARKERR_CANT_READ_CONTAINER_HEADER					= 0x12,		// 컨테이너의 헤더에 문제가 있음
	ARKERR_MEM_ALLOC_FAILED								= 0x13,		// 메모리 할당 실패
	ARKERR_CANT_READ_DATA								= 0x15,		// 압축 데이타 읽기 실패
	ARKERR_INFLATE_FAILED								= 0x16,		// Inflate 함수 호출중 에러 발생
	ARKERR_USER_ABORTED									= 0x17,		// 사용자 중지
	ARKERR_INVALID_FILE_CRC								= 0x18,		// 압축 해제후 CRC 에러 발생
	ARKERR_UNKNOWN_COMPRESSION_METHOD					= 0x19,		// 모르는(혹은 지원하지 않는) 압축방식
	ARKERR_PASSWD_NOT_SET								= 0x20,		// 암호걸린 파일인데 암호가 지정되지 않았음
	ARKERR_INVALID_PASSWD								= 0x21,		// 암호가 틀렸음
	ARKERR_WRITE_FAIL									= 0x30,		// 파일 쓰다가 실패
	ARKERR_CANT_OPEN_DEST_FILE							= 0x31,		// 대상 파일을 만들 수 없음
	ARKERR_BZIP2_ERROR									= 0x32,		// BZIP2 압축해제중 에러 발생
	ARKERR_INVALID_DEST_PATH							= 0x33,		// 경로명에 ../ 이 포함된 경우, 대상 경로에 접근이 불가능한 경우
	ARKERR_CANT_CREATE_FOLDER							= 0x34,		// 경로 생성 실패
	ARKERR_DATA_CORRUPTED								= 0x35,		// 압축푸는데 데이타가 손상됨 + RAR 분할압축 파일의 뒷부분이 없음
	ARKERR_CANT_OPEN_FILE_TO_WRITE						= 0x36,		// 쓰기용으로 파일 열기 실패
	ARKERR_INVALID_INDEX								= 0x37,		// 압축풀 대상의 index 파라메터가 잘못됨
	ARKERR_CANT_READ_CODEC_HEADER						= 0x38,		// 압축 코덱의 헤더를 읽는데 에러
	ARKERR_CANT_INITIALIZE_CODEC						= 0x39,		// 코덱 초기화 실패
	ARKERR_LZMA_ERROR									= 0x40,		// LZMA 압축 해제중 에러 발생
	ARKERR_PPMD_ERROR									= 0x41,		// ppmd 에러
	ARKERR_CANT_SET_OUT_FILE_SIZE						= 0x42,		// 출력파일의 SetSize() 실패
	ARKERR_NOT_MATCH_FILE_SIZE							= 0x43,		// 압축을 푼 파일 크기가 맞지 않음
	ARKERR_NOT_A_FIRST_VOLUME_FILE						= 0x44,		// 분할 압축 파일중 첫번째 파일이 아님
	ARKERR_NOT_OPENED									= 0x45,		// 파일이 열려있지 않음
	ARKERR_NOT_SUPPORTED_ENCRYPTION_METHOD				= 0x46,		// 지원하지 않는 암호 방식
	ARKERR_INTERNAL										= 0x47,		// 내부 에러
	ARKERR_NOT_SUPPORTED_FILEFORMAT						= 0x48,		// 지원하지 않는 파일 포맷
	ARKERR_UNKNOWN_FILEFORMAT							= 0x49,		// 압축파일이 아님
	ARKERR_FILENAME_EXCED_RANGE							= 0x50,		// 경로명이 너무 길어서 파일이나 폴더를 만들 수 없음
	ARKERR_LZ_ERROR										= 0x52,		// lz 에러
	ARKERR_NOTIMPL										= 0x53,		// not implmented
	ARKERR_DISK_FULL									= 0x54,		// 파일 쓰다가 실패
	ARKERR_FILE_TRUNCATED								= 0x55,		// 파일의 뒷부분이 잘렸음
	ARKERR_CANT_DO_THAT_WHILE_WORKING					= 0x56,		// 압축 해제 작업중에는 파일을 열거나 닫을 수 없음
	ARKERR_CANNOT_FIND_NEXT_VOLUME						= 0x57,		// 분할 압축된 파일의 다음 파일을 찾을 수 없음
	ARKERR_NOT_ARCHIVE_FILE								= 0x58,		// 압축파일이 아님 (Open() 호출시 명백히 압축파일이 아닌 경우 발생)
	ARKERR_USER_SKIP									= 0x59,		// 사용자가 건너띄기 했음.

	ARKERR_CORRUPTED_FILE								= 0x100,	// 파일이 손상되었음
	ARKERR_INVALID_FILE									= 0x101,	// 포맷이 다르다
	ARKERR_CANT_READ_FILE								= 0x102,	// 파일을 읽을 수 없음

	ARKERR_INVALID_VERSION								= 0x200,	// 헤더파일과 dll 의 버전이 맞지 않음
	ARKERR_ENCRYPTED_BOND_FILE							= 0x201,	// 압축 해제 불가(암호화된 bond 파일임)

	ARKERR_7ZERR_BROKEN_ARCHIVE							= 0x300,	// 7z.dll 으로 열때 에러가 발생(깨진파일)
	ARKERR_LOAD_7Z_DLL_FAILED							= 0x301,	// 7z.dll 열다가 에러 발생

	ARKERR_CANT_CREATE_FILE								= 0x401,	// 파일을 쓰기용으로 생성하지 못함
	ARKERR_INIT_NOT_CALLED								= 0x402,	// Init() 함수가 호출되지 않았음
	ARKERR_INVALID_PARAM								= 0x403,	// 잘못된 파라메터로 호출하였음
	ARKERR_CANT_OPEN_INPUT_SFX							= 0x404,	// SFX 파일을 열지 못함

	ARKERR_ALREADY_DLL_CREATED							= 0x902,	// (CArkLib) 이미 ARK DLL 파일을 로드하였음
	ARKERR_LOADLIBRARY_FAILED							= 0x903,	// (CArkLib) LoadLibrary() 호출 실패
	ARKERR_GETPROCADDRESS_FAILED						= 0x904,	// (CArkLib) GetProcAddress() 호출 실패
	ARKERR_UNSUPPORTED_OS								= 0x905,	// (CArkLib) 지원하지 않는 os 
	ARKERR_LIBRARY_NOT_LOADED							= 0x906,	// (CArkLib) 라이브러리를 로드하지 않았거나 로드하는데 실패하였음
};


// ARK FILE FORMAT
enum ARK_FF
{
	ARK_FF_UNKNOWN,					// 파일 포맷을 알 수 없음
	ARK_FF_NOT_ARCHIVE_FORMAT,		// 명백히 압축 파일이 아님 (실행파일, 이미지파일 등등..)

	ARK_FF_ZIP,						// zip, zipx
	ARK_FF_ALZ,
	ARK_FF_ALZ_SECONDVOL,			// 분할 alz 파일의 2번째 이후 압축파일
	ARK_FF_LZH,
	ARK_FF_RAR,
	ARK_FF_RAR_SECONDVOL,			// 분할 RAR 파일의 2번째 이후 압축파일
	ARK_FF_7Z,
	ARK_FF_7ZSPLIT,					// 7z 파일의 뒷부분이 잘렸고 확장자가 .001 인 파일 (.7z.001 ~ .7z.NNN)
	ARK_FF_7ZBROKEN,				// 7z 파일의 뒷부분이 잘렸거나 헤더가 손상된 파일
	ARK_FF_TAR,
	ARK_FF_CAB,
	ARK_FF_ISO,						// iso, joliet
	ARK_FF_UDF,
	ARK_FF_UDFBROKEN,				// 뒷부분이 잘린 UDF 
	ARK_FF_SPLIT,					// 확장자가 .001 인 파일 (.001 ~ .NNN)
	ARK_FF_BOND,					// hv3
	ARK_FF_GZ,
	ARK_FF_BZ2,
	ARK_FF_NSIS,					// nsis exe
	ARK_FF_BH,						// blakhole
	ARK_FF_EGG,
	ARK_FF_EGG_NOTFIRSTVOL,			// 분할 압축의 첫번째 볼륨이 아닌 파일
	ARK_FF_XZ,
	ARK_FF_WIM,
	ARK_FF_ARC,						// FreeArc - 파일 목록열기만 지원
	ARK_FF_Z,						// .Z (unix compress)
	ARK_FF_ARJ,						// arj 
	ARK_FF_SIT,						// sit (not supported)
};

// 암호화 방식
enum ARK_ENCRYPTION_METHOD
{
	ARK_ENCRYPTION_METHOD_NONE			=	0x00,
	ARK_ENCRYPTION_METHOD_ZIP			=	0x01,			// ZipCrypto
	ARK_ENCRYPTION_METHOD_AES128		=	0x02,
	ARK_ENCRYPTION_METHOD_AES192		=	0x03,			// 실제로는 사용되지 않음
	ARK_ENCRYPTION_METHOD_AES256		=	0x04,

	ARK_ENCRYPTION_METHOD_EGG_ZIP		=	0x05,			// EGG 포맷에서 사용
	ARK_ENCRYPTION_METHOD_EGG_AES128	=	0x06,
	ARK_ENCRYPTION_METHOD_EGG_AES256	=	0x07,

	ARK_ENCRYPTION_METHOD_RAR			=	0x08,			// RAR 암호 방식
	ARK_ENCRYPTION_METHOD_GARBLE		=	0x09,			// ARJ 암호 방식

	ARK_ENCRYPTION_METHOD_ETC			=	0x99,
};

// 압축 방식
enum ARK_COMPRESSION_METHOD
{
	/////////////////////////////////////////////////////////////////
	// zip 에서 사용하는것들, zip 포맷에 정의된 값과 맞추었다.	
	// (http://www.pkware.com/documents/casestudies/APPNOTE.TXT 참고)
	ARK_COMPRESSION_METHOD_STORE		=	0,
	ARK_COMPRESSION_METHOD_DEFLATE		=	8,

	ARK_COMPRESSION_METHOD_DEFLATE64	=	9,
	ARK_COMPRESSION_METHOD_BZIP2		=	12,
	ARK_COMPRESSION_METHOD_LZMA			=	14,		// zipx, 7zip ...
	ARK_COMPRESSION_METHOD_JPEG			=	96,		// zipx
	ARK_COMPRESSION_METHOD_PPMD			=	98,		// zipx, 7zip
	ARK_COMPRESSION_METHOD_AES			=	99,		// aes 로 암호화된 zip 파일. 실제 압축 방법은 다른곳에 저장된다.
	// 
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// ETC
	ARK_COMPRESSION_METHOD_FUSE			=	300,	// bh 에서 사용 
	ARK_COMPRESSION_METHOD_FUSE6		=	301,	// bh 에서 사용 
	ARK_COMPRESSION_METHOD_AZO			=	302,	// egg 에서 사용
	ARK_COMPRESSION_METHOD_COMPRESS		=	303,	// .Z 에서 사용

	ARK_COMPRESSION_METHOD_RAR15		=	400,	// RAR 1.5
	ARK_COMPRESSION_METHOD_RAR20		=	401,	// RAR 2.X
	ARK_COMPRESSION_METHOD_RAR26		=	402,	// RAR 2.X & 2GB 이상
	ARK_COMPRESSION_METHOD_RAR29		=	403,	// RAR 3.X
	ARK_COMPRESSION_METHOD_RAR36		=	404,	// RAR 3.X alternative hash

	ARK_COMPRESSION_METHOD_MSZIP		=	500,	// CAB
	ARK_COMPRESSION_METHOD_LHA			=	501,	// lzh
	ARK_COMPRESSION_METHOD_LZMA2		=	502,	// 7z
	ARK_COMPRESSION_METHOD_BCJ			=	503,	// 7z
	ARK_COMPRESSION_METHOD_BCJ2			=	504,	// 7z
	ARK_COMPRESSION_METHOD_LZX			=	505,	// CAB
	ARK_COMPRESSION_METHOD_LZXWIM		=	506,	// wim
	ARK_COMPRESSION_METHOD_QUANTUM		=	507,	// cab...

	ARK_COMPRESSION_METHOD_LH0			=	600,	// -lh0-
	ARK_COMPRESSION_METHOD_LH1			=	601,	// -lh1-
	ARK_COMPRESSION_METHOD_LH2			=	602,	// -lh2-
	ARK_COMPRESSION_METHOD_LH3			=	603,	// -lh3-
	ARK_COMPRESSION_METHOD_LH4			=	604,	// -lh4-
	ARK_COMPRESSION_METHOD_LH5			=	605,	// -lh5-
	ARK_COMPRESSION_METHOD_LH6			=	606,	// -lh6-
	ARK_COMPRESSION_METHOD_LH7			=	607,	// -lh7-
	ARK_COMPRESSION_METHOD_LZS			=	608,	// -lzs-
	ARK_COMPRESSION_METHOD_LZ5			=	609,	// -lz5-
	ARK_COMPRESSION_METHOD_LZ4			=	610,	// -lz4-
	ARK_COMPRESSION_METHOD_LHD			=	611,	// -lhd-

	ARK_COMPRESSION_METHOD_LZX15		=	715,	// LZX (WINDOW SIZE 15bit)
	ARK_COMPRESSION_METHOD_LZX16		=	716,	// 
	ARK_COMPRESSION_METHOD_LZX17		=	717,	// 
	ARK_COMPRESSION_METHOD_LZX18		=	718,	// 
	ARK_COMPRESSION_METHOD_LZX19		=	719,	// 
	ARK_COMPRESSION_METHOD_LZX20		=	720,	// 
	ARK_COMPRESSION_METHOD_LZX21		=	721,	// LZX (WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_ARJ1			=	801,	// Arj Method 1
	ARK_COMPRESSION_METHOD_ARJ2			=	802,	//            2
	ARK_COMPRESSION_METHOD_ARJ3			=	803,	//            3
	ARK_COMPRESSION_METHOD_ARJ4			=	804,	//            4

	// 
	/////////////////////////////////////////////////////////////////

	ARK_COMPRESSION_METHOD_UNKNOWN		=	999,	// unknown
};

// 분할 압축 스타일
enum ARK_MULTIVOL_STYLE
{
	ARK_MULTIVOL_STYLE_NONE,			// 분할 압축파일이 아님
	ARK_MULTIVOL_STYLE_001,				// 7zip 의 001, 002, .. 스타일
	ARK_MULTIVOL_STYLE_WINZIP,			// winzip 스타일  (z01, z02 ..... zip)
	ARK_MULTIVOL_STYLE_ALZ,				// alzip 의 alz, a00, a01, a02, .. 스타일
	ARK_MULTIVOL_STYLE_EGG,				// vol1.egg vol2.egg vol3.egg ... 스타일
	ARK_MULTIVOL_STYLE_RAR,				// part1.rar part2.rar ... 스타일
	ARK_MULTIVOL_STYLE_R00,				// .rar .r00 .r01 스타일
	ARK_MULTIVOL_STYLE_ARJ,				// .arj .a01 .a02 스타일
};


// 파일 속성
#define ARK_FILEATTR					int
#define ARK_FILEATTR_NONE				0x00
#define ARK_FILEATTR_READONLY			0x01	// FILE_ATTRIBUTE_READONLY
#define ARK_FILEATTR_HIDDEN				0x02	// FILE_ATTRIBUTE_HIDDEN
#define ARK_FILEATTR_SYSTEM				0x04	// FILE_ATTRIBUTE_SYSTEM
#define ARK_FILEATTR_DIRECTORY			0x10	// FILE_ATTRIBUTE_DIRECTORY
#define ARK_FILEATTR_FILE				0x20	// FILE_ATTRIBUTE_ARCHIVE

// 코드 페이지
#define ARK_CP_ACP						0		// == CP_ACP
#define ARK_CP_KOR						949		
#define ARK_CP_UTF8						65001	// == CP_UTF8
#define ARK_CP_UTF8_MAC					65002	// 맥용 utf8 코드 페이지


// 기타 정의
#define ARK_FILESIZE_UNKNOWN			(0xffffffffffffffffLL)	// 파일 크기를 알 수 없을때 사용되는 값

// WIN32 이외의 시스템일 경우 기본 타입 정의
#ifndef TRUE
	typedef int                 BOOL;
	#define FALSE               0
	#define TRUE                1
	typedef char				CHAR;
	typedef wchar_t				WCHAR;
	typedef unsigned int		UINT32;
	typedef const char*			LPCSTR;
	typedef const wchar_t*		LPCWSTR;
#endif

#ifndef PURE
#	define PURE                = 0
#endif

#ifdef _WIN32
	typedef signed __int64      INT64;
	#define WINAPI				__stdcall
#else
	typedef signed long long	INT64;
	#define WINAPI				
#endif

// use os default packing
#pragma pack()

// 인터페이스 메써드 타입 정의
#define ARKMETHOD(type)	virtual type WINAPI

#define ARK_TIME_T			INT64					// time_t 와 동일
struct SArkFileTime									// FILETIME (ntfs) 과 동일
{
	UINT32 dwLowDateTime;
	UINT32 dwHighDateTime;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일 아이템 정보
//
struct SArkFileItem
{
	CHAR*					fileName;							// 압축파일에 저장된 파일명 (이 이름은 폴더 경로명도 포함한다)
	WCHAR*					fileNameW;
	WCHAR*					fileCommentW;
	ARK_TIME_T				fileTime;							// last modified(write) time
	SArkFileTime			fileTimeNtfs;						// ''
	INT64					compressedSize;
	INT64					uncompressedSize;
	ARK_ENCRYPTION_METHOD	encryptionMedhod;
	ARK_FILEATTR			attrib;
	UINT32					crc32;
	ARK_COMPRESSION_METHOD	compressionMethod;

	BOOL					IsFolder() const { return attrib & ARK_FILEATTR_DIRECTORY ? TRUE : FALSE;}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 해제 진행 상황 정보
//
struct SArkProgressInfo
{
	float		fCurPercent;		// 현재 파일의 압축 해제 진행율(%)
	float		fTotPercent;		// 전체 파일의 압축 해제 진행율(%)
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 해제 진행 상황
//
enum ARK_OVERWRITE_MODE
{
	ARK_OVERWRITE_MODE_OVERWRITE,
	ARK_OVERWRITE_MODE_SKIP, 
	ARK_OVERWRITE_MODE_RENAME,
};
#define ARK_MAX_PATH				300
struct IArkEvent
{
	ARKMETHOD(void)					OnOpening(const SArkFileItem* pFileItem, float progress, BOOL& bStop) PURE;

	ARKMETHOD(void)					OnStartFile(const SArkFileItem* pFileItem, BOOL& bStopCurrent, BOOL& bStopAll) PURE;
	ARKMETHOD(void)					OnProgressFile(const SArkProgressInfo* pProgressInfo, BOOL& bStopCurrent, BOOL& bStopAll) PURE;
	ARKMETHOD(void)					OnCompleteFile(const SArkProgressInfo* pProgressInfo, ARKERR nErr) PURE;

	ARKMETHOD(void)					OnError(ARKERR nErr, const SArkFileItem* pFileItem, BOOL bIsWarning, BOOL& bStopAll) PURE;
	ARKMETHOD(void)					OnMultiVolumeFileChanged(LPCWSTR szPathFileName) PURE;

	ARKMETHOD(void)					OnAskOverwrite(const SArkFileItem* pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE& overwrite, WCHAR pathName2Rename[ARK_MAX_PATH]) PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 파일 출력 스트림
//
struct IArkSimpleOutStream
{
	ARKMETHOD(BOOL)					Open(LPCWSTR szPathName) PURE;
	ARKMETHOD(BOOL)					SetSize(INT64 nSize) PURE;
	ARKMETHOD(BOOL)					Write(const void* lpBuffer, UINT32 nNumberOfBytesToWrite) PURE;
	ARKMETHOD(BOOL)					Close() PURE;
	ARKMETHOD(BOOL)					CreateFolder(LPCWSTR szPathName) PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일의 압축 해제 인터페이스
//
struct IArk
{
	ARKMETHOD(void)					Release() PURE;
									
	ARKMETHOD(BOOL)  				Open(LPCSTR  filePath, LPCSTR password) PURE; 
	ARKMETHOD(BOOL)  				Open(LPCWSTR filePath, LPCSTR password) PURE; 
	ARKMETHOD(void)					Close() PURE;
	ARKMETHOD(BOOL)  				TestArchive() PURE; 

	ARKMETHOD(ARK_FF)  				CheckFormat(LPCSTR  filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(LPCWSTR filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(const unsigned char* buffer, int bufLen) const PURE; 

	ARKMETHOD(void)					SetPassword(LPCSTR password) PURE;
	ARKMETHOD(int)					GetFileItemCount() const PURE;
	ARKMETHOD(const SArkFileItem*)	GetFileItem(int index) const PURE;
	ARKMETHOD(ARK_FF)				GetFileFormat() const PURE;
	ARKMETHOD(BOOL)					IsBrokenArchive() const PURE;
	ARKMETHOD(BOOL)					IsEncryptedArchive() const PURE;
	ARKMETHOD(BOOL)					IsSolidArchive() const PURE;
	ARKMETHOD(BOOL)					IsOpened() const PURE;

	ARKMETHOD(BOOL)					ExtractAllTo(LPCSTR folderPath) PURE;						// 전체 파일 풀기
	ARKMETHOD(BOOL)					ExtractAllTo(LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL)					ExtractAllTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL)					ExtractOneTo(int index, LPCWSTR folderPath) PURE;			// 하나 파일 풀기
	ARKMETHOD(BOOL)					ExtractOneTo(int index, LPCSTR folderPath) PURE;
	ARKMETHOD(BOOL)					ExtractOneTo(int index, IArkSimpleOutStream* outStream) PURE;
	ARKMETHOD(BOOL)					ExtractOneAs(int index, LPCWSTR filePathName) PURE;			// 파일명을 지정해서 파일 하나 풀기

	ARKMETHOD(BOOL)					AddIndex2ExtractList(int index) PURE;						// 압축풀 파일 인덱스를 목록에 추가
	ARKMETHOD(void)					ClearExtractList() PURE;									// 압축풀 파일 목록 삭제하기
	ARKMETHOD(int)					GetExtractListCount() const PURE;							// 압축풀 파일 목록의 갯수
	ARKMETHOD(BOOL)					ExtractMultiFileTo(LPCSTR szDestPath) PURE;					// 몇개 파일 풀기
	ARKMETHOD(BOOL)					ExtractMultiFileTo(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL) PURE;
	ARKMETHOD(BOOL)					ExtractMultiFileTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL)					SetEvent(IArkEvent* pEvent) PURE;
	ARKMETHOD(ARKERR)				GetLastError() const PURE;
	ARKMETHOD(void)					SetCodePage(int cp) PURE;

	ARKMETHOD(LPCWSTR)				EncryptionMethod2Str(ARK_ENCRYPTION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				CompressionMethod2Str(ARK_COMPRESSION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				FileFormat2Str(ARK_FF ff) const PURE;

	ARKMETHOD(void)					SetGlobalOpt(BOOL bPrintAssert) PURE;
	ARKMETHOD(INT64)				GetArchiveFileSize() const PURE;
	ARKMETHOD(INT64)				GetArchiveStartPos() const PURE;
	ARKMETHOD(LPCWSTR)				GetFilePathName() const PURE;
	ARKMETHOD(int)					FindIndex(LPCWSTR szFileNameW, LPCSTR szFileNameA, BOOL bCaseSensitive) const PURE;
	ARKMETHOD(LPCWSTR)				GetArchiveComment() const PURE;
	ARKMETHOD(ARK_MULTIVOL_STYLE)	GetMultivolStyle() const PURE;

	///////////////////////
	// undocumented (do not use)
	ARKMETHOD(void)					_Test() PURE;
	ARKMETHOD(const void*)			_GetBondFileInfo() PURE;
	ARKMETHOD(LPCWSTR)				_GetAlias() PURE;
	ARKMETHOD(void)					_SetAlias(LPCWSTR szAlias) PURE;
	ARKMETHOD(void)					_SetUserKey(void* key) PURE;
	ARKMETHOD(UINT32)  				_CheckCRC32(LPCWSTR filePath) PURE; 
	ARKMETHOD(void*)				_GetExtractor() PURE;
	ARKMETHOD(BOOL)					_DisableFile(int index) PURE;
};


/////////////////////////////////////////////////////////
//
// 압축 옵션
//
struct SArkCompressorOpt
{
	SArkCompressorOpt(){Init();}
	void Init()
	{
		saveNTFSTime = TRUE;
		streamOutput = FALSE;
		compressionMethod = ARK_COMPRESSION_METHOD_DEFLATE;
		compressionLevel = -1;							// -1 은 Z_DEFAULT_COMPRESSION
		splitSize = 0;
		forceZip64 = FALSE;
		useDosTime2PasswordCheck = TRUE;
		utf8Comment = FALSE;
		sfxPathName = NULL;
	}
	BOOL					saveNTFSTime;				// ntfs 시간 저장 여부
	BOOL					streamOutput;				// stream 형태로 저장 - 이걸 사용할 경우 열지 못하는 프로그램이 너무 많다...
	ARK_COMPRESSION_METHOD	compressionMethod;			// 압축 방식 ( ARK_COMPRESSION_METHOD_STORE, ARK_COMPRESSION_METHOD_DEFLATE )
	int						compressionLevel;			// 압축 레벨 ( Z_NO_COMPRESSION, Z_BEST_SPEED ~ Z_BEST_COMPRESSION )
	INT64					splitSize;					// 분할 압축 크기 (bytes,  0 이면 분할 압축 안함)
	BOOL					forceZip64;					// 강제로 zip64 정보 저장
	BOOL					useDosTime2PasswordCheck;	// 암호 체크 데이타를 crc 대신 dostime 을 사용한다. (사용시 압축 속도 향상). 단 분할압축시 이 옵션은 무시됨
	BOOL					utf8Comment;				// utf8 comment 사용 여부
	LPCWSTR					sfxPathName;				// sfx 만들경우 sfx 파일경로명. NULL 이면 사용하지 않음.
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 만들기 인터페이스
//
struct IArkCompressor
{
	ARKMETHOD(void)					Release() PURE;												// 객체 해제

	ARKMETHOD(void)					Init() PURE;												// 초기화 (새로운 압축파일 생성 시작)
	ARKMETHOD(void)					SetEvent(IArkEvent* pEvent) PURE;							// 반드시 Init() 호출후 매번 호출해야 한다.
	ARKMETHOD(void)					SetOption(SArkCompressorOpt& opt, CHAR* password) PURE;		// CreateArchive() 호출전에만 호출하면 언제 호출해도 상관없고, 한번 호출하면 끝

	ARKMETHOD(BOOL)					SetArchiveFile(IArk* pArchive) PURE;						// 원본 파일 세팅 
	ARKMETHOD(BOOL)					AddFileItem(LPCWSTR	szSrcPathName, LPCWSTR szTargetPathName, BOOL overwrite, LPCWSTR szFileComment=NULL) PURE;

	ARKMETHOD(BOOL)					RenameItem(int index, LPCWSTR szPathName) PURE;				// SetArchiveFile() 로 지정한 파일의 이름을 바꾼다.
	ARKMETHOD(BOOL)					DeleteItem(int index) PURE;									// SetArchiveFile() 로 지정한 파일을 삭제한다.

	ARKMETHOD(int)					FindFileItemIndex2Add(LPCWSTR szTargetPathName) PURE;						// 기존 목록에 존재하는지 확인한다.
	ARKMETHOD(BOOL)					GetFileItemInfo(int index, INT64& fileSize, ARK_TIME_T& fileTime) PURE;		// 목록에 있는 파일의 정보 가져오기
	ARKMETHOD(INT64)				GetTotalFileSize2Archive() PURE;

	ARKMETHOD(BOOL)					CreateArchive(LPCWSTR szPathName, LPCWSTR szArchiveComment=NULL) PURE;

	ARKMETHOD(ARKERR)				GetLastError() const PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IArk, IArkCompressor 객체를 생성합니다. SDKVersion 파라메터는 ARK_LIBRARY_VERSION 을 넘기면 됩니다.
//

#ifdef _WIN32
extern "C" __declspec(dllexport) IArk*				CreateArk(UINT32 SDKVersion);
extern "C" IArk*									CreateArkLib(UINT32 SDKVersion);
extern "C" __declspec(dllexport) IArkCompressor*	CreateArkCompressor(UINT32 SDKVersion);
#endif



#endif // _ARK_H_

