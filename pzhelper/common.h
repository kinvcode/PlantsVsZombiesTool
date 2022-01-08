#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <atlstr.h>

void isInDungeon(CpzhelperDlg* object);

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
DWORD WINAPI ThreadProc(LPVOID lpParameter)
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
		}
		Sleep(1500);
	}
	return 0;
}

// �޸�����
BOOL sunUpdate(CpzhelperDlg* object,int number)
{
	DWORD addr, value;
	addr = object->m_base_address;
	readMemery(object->m_game_handle, addr + 0x2A9EC0, value);
	readMemery(object->m_game_handle, value + 0x768, value);
	return WriteProcessMemory(object->m_game_handle, (LPVOID)(value+0x5560), &number, 4, NULL);
}

// ����Ƿ��ڹؿ�֮��
void isInDungeon(CpzhelperDlg* object)
{
	DWORD addr, value;
	addr = object->m_base_address;
	readMemery(object->m_game_handle, addr + 0x2A9EC0, value);
	readMemery(object->m_game_handle, value + 0x768, value);
	if (value != 0)
	{
		// ������Ϸ�е�״̬
		object->m_in_dungeon = true;
		// ��������
		if (object->m_sun_locked) 
		{
			CString numeric;
			object->m_sun_number.GetWindowTextW(numeric);
			int number = _ttoi(numeric);
			if (number > 0 && number <= 999999)
			{
				WriteProcessMemory(object->m_game_handle, (LPVOID)(value + 0x5560), &number, 4, NULL);
			}
		}
	}
}