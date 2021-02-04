//Pre-code user set-up:
bool AntiDebugB = true;
bool AntiDumpB = true;
bool TracesB = false;
bool BSODB = false;
bool KillTasksB = true;
bool NativeDebuggerProtection = true; //should be toggled off if you are debugging it using VS

#define _CRT_SECURE_NO_DEPRECATE //for fopen


#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <direct.h>

using namespace std;
// version: 0.1
// Made by lhaasper 
// github.com/lhaasper


void Protect()
{
	std::thread anti(Protecion);
}



void detect(std::string msg)
{
	if (TracesB) 
	{
		std::ofstream Trace01;
		Trace01.open("C:\\Program Files\\Win32Log.txt");
		Trace01 << "windows";
		Trace01.close();
	}
	std::ofstream outfile("Error.txt");
	outfile << "Detected: " + msg << std::endl;
	outfile.close();
	exit(1337);
}



bool isProcessRunning(const wchar_t* processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry)) {


			if (!_wcsicmp(entry.szExeFile, processName))
				exists = true;
		}

	CloseHandle(snapshot);
	return exists;
}

void exedetect()
{
	

		if (isProcessRunning((L"KsDumperClient.exe")))
		{
			detect("KsDumper");
		}
		else if (isProcessRunning((L"HTTPDebuggerUI.exe")))
		{
			detect("HttpDebuggerPro");
		}
		else if (isProcessRunning((L"HTTPDebuggerSvc.exe")))
		{
			detect("HttpDebuggerPro - Service");
		}
		else if (isProcessRunning((L"FolderChangesView.exe")))
		{
			detect("FolderChangesView");
		}
		else if (isProcessRunning((L"ProcessHacker.exe")))
		{
			detect("Process Hacker");
		}
		else if (isProcessRunning((L"procmon.exe")))
		{
			detect("Process Monitor");
		}
		else if (isProcessRunning((L"idaq.exe")))
		{
			detect("IDA");
		}
		else if (isProcessRunning((L"idaq64.exe")))
		{
			detect("IDA");
		}
		else if (isProcessRunning((L"Wireshark.exe")))
		{
			detect("Wireshark");
		}
		else if (isProcessRunning((L"Fiddler.exe")))
		{
			detect("Fiddler");
		}
		else if (isProcessRunning((L"Xenos64.exe")))
		{
			detect("Xenos");
		}
		else if (isProcessRunning((L"Cheat Engine.exe")))
		{
			detect("Cheat Engine");
		}
		else if (isProcessRunning((L"HTTP Debugger Windows Service (32 bit).exe")))
		{
			detect("HTTP Debugger - Service (2)");
		}
		else if (isProcessRunning((L"KsDumper.exe")))
		{
			detect("KSDumper");
		}
		else if (isProcessRunning((L"x64dbg.exe")))
		{
			detect("x64dbg");
		}

    
}


void KillDebuggers()
{
	
	system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq wireshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq rawshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq charles*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq ida*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("sc stop KProcessHacker3 >nul 2>&1");
	system("sc stop KProcessHacker2 >nul 2>&1");
	system("sc stop KProcessHacker1 >nul 2>&1");
	system("sc stop wireshark >nul 2>&1");
	system("sc stop npf >nul 2>&1");
}

void DetectNativeDebugger() 
{
	if (IsDebuggerPresent()) 
	{
		detect("Native debugger (IsDebuggerPresent returned true)");
	}
}

void AntiDump() {
	
}





void Protecion()
{
	while (true)
	{
		FILE* file;
		if (file = fopen("C:\\Program Files\\Win32Log.txt", "r")) {
			fclose(file);
			//trace exists (user is banned)
			detect("User is banned (7)");
		}

		if (AntiDebugB) 
		{
			exedetect();
		}
		else if (AntiDumpB)
		{
			//todo
		}
		else if (KillTasksB) 
		{
			KillDebuggers();
		}
		else if (NativeDebuggerProtection)
		{
			DetectNativeDebugger();
		}
	}
}
