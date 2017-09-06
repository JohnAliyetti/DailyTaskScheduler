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
		
		TEST_METHOD(TestPositive1)												// this tests normal positive usage
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

		TEST_METHOD(TestPositive2)												// this tests normal positive usage
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

		TEST_METHOD(TestPositive3)												// this tests normal positive usage
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

		TEST_METHOD(TestNegative1)												// this tests non-normal (negative) usage
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Control Panel Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CONTROL.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-06-01T12:00:00");			// start date is after the end date
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

		TEST_METHOD(TestNegative2)												// this tests non-normal (negative) usage
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Charmap Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CHARMAP.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-02-31T12:00:00");			// end date is invalid
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

		TEST_METHOD(TestNegative3)												// this tests non-normal (negative) usage
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Calculator Task");
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CALC.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-13-01T12:00:00");			// start date is invalid
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

		TEST_METHOD(TestEmptyParam1)											// this tests non-normal (negative) usage
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = NULL;											// this param will be NULL
			vParms.bstrExecutablePath = SysAllocString(L"\\SYSTEM32\\CALC.EXE");
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-02-28T12:00:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the charmap task (it should fail because a parameter is NULL)

			// vParms.bstrTaskName is NULL so it is not freed
			SysFreeString(vParms.bstrExecutablePath);
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(FAILED(get<0>(vResult)));
		}

		TEST_METHOD(TestEmptyParam2)											// this tests non-normal (negative) usage
		{
			CTaskSchedParms vParms;
			CTaskSchedResult vResult;

			// allocate and set the parameters
			vParms.bstrTaskName = SysAllocString(L"Daily Calculator Task");	
			vParms.bstrExecutablePath = SysAllocString(L"");					// this parameter is empty (zero length)
			vParms.bstrId = SysAllocString(L"Trigger1");
			vParms.bstrStart = SysAllocString(L"2017-01-01T12:00:00");
			vParms.bstrEnd = SysAllocString(L"2017-02-28T12:00:00");
			vParms.bstrName = SysAllocString(T2OLE(pszName));
			vParms.bstrPwd = SysAllocString(T2OLE(pszPwd));

			vResult = schedualDailyTask(vParms);								// attempt to register the charmap task (it should fail because a parameter is empty)

			SysFreeString(vParms.bstrTaskName);
			SysFreeString(vParms.bstrExecutablePath);							// free empty param
			SysFreeString(vParms.bstrId);
			SysFreeString(vParms.bstrStart);
			SysFreeString(vParms.bstrEnd);
			SysFreeString(vParms.bstrName);
			SysFreeString(vParms.bstrPwd);

			Assert::IsTrue(FAILED(get<0>(vResult)));
		}
	};
}