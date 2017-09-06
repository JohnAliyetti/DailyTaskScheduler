//
//  CTaskSched.hpp
//  
//
//  Created by John Aliyetti on 9/2/17.
//
//

#ifndef CTaskSched_hpp
#define CTaskSched_hpp

#define _WIN32_DCOM

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <comdef.h>
#include <wincred.h>
#include <taskschd.h>
#include <tuple>

using namespace std;


typedef struct tagTaskSchedParms					// parameters to be passed into schedualDailyTask() must be non-empty
{
    BSTR bstrTaskName;                              // task name
    BSTR bstrExecutablePath;                        // fully qualified executable path
    BSTR bstrId;                                    // string id
	BSTR bstrStart;                                 // start boundary - format should be YYYY-MM-DDTHH:MM:SS(+-)(timezone).
	BSTR bstrEnd;                                   // end boundary - ""
    BSTR bstrName;                                  // user name
    BSTR bstrPwd;                                   // user password
} CTaskSchedParms;

typedef tuple<HRESULT, const char *> CTaskSchedResult;       // result tuple for schedualDailyTask()

__declspec(dllimport) CTaskSchedResult schedualDailyTask(const CTaskSchedParms& vParams);              // creates a daily task with the given parameter struct

#endif /* CTaskSched_hpp */
