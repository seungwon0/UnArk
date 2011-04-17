#include <stdio.h>

#include <string>

#include "include/ArkLib.h"

using namespace std;

CArkLib g_arkLib;

// http://read.pudn.com/downloads182/sourcecode/unix_linux/854401/Unicode2Utf8.cpp__.htm
std::string unicode2utf8(WCHAR* str)
{
	unsigned char u1, u2, u3, u4;
	std::string ret;
	WCHAR uc;

	while(*str)
	{
		uc = *str;
		if (uc < 0x80)
		{
			ret += (char)*str;
		}
		else if (uc < 0x800)
		{
			u2 = 0xC0 | uc >> 6;
			u1 = 0x80 | uc & 0x3F;
			ret+=u2;
			ret+=u1;
		}
		else if (uc < 0x10000)
		{
			u3 = 0xE0 | uc >> 12;
			u2 = 0x80 | uc >> 6 & 0x3F;
			u1 = 0x80 | uc & 0x3F;
			ret+=u3;
			ret+=u2;
			ret+=u1;
		}
		else if (uc < 0x200000)
		{
			u4 = 0xF0 | uc >> 18;
			u3 = 0x80 | uc >> 12 & 0x3F;
			u2 = 0x80 | uc >> 6 & 0x3F;
			u1 = 0x80 | uc & 0x3F;
			ret+=u4;
			ret+=u3;
			ret+=u2;
			ret+=u1;
		}
		str++;
	}

	return ret;
}

class CArkEvent : public IArkEvent
{
public :
	ARKMETHOD(void)	OnOpening(const SArkFileItem* pFileItem,
				  float progress, BOOL& bStop)
		{
		}

	ARKMETHOD(void) OnStartFile(const SArkFileItem* pFileItem,
				    BOOL& bStopCurrent, BOOL& bStopAll)
		{
			std::string name = unicode2utf8(pFileItem->fileNameW);
			printf("  %s\n", name.c_str());
		}

	ARKMETHOD(void)	OnProgressFile(const SArkProgressInfo* pProgressInfo,
				       BOOL& bStopCurrent, BOOL& bStopAll)
		{
		}

	ARKMETHOD(void)	OnCompleteFile(const SArkProgressInfo* pProgressInfo,
				       ARKERR nErr)
		{
		}

	ARKMETHOD(void)	OnError(ARKERR nErr, const SArkFileItem* pFileItem,
				BOOL bIsWarning, BOOL& bStopAll)
		{
		}

	ARKMETHOD(void)	OnMultiVolumeFileChanged(LPCWSTR szPathFileName)
		{
		}

	ARKMETHOD(void)	OnAskOverwrite(const SArkFileItem* pFileItem,
				       LPCWSTR szLocalPathName,
				       ARK_OVERWRITE_MODE& overwrite,
				       WCHAR pathName2Rename[ARK_MAX_PATH])
		{
		}
};

int main(int argc, char* argv[])
{
	if (argc != 2 && argc != 3) {
		puts("UnArk - Archive Extractor");
		puts("Usage: unark <ARCHIVE> [DESTINATION]");
		puts("Copyright(C) 2011, Bandisoft.com");
		return 0;
	}

	if (g_arkLib.Create(ARK_DLL_FILE_NAME) != ARKERR_NOERR) {
		fputs("Failed to load ArkLibrary\n", stderr);
		return 1;
	}

	CArkEvent evt;

	g_arkLib.SetGlobalOpt(FALSE);
	g_arkLib.SetEvent(&evt);

	if (g_arkLib.Open(argv[1], NULL) == FALSE) {
		fprintf(stderr, "Cannot open file: %s\n", argv[1]);
		return 1;
	}

	const char *targetPath = ".";

	if (argc == 3)
		targetPath = argv[2];

	printf("Extracting '%s' to '%s'...\n", argv[1], targetPath);

	if (g_arkLib.ExtractAllTo(targetPath) == FALSE) {
		fprintf(stderr,
			"Error occurred: 0x%x\n", g_arkLib.GetLastError());
		return 1;
	}

	printf("Done.\n");

	return 0;
}
