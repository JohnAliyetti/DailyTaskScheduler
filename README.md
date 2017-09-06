# DailyTaskScheduler
a small C++ (Windows) application that uses COM to talk to and create a scheduled task with the task scheduler.

# Author: John Aliyetti
# Developed for: PhishMe

# This solution contains 3 projects:

# TaskSchedLib - dll project that contains the implementation that uses COM to talk to and create a scheduled task with the task scheduler.
#                The main function in this project is schedualDailyTask().
               
# TaskSchedUnitTest - Unit Test project that contains several positive and negative unit test methods for testing TaskSchedLib.

# DailyTaskScheduler - Console application project that shows how to call schedualDailyTask().


# To start the development solution run DailyTaskSchedulerDev.bat in the root of the repository. 
# It effectively launches the DailyTaskScheduler.sln solution file that contains all threes projects.

# To build the solution select the appropriate configuration (Release/Debug) first.
# Next you will want to update unittest1.cpp in the TaskSchedUnitTest project to provide your credentials 
# with pszName and pszPwd (Windows/Domain user name and password) that will be used when running the unit test methods.

# The build order is:
#                     TaskSchedLib
                    
#                     Then either TaskSchedUnitTest or DailyTaskScheduler

