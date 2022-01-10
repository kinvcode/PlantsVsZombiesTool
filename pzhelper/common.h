#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <atlstr.h>

void isInDungeon(CpzhelperDlg* object);

char* wchar2char(WCHAR WStr[MAX_PATH])
{
	size_t len = wcslen(WStr) + 1;
	size_t converted = 0;
	char* CStr;
	CStr = (char*)malloc(len * sizeof(char));
	wcstombs_s(&converted, CStr, len, WStr, _TRUNCATE);
	return CStr;
}

// 根据进程名，获取进程id
int getProcessIdByName(CString target)
{

	HANDLE process_handle; // 快照句柄
	PROCESSENTRY32 process_info;
	process_info.dwSize = sizeof(PROCESSENTRY32);
	BOOL open_status;

	process_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	open_status = Process32First(process_handle, &process_info);

	while (open_status) {
		char* current = wchar2char(process_info.szExeFile);
		//CString current = CString(process_info.szExeFile);
		if (current == target) {
			return process_info.th32ProcessID;
			break;
		}

		open_status = Process32Next(process_handle, &process_info);
	}

	CloseHandle(process_handle);
	return 0;
}

// 读内存
BOOL readMemery(HANDLE handle, DWORD address, DWORD& value)
{
	return ReadProcessMemory(handle, (LPCVOID)address, (LPVOID)&value, 4, NULL);
}

// 检测游戏运行状态线程
DWORD WINAPI GameIsRuning(LPVOID lpParameter)
{
	CpzhelperDlg* object = (CpzhelperDlg*)lpParameter;

	CString game_name = L"PlantsVsZombies.exe";
	int pid;

	while (1)
	{
		if (pid = getProcessIdByName(game_name))
		{
			if (!object->m_status_int)
			{
				HANDLE hSnapshot = INVALID_HANDLE_VALUE;
				hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, pid);
				if (hSnapshot == INVALID_HANDLE_VALUE)
				{
					continue;
				}
				MODULEENTRY32 module_struct;
				module_struct.dwSize = sizeof(MODULEENTRY32);
				if (!Module32First(hSnapshot, &module_struct))
				{
					CloseHandle(hSnapshot);
					continue;
				}
				HANDLE hProcess;
				// 打开目标进程句柄
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
				if (!hProcess)
				{
					continue;
				}

				object->m_game_pid = pid;
				object->m_status_int = 1;
				object->m_game_status.SetWindowTextW(L"运行中");
				object->m_game_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
				object->m_game_handle = hProcess;
				object->m_base_address = (DWORD)module_struct.modBaseAddr;
				isInDungeon(object);
			}
			else {
				isInDungeon(object);
			}
		}
		else {
			object->m_game_pid = 0;
			object->m_status_int = 0;
			object->m_game_status.SetWindowTextW(L"未运行");
			object->m_in_dungeon = FALSE;
		}
		Sleep(1500);
	}
	return 0;
}

// 修改阳光
BOOL sunUpdate(CpzhelperDlg* object, int number)
{
	DWORD addr, value;
	addr = object->m_base_address;
	readMemery(object->m_game_handle, addr + 0x2A9EC0, value);
	readMemery(object->m_game_handle, value + 0x768, value);
	return WriteProcessMemory(object->m_game_handle, (LPVOID)(value + 0x5560), &number, 4, NULL);
}

// 检测是否在关卡之中
void isInDungeon(CpzhelperDlg* object)
{
	DWORD moduleBase, value;
	moduleBase = object->m_base_address;
	readMemery(object->m_game_handle, moduleBase + 0x2A9EC0, value);
	readMemery(object->m_game_handle, value + 0x768, value);
	if (value != 0)
	{
		DWORD commonAddress = value, coolAddress = value;
		// 更新游戏中的状态
		object->m_in_dungeon = TRUE;
		object->m_dungeon_status.SetWindowTextW(L"是");
	}
	else
	{
		object->m_in_dungeon = FALSE;
		object->m_dungeon_status.SetWindowTextW(L"否");
	}
}

DWORD WINAPI FastScan(LPVOID lpParameter)
{
	CpzhelperDlg* object = (CpzhelperDlg*)lpParameter;

	while (1)
	{
		if (object->m_in_dungeon == TRUE)
		{
			DWORD moduleBase, value;
			moduleBase = object->m_base_address;
			readMemery(object->m_game_handle, moduleBase + 0x2A9EC0, value);
			readMemery(object->m_game_handle, value + 0x768, value);
			DWORD commonAddress = value, coolAddress = value;

			// 锁定阳光
			if (object->m_sun_locked)
			{
				CString numeric;
				object->m_sun_number.GetWindowTextW(numeric);
				int number = _ttoi(numeric);
				if (number > 0 && number <= 999999)
				{
					WriteProcessMemory(object->m_game_handle, (LPVOID)(commonAddress + 0x5560), &number, 4, NULL);
				}
			}
			// 无冷却
			readMemery(object->m_game_handle, coolAddress + 0x144, coolAddress);
			if (object->m_plants_cool_down)
			{
				byte coolStatus = 1;
				coolAddress = coolAddress + 0x70;
				for (int i = 0; i < 5; i++)
				{
					WriteProcessMemory(object->m_game_handle, (LPVOID)(coolAddress + i * 0x50), &coolStatus, 1, NULL);
				}
			}
		}
		Sleep(500);
	}
	return 0;
}