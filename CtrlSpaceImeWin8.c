/************************************************************************/
/* @Author: starvii                                                                     */
/************************************************************************/
#include <windows.h>


HINSTANCE   m_hInstance = NULL;
HHOOK       m_hHook = NULL;


/************************************************************************/
/* ģ�� ctrl + shift �������л�����                                      */
/************************************************************************/
VOID sendCtrlShift()
{
	/* ctrl shift ������ */
	keybd_event(VK_CONTROL, (BYTE)0, 0, 0);
	keybd_event(VK_SHIFT, (BYTE)0, 0, 0);

	/* ctrl shift ���ͷ� */
	keybd_event(VK_SHIFT, (BYTE)0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);

	/* �ָ� ctrl ������״̬ */
	keybd_event(VK_CONTROL, (BYTE)0, 0, 0);
}

/************************************************************************/
/* ȫ�ּ��̹��ӻص�����                                                  */
/************************************************************************/
LRESULT CALLBACK KeyBoardProc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam)
{
	KBDLLHOOKSTRUCT *tag = NULL;

	if (nCode == HC_ACTION)
	{

		tag = (KBDLLHOOKSTRUCT *)lParam;

		/* ���� ctrl + space �����¼� */
		if (WM_KEYDOWN == wParam)
		{
			if (GetKeyState(VK_CONTROL) < 0 && tag->vkCode == VK_SPACE)
			{
				sendCtrlShift();
				return TRUE;
			}
		}

		/* ���� ctrl + space ̧���¼������л��������� */
		/* Win8֮ǰ���뷨�л����ɰ������´����ģ���win8�ɰ���̧�𴥷� */
		/* ���������ԣ����ַ�����Ӧ�ٶȽ��������ܵ�����ʱ�޷��л����뷨 */

		/*
		if (WM_KEYUP == wParam || WM_SYSKEYUP == wParam)
		{
		if (GetKeyState(VK_CONTROL) < 0 && tag->vkCode == VK_SPACE)
		{
		sendCtrlShift();
		return TRUE;
		}
		}
		*/

	}

	return CallNextHookEx(m_hHook, nCode, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	m_hInstance = (HINSTANCE)hInstance;

	/* ��װȫ�ּ��̹��� */
	m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyBoardProc, m_hInstance, 0);

	if (NULL == m_hHook)
	{
		MessageBox(NULL, "�޷�����ȫ�ּ��̹��ӣ�", "����", MB_OK & MB_ICONERROR);
		return -1;
	}

	/* ������Ϣѭ������֤ȫ�ּ��̹�����Ч */
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

	return 0;
}