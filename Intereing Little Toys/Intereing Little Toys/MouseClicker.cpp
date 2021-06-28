#include<Windows.h>
int x=1;
int main(void) {
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) {
			while (true)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(100);
				if (GetAsyncKeyState(VK_ESCAPE))return 0;
				if (GetAsyncKeyState(VK_TAB))break;
			}
		}
	}
	return 0;
}
