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

// ���ݽ���������ȡ����id
int getProcessIdByName(CString target)
{

	HANDLE process_handle; // ���վ��
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

// ���ڴ�
BOOL readMemery(HANDLE handle, DWORD address, DWORD& value)
{
	return ReadProcessMemory(handle, (LPCVOID)address, (LPVOID)&value, 4, NULL);
}

// �����Ϸ����״̬�߳�
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
				// ��Ŀ����̾��
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
				if (!hProcess)
				{
					continue;
				}

				object->m_game_pid = pid;
				object->m_status_int = 1;
				object->m_game_status.SetWindowTextW(L"������");
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
			object->m_game_status.SetWindowTextW(L"δ����");
			object->m_in_dungeon = FALSE;
		}
		Sleep(1500);
	}
	return 0;
}

// �޸�����
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

// ����Ƿ��ڹؿ�֮��
void isInDungeon(CpzhelperDlg* object)
{
	DWORD moduleBase, value;
	moduleBase = object->m_base_address;
	readMemery(object->m_game_handle, moduleBase + 0x3794F8, value);
	readMemery(object->m_game_handle, value + 0x868, value);
	if (value != 0)
	{
		DWORD commonAddress = value, coolAddress = value;
		// ������Ϸ�е�״̬
		object->m_in_dungeon = TRUE;
		object->m_dungeon_status.SetWindowTextW(L"��");
	}
	else
	{
		object->m_in_dungeon = FALSE;
		object->m_dungeon_status.SetWindowTextW(L"��");
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

			// ��������
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
			// ����ȴ
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

void rapidFire(CpzhelperDlg* object,bool on)
{
	int call_addr = 0x709590;
	int origin_addr = 0x4838BA;
	if (on) {
		// �޸ı���
		byte code[8] = {0x83,0x43,0x58,0xFC,0x8B,0x43,0x58,0xC3};
		WriteProcessMemory(object->m_game_handle, (LPVOID)(call_addr), &code, 8, NULL);
	
		// ��ת���޸ı���
		byte jmp_code[6] = {0xE8,0xD1,0x5C,0x28,0x00,0x90};
		WriteProcessMemory(object->m_game_handle, (LPVOID)(origin_addr), &jmp_code, 6, NULL);
	}
	else {
		// ��ԭ����
		byte code[6] = {0xFF,0x4B,0x58,0x8B,0x43,0x58};
		WriteProcessMemory(object->m_game_handle, (LPVOID)(origin_addr), &code, 6, NULL);
	}
}

// ����Ͷ��
void superFire(CpzhelperDlg* object, bool on)
{
	// ����Ͷ�ֵĵ���
	//int addr = 0x488FF4 + 6;
	//if (on) {
	//	// �޸ı���
	//	byte speed = 2;
	//	WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &speed, 1, NULL);
	//}
	//else {
	//	// ��ԭ����
	//	byte speed = 1;
	//	WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &speed, 1, NULL);
	//}

	// �ӵ�����
	int addr = 0x488CD9;
	if (on) {
		// �޸ĵ���
		byte code[6] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &code, 6, NULL);
	}
	else {
		// ��ԭ����
		byte code[6] = { 0x0F,0x85,0x86,0xFE,0xFF,0xFF };
		WriteProcessMemory(object->m_game_handle, (LPVOID)(addr), &code, 6, NULL);
	}
}

// �Զ��ɼ�����
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