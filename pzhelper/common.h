#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <atlstr.h>
#include <vector>

void isInDungeon(CpzhelperDlg* object);

std::vector<byte> operator+(std::vector<byte> a, std::vector<byte> b)
{
	for (unsigned int i = 0; i < b.size(); i++)
	{
		a.push_back(b[i]);
	}

	b.clear();

	return a;
}

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
	readMemery(object->m_game_handle, addr + 0x3794F8, value);
	readMemery(object->m_game_handle, value + 0x868, value);
	return WriteProcessMemory(object->m_game_handle, (LPVOID)(value + 0x5578), &number, 4, NULL);
}

BOOL goldUpdate(CpzhelperDlg* object, int number)
{
	DWORD addr, value;
	addr = object->m_base_address;
	readMemery(object->m_game_handle, addr + 0x3794F8, value);
	readMemery(object->m_game_handle, value + 0x950, value);
	return WriteProcessMemory(object->m_game_handle, (LPVOID)(value + 0x50), &number, 4, NULL);
}

// 检测是否在关卡之中
void isInDungeon(CpzhelperDlg* object)
{
	DWORD moduleBase, value;
	moduleBase = object->m_base_address;
	readMemery(object->m_game_handle, moduleBase + 0x3794F8, value);
	readMemery(object->m_game_handle, value + 0x868, value);
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
			readMemery(object->m_game_handle, moduleBase + 0x3794F8, value);
			readMemery(object->m_game_handle, value + 0x868, value);
			DWORD commonAddress = value, coolAddress;

			readMemery(object->m_game_handle, moduleBase + 0x3794F8, coolAddress);
			readMemery(object->m_game_handle, coolAddress + 0x868, coolAddress);
			readMemery(object->m_game_handle, coolAddress + 0x15C, coolAddress);

			// 锁定阳光
			if (object->m_sun_locked)
			{
				CString numeric;
				object->m_sun_number.GetWindowTextW(numeric);
				int number = _ttoi(numeric);
				if (number > 0 && number <= 999999)
				{
					WriteProcessMemory(object->m_game_handle, (LPVOID)(commonAddress + 0x5578), &number, 4, NULL);
				}
			}
			// 无冷却
			if (object->m_plants_cool_down)
			{
				byte coolStatus = 1;
				for (int i = 0; i < 10; i++)
				{
					WriteProcessMemory(object->m_game_handle, (LPVOID)(coolAddress + i * 0x50 + 0x28 + 0x24), &coolStatus, 1, NULL);
				}
			}
		}
		Sleep(100);
	}
	return 0;
}

void rapidFire(CpzhelperDlg* object, bool on)
{
	// 使用了空白地址
	int call_addr = 0x709590;
	int origin_addr = 0x4838BA;
	if (on) {
		// 修改倍速
		byte code[8] = { 0x83,0x43,0x58,0xFC,0x8B,0x43,0x58,0xC3 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(call_addr), &code, 8, NULL);

		// 跳转到修改倍速
		byte jmp_code[6] = { 0xE8,0xD1,0x5C,0x28,0x00,0x90 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(origin_addr), &jmp_code, 6, NULL);
	}
	else {
		// 还原倍速
		byte code[6] = { 0xFF,0x4B,0x58,0x8B,0x43,0x58 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(origin_addr), &code, 6, NULL);
	}
}

// 超级投手
void superFire(CpzhelperDlg* object, bool on)
{
	// 适用投手的叠加
	//int addr = 0x488FF4 + 6;
	//if (on) {
	//	// 修改倍速
	//	byte speed = 2;
	//	WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &speed, 1, NULL);
	//}
	//else {
	//	// 还原倍速
	//	byte speed = 1;
	//	WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &speed, 1, NULL);
	//}

	// 子弹叠加
	int addr = 0x488CD9;
	if (on) {
		// 修改叠加
		byte code[6] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &code, 6, NULL);
	}
	else {
		// 还原叠加
		byte code[6] = { 0x0F,0x85,0x86,0xFE,0xFF,0xFF };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &code, 6, NULL);
	}
}

// 自动采集阳光
void autoGatherSun(CpzhelperDlg* object, bool on)
{
	int addr = 0x44C5F1;
	if (on) {
		byte gather = 1;
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &gather, 1, NULL);
	}
	else {
		byte gather = 0;
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &gather, 1, NULL);
	}
}

// 僵尸秒杀
void skillZombies(CpzhelperDlg* object, bool on)
{
	int addr = 0x5608D5;
	if (on) {
		byte code[2] = { 0x90,0x90 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &code, 2, NULL);
	}
	else {
		byte code[2] = { 0x75,0xC };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &code, 2, NULL);
	}
}

// 后台运行

void backgroundRunning(CpzhelperDlg* object, bool on)
{
	int win_addr = 0x540C40;
	int background_addr = 0x42BCCA;
	if (on) {
		byte code[3] = { 0xC3, 0x90,0x90 };
		byte code2[2] = { 0xEB,0x37 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(win_addr), &code, 3, NULL);
		WriteProcessMemory(object->m_game_handle, (LPVOID)(background_addr), &code2, 2, NULL);
	}
	else {
		byte code[3] = { 0x8B, 0x40,0x1C };
		byte code2[2] = { 0x75,0x37 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(win_addr), &code, 3, NULL);
		WriteProcessMemory(object->m_game_handle, (LPVOID)(background_addr), &code2, 2, NULL);
	}
}

void changebullet(CpzhelperDlg* object, bool on, byte code)
{
	int empty_addr = 0x830000;
	int oringin_addr = 0x493604;
	if (on) {
		byte oringin_code[7] = { 0xE9,0xF7,0xC9,0x39,0x00,0x66,0x90 };
		byte inject_code[19] = { 0xC7,0x45,0x5C ,code ,0x00 ,0x00 ,0x00 ,0x8B ,0x45 ,0x5C ,0x56 ,0x8D ,0x34 ,0x40 ,0xE9 ,0xF8 ,0x35 ,0xC6 ,0xFF };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(oringin_addr), &oringin_code, 7, NULL);
		WriteProcessMemory(object->m_game_handle, (LPVOID)(empty_addr), &inject_code, 19, NULL);
	}
	else {
		byte oringin_code[7] = { 0x8B,0x45,0x5C,0x56,0x8D,0x34,0x40 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(oringin_addr), &oringin_code, 7, NULL);
	}
}