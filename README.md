# DailyTaskScheduler
a small C++ (Windows) application that uses COM to talk to and create a scheduled task with the task scheduler.

Author: John Aliyetti
Developed for: PhishMe

This solution contains 3 projects:

TaskSchedLib - dll project that contains the implementation that uses COM to talk to and create a scheduled task with the task scheduler.
               The main function in this project is schedualDailyTask().
               
TaskSchedUnitTest - Unit Test project that contains several positive and negative unit test methods for testing TaskSchedLib.

DailyTaskScheduler - Console application project that shows how to call schedualDailyTask().


To start the development solution run DailyTaskSchedulerDev.bat in the root of the repository. 
It effectively launches the DailyTaskScheduler.sln solution file that contains all threes projects.

To build the solution select the appropriate configuration (Release/Debug) first.
Next you will want to update unittest1.cpp in the TaskSchedUnitTest project to provide your credentials 
with pszName and pszPwd (Windows/Domain user name and password) that will be used when running the unit test methods.
If you do not update pszName and pszPwd the first three unit test methods will fail due to invalid credentials.

The build order is:
                    TaskSchedLib
                    
                    Then either TaskSchedUnitTest or DailyTaskScheduler

					Microsoft Visual Studio Community 2017 



Developed with Microsoft Visual Studio 2017 (Community) Version 15.2 (26430.16)

Details:

Version 15.2 (26430.16) Release
VisualStudio.15.Release/15.2.0+26430.16
Microsoft .NET Framework
Version 4.7.02046

Installed Version: Community

Visual Basic 2017   00369-60000-00001-AA448
Microsoft Visual Basic 2017

Visual C# 2017   00369-60000-00001-AA448
Microsoft Visual C# 2017

Visual C++ 2017   00369-60000-00001-AA448
Microsoft Visual C++ 2017

Application Insights Tools for Visual Studio Package   8.6.00404.2
Application Insights Tools for Visual Studio

ASP.NET and Web Tools 2017   15.0.30503.0
ASP.NET and Web Tools 2017

Azure App Service Tools v3.0.0   15.0.30209.0
Azure App Service Tools v3.0.0

Common Azure Tools   1.9
Provides common services for use by Azure Mobile Services and Microsoft Azure Tools.

Cookiecutter   3.0.17114.1
Provides tools for finding, instantiating and customizing templates in cookiecutter format.

JavaScript Language Service   2.0
JavaScript Language Service

JavaScript Project System   2.0
JavaScript Project System

JavaScript UWP Project System   2.0
JavaScript UWP Project System

KofePackagePackage Extension   1.0
KofePackagePackage Visual Studio Extension Detailed Info

Microsoft Azure Tools   2.9
Microsoft Azure Tools for Microsoft Visual Studio 2017 - v2.9.50131.1

Microsoft MI-Based Debugger   1.0
Provides support for connecting Visual Studio to MI compatible debuggers

Microsoft Visual Studio VC Package   1.0
Microsoft Visual Studio VC Package

NuGet Package Manager   4.2.0
NuGet Package Manager in Visual Studio. For more information about NuGet, visit http://docs.nuget.org/.

Python   3.0.17114.1
Provides IntelliSense, projects, templates, debugging, interactive windows, and other support for Python developers.

Python - Django support   3.0.17114.1
Provides templates and integration for the Django web framework.

Python - IronPython support   3.0.17114.1
Provides templates and integration for IronPython-based projects.

Python - Profiling support   3.0.17114.1
Profiling support for Python projects.

TypeScript   2.2.2.0
TypeScript tools for Visual Studio

Visual C++ for Cross Platform Mobile Development (Android)   15.0.26228.00
Visual C++ for Cross Platform Mobile Development (Android)

Visual Studio tools for CMake   1.0
Visual Studio tools for CMake

Visual Studio Tools for Universal Windows Apps   15.0.26430.06
The Visual Studio Tools for Universal Windows apps allow you to build a single universal app experience 
that can reach every device running Windows 10: phone, tablet, PC, and more. 
It includes the Microsoft Windows 10 Software Development Kit.