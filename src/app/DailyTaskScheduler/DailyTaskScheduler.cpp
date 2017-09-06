//
//  DailyTaskScheduler.cpp
//  
//	
//  Created by John Aliyetti on 9/5/2017.
//
//	Purpose: Provides a console application that shows how to call schedualDailyTask.
//

#include "stdafx.h"
#include <atlconv.h>

#include <CTaskSched.hpp>			// header file that defines CTaskSchedParms, CTaskSchedResult, and schedualDailyTask().


int main()
{
	CTaskSchedParms vParms;			// parameters passed in to schedualDailyTask()
	CTaskSchedResult vResult;		// results returned from schedualDailyTask()

	//  Initialize COM.
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(hr))
	{
		printf("CoInitializeEx failed\n");
		return -1;
	}

	//  Set general COM security levels.
	hr = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_PKT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		0,
		NULL);

	if (FAILED(hr))
	{
		CoUninitialize();
		printf("CoInitializeSecurity failed\n");
		return -2;
	}

	//  Acquire the user name and password.
	CREDUI_INFO cui;
	TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH] = _T("");
	TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH] = _T("");
	BOOL fSave;
	DWORD dwErr;

	cui.cbSize = sizeof(CREDUI_INFO);
	cui.hwndParent = NULL;
	//  Ensure that MessageText and CaptionText identify
	//  what credentials to use and which application requires them.
	cui.pszMessageText = TEXT("Account information for task registration:");
	cui.pszCaptionText = TEXT("Enter Account Information for Task Registration");
	cui.hbmBanner = NULL;
	fSave = FALSE;

	//  Create the UI asking for the credentials.
	dwErr = CredUIPromptForCredentials(
		&cui,                             //  CREDUI_INFO structure
		TEXT(""),                         //  Target for credentials
		NULL,                             //  Reserved
		0,                                //  Reason
		pszName,                          //  User name
		CREDUI_MAX_USERNAME_LENGTH,       //  Max number for user name
		pszPwd,                           //  Password
		CREDUI_MAX_PASSWORD_LENGTH,       //  Max number for password
		&fSave,                           //  State of save check box
		CREDUI_FLAGS_GENERIC_CREDENTIALS |  //  Flags
		CREDUI_FLAGS_ALWAYS_SHOW_UI |
		CREDUI_FLAGS_DO_NOT_PERSIST);

	if (dwErr)
	{
		printf("authentication failed\n");
		return -3;
	}

	// allocate and set the parameters
	vParms.bstrTaskName = SysAllocString(L"Daily Calculator Task");
	vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CALC.EXE");
	vParms.bstrId = SysAllocString(L"Trigger1");
	vParms.bstrStart = SysAllocString(L"2017-01-05T12:00:00");
	vParms.bstrEnd = SysAllocString(L"2017-12-31T12:00:00");
	vParms.bstrName = SysAllocString(T2OLE(pszName));
	vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

	vResult = schedualDailyTask(vParms);								// attempt to register the task

	printf("%s : %d\n", get<1>(vResult), get<0>(vResult));				// print the result string and code to the console

	// free the parameters
	SysFreeString(vParms.bstrTaskName);
	SysFreeString(vParms.bstrExecutablePath);
	SysFreeString(vParms.bstrId);
	SysFreeString(vParms.bstrStart);
	SysFreeString(vParms.bstrEnd);
	SysFreeString(vParms.bstrName);
	SysFreeString(vParms.bstrPwd);

	CoUninitialize();
	
	return FAILED(get<0>(vResult));
}

