#include "stdafx.h"
#include "CppUnitTest.h"
#include <atlconv.h>
#include <tchar.h>

#include <CTaskSched.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH] = _T("aliyetti@aol.com");
TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH] = _T("ElvisR0x");

//TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH] = _T("username");				// fill your username and password in for proper authentication
//TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH] = _T("password");

namespace TaskSchedUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Calculator Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CALC.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-05T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-12-31T12:00:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the task

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(SUCCEEDED(get<0>(vResult)));
		}

	};
}