//
//  CTaskSchedLib.cpp
//  
//	
//  Created by John Aliyetti on 9/5/2017.
//
//	Purpose: Provides the implementation for a simple function that uses COM to talk to and create a scheduled task with the task scheduler.
//

#include <CTaskSched.hpp>

#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "credui.lib")

//************************************************************************************************************
// function:  validateParams(const CTaskSchedParms & vParams)
//
// purpose: Validates the given CTaskSchedParms parameters struct.
//
// returns: true if the Params are valid or false if they are not valid
//************************************************************************************************************
bool validateParams(const CTaskSchedParms & vParams)
{
	return ((vParams.bstrTaskName != NULL && SysStringLen(vParams.bstrTaskName) > 0)
			&& (vParams.bstrExecutablePath != NULL && SysStringLen(vParams.bstrExecutablePath) > 0)
			&& (vParams.bstrId != NULL && SysStringLen(vParams.bstrId) > 0)
			&& (vParams.bstrStart != NULL && SysStringLen(vParams.bstrStart) > 0)
			&& (vParams.bstrEnd != NULL && SysStringLen(vParams.bstrEnd) > 0)
			&& (vParams.bstrName != NULL && SysStringLen(vParams.bstrName) > 0)
			&& (vParams.bstrPwd != NULL && SysStringLen(vParams.bstrPwd) > 0));
}

//************************************************************************************************************
// function:  schedualDailyTask(const CTaskSchedParms & vParams)
//
// purpose: Registers a daily task with the Task Scheduler with the given CTaskSchedParms parameters struct.
//
// returns: CTaskSchedResult tuple that specifies the HRESULT and a status string.
//************************************************************************************************************
CTaskSchedResult schedualDailyTask(const CTaskSchedParms & vParams)
{
	// validate the parameters first
	if (!validateParams(vParams))				
	{
		return make_tuple(E_INVALIDARG, "Invalid parameter(s)");
	}

    //  Create an instance of the Task Service.
    ITaskService *pService = NULL;
	HRESULT hr = CoCreateInstance( CLSID_TaskScheduler,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          IID_ITaskService,
                          (void**)&pService );
    if (FAILED(hr))
    {
        return make_tuple(hr, "Failed to create an instance of ITaskService");
    }
    
    //  Connect to the task service.
    hr = pService->Connect(_variant_t(), _variant_t(),
                           _variant_t(), _variant_t());
    if(FAILED(hr))
    {
        pService->Release();

		return make_tuple(hr, "ITaskService Connect failed");
    }
    
    //  Get the pointer to the root task folder that will hold the new task that is registered.
    ITaskFolder *pRootFolder = NULL;
    hr = pService->GetFolder(_bstr_t( L"\\"), &pRootFolder);
    
    if(FAILED(hr))
    {
        pService->Release();

		return make_tuple(hr, "Cannot get Root Folder pointer");
    }
    
    //  If the same task exists, remove it.
    pRootFolder->DeleteTask(vParams.bstrTaskName, 0);
    
    //  Create the task builder object to create the task.
    ITaskDefinition *pTask = NULL;
    hr = pService->NewTask(0, &pTask);
    
    pService->Release();  // COM clean up.  Pointer is no longer used.
    
    if (FAILED(hr))
    {
        pRootFolder->Release();

		return make_tuple(hr, "Failed to create a task definition");
    }
    
    //  Get the registration info for setting the identification.
    IRegistrationInfo *pRegInfo= NULL;
    hr = pTask->get_RegistrationInfo(&pRegInfo);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot get identification pointer");
    }
    
    hr = pRegInfo->put_Author( L"JAliyetti" );
    pRegInfo->Release();  // COM clean up.  Pointer is no longer used.
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot get identification info");
    }
    
    //  Get the trigger collection to insert the weekly trigger.
    ITriggerCollection *pTriggerCollection = NULL;
    hr = pTask->get_Triggers(&pTriggerCollection);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot get trigger collection");
    }
    
    ITrigger *pTrigger = NULL;
    hr = pTriggerCollection->Create( TASK_TRIGGER_DAILY, &pTrigger);
    pTriggerCollection->Release();
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot create trigger");
    }
    
    IDailyTrigger *pDailyTrigger = NULL;
    hr = pTrigger->QueryInterface(IID_IDailyTrigger, (void**) &pDailyTrigger);
    pTrigger->Release();
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "QueryInterface call for IDailyTrigger failed");
    }
    
    hr = pDailyTrigger->put_Id(vParams.bstrId);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot put trigger ID");
    }
    
    //  Set the time the trigger is started
    hr = pDailyTrigger->put_StartBoundary(vParams.bstrStart);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot put the start boundary");
    }
    
    //  Set the time when the trigger is ended
    hr = pDailyTrigger->put_EndBoundary(vParams.bstrEnd);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot put the end boundary");
    }
    
    //  ------------------------------------------------------
    //  Add an Action to the task. This task will execute vParams.bstrExecutablePath.
    IActionCollection *pActionCollection = NULL;
    
    //  Get the task action collection pointer.
    hr = pTask->get_Actions(&pActionCollection);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot get task collection pointer");
    }
    
    //  Create the action, specifying that it is an executable action.
    IAction *pAction = NULL;
    hr = pActionCollection->Create(TASK_ACTION_EXEC, &pAction);
    pActionCollection->Release();
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot create the action");
    }
    
    IExecAction *pExecAction = NULL;
    //  QI for the executable task pointer.
    hr = pAction->QueryInterface(IID_IExecAction, (void**) &pExecAction);
    pAction->Release();
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "QueryInterface call failed on IExecAction");
    }
    
    //  Set the path of the executable to vParams.bstrExecutablePath.
    hr = pExecAction->put_Path(vParams.bstrExecutablePath);

	pExecAction->Release();
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Cannot add path for executable action");
    }
    
    //  Register the task in the root folder.
    IRegisteredTask *pRegisteredTask = NULL;
    hr = pRootFolder->RegisterTaskDefinition(
                                             vParams.bstrTaskName,
                                             pTask,
                                             TASK_CREATE_OR_UPDATE,
                                             _variant_t(vParams.bstrName),
                                             _variant_t(vParams.bstrPwd),
                                             TASK_LOGON_PASSWORD,
                                             _variant_t(L""),
                                             &pRegisteredTask);
    
    if(FAILED(hr))
    {
        pRootFolder->Release();
        pTask->Release();

		return make_tuple(hr, "Error saving the Task");
    }
    
    
    //  Success!  now clean up...
    pRootFolder->Release();
    pTask->Release();
    pRegisteredTask->Release();
    
    return make_tuple(hr, "Success!");
}


// eof CTaskSchedLib.cpp