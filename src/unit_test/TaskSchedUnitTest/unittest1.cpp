#include "stdafx.h"
#include "CppUnitTest.h"
#include <atlconv.h>
#include <tchar.h>

#include <CTaskSched.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH] = _T("username");				// fill your username and password in for proper authentication
TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH] = _T("password");

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

			vResult = schedualDailyTask(vParms);								// attempt to register the calculator task

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(SUCCEEDED(get<0>(vResult)));
		}

		TEST_METHOD(TestMethod2)
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Charmap Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CHARMAP.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-01-02T12:00:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the charmap task

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(SUCCEEDED(get<0>(vResult)));
		}

		TEST_METHOD(TestMethod3)
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Control Panel Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CONTROL.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-06-30T16:30:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the control panel task

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(SUCCEEDED(get<0>(vResult)));
		}

		TEST_METHOD(TestMethod4)
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Control Panel Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CONTROL.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-06-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-01-30T16:30:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the control panel task (it should fail because start is after end)

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(FAILED(get<0>(vResult)));
		}

		TEST_METHOD(TestMethod5)
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Charmap Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CHARMAP.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-02-31T12:00:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the charmap task (it should fail because end date is invalid)

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(FAILED(get<0>(vResult)));
		}	

		TEST_METHOD(TestMethod6)
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Calculator Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CALC.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-13-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-02-28T12:00:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the charmap task (it should fail because start date is invalid)

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(FAILED(get<0>(vResult)));
		}
	};
}