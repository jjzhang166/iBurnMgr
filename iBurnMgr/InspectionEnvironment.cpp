/*********************************************************************************************************
* InspectionEnvironment.cpp
* Note: iBurnMgr InspectionEnvironment
* E-mail:<forcemz@outlook.com>
* Date: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "InspectionEnvironment.h"
#include "APIController.h"
#include <PathCch.h>
#include <string>

WCHAR szLog[100] = {0};


////lParam HWND
DWORD WINAPI  InspectionEnvironmentThread(LPVOID lParam)
{
	HWND hWnd = static_cast<HWND>(lParam);
	WCHAR szPath[PATHCCH_MAX_CCH] = { 0 };
	wcscpy_s(szLog, 100, L"Inspection Environment Status");
	std::wstring _7z,bcd;
	GetModuleFileNameW(GetModuleHandle(nullptr), szPath, PATHCCH_MAX_CCH);
	_7z = szPath;
	bcd = szPath;
	std::string::size_type npos = _7z.find_last_of(L"\\");
	_7z = _7z.substr(0, npos);
	npos = _7z.find_last_of(L"\\");
	_7z = _7z.substr(0, npos);
	bcd = _7z + LR"(\utility\BCDBoot\bootsect.exe)";
	_7z = _7z + LR"(\utility\7z\7z.exe)";
	if (!_waccess_s(_7z.c_str(), 0) == 0){
		wcscat_s(szLog,L"\n7z Not Found!");
	}
	else{
		wcscat_s(szLog, L"\nFound 7z");
	}
	if (!_waccess_s(bcd.c_str(), 0) == 0)
	{
		wcscat_s(szLog, L"\nBCDBoot Not Found !");
	}
	else{
		wcscat_s(szLog, L"\nFound BCDBoot");
	}
	Sleep(1500);	
	PostMessage(hWnd, Metro::METRO_MULTITHREAD_MSG, MET_INSPECTIONEC, LPARAM(szLog));
	return 0;
}
