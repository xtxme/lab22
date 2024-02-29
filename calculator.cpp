#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND , UINT ,WPARAM ,LPARAM);
char text1[20];
char text2[20];
HWND textfield,textbox1,textbox2,button;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
			textfield = CreateWindow("STATIC","   Please input two numbers",WS_VISIBLE|WS_CHILD|WS_BORDER,20,20,200,20,hwnd,NULL,NULL,NULL);
			textbox1 = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,50,50,140,20,hwnd,NULL,NULL,NULL);
			textbox2 = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,50,80,140,20,hwnd,NULL,NULL,NULL);
			button = CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD|WS_BORDER,50,120,30,20,hwnd,(HMENU) 1,NULL,NULL);
			button = CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD|WS_BORDER,85,120,30,20,hwnd,(HMENU) 2,NULL,NULL);
			button = CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD|WS_BORDER,125,120,30,20,hwnd,(HMENU) 3,NULL,NULL);
			button = CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD|WS_BORDER,160,120,30,20,hwnd,(HMENU) 4,NULL,NULL);
			break;

			case WM_COMMAND: 
				if(LOWORD(wParam)!=0){
					int gwtstat1 = 0,gwtstat2 = 0;
					gwtstat1 = GetWindowText(textbox1,&text1[0],20);
					gwtstat2 = GetWindowText(textbox2,&text2[0],20);
				}
				if(LOWORD(wParam)==1){
					float re=atof(text1)+atof(text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				if(LOWORD(wParam)==2){
					float re=atof(text1)-atof(text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				if(LOWORD(wParam)==3){
					float re=atof(text1)*atof(text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				if(LOWORD(wParam)==4){
					float re=atof(text1)/atof(text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				break;	

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(14);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
