#include <stdio.h>
#include <windows.h>
#include <CommCtrl.h>
#include <time.h>

#include "pupils.h"

const char g_szClassName[] = "Windows";

#define ID_LABEL 131
#define ID_LB    132

enum {
    STATIC_ID = 1,
    BUTTON_ID1,
    BUTTON_ID2,
    BTN_DEL_ID,
    EDIT_ID,
    LIST_ID,
};

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Test",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 360, 260,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hButtonReset, hButtonRandom, hEditName, hEditSurname, hEditForm, hEditNumber, hEditScore, hEditBirthdate,
            hLabelName,  hLabelSurname, hLabelForm, hLabelNumber, hLabelScore, hLabelBirthdate;
	HINSTANCE hInstance = GetModuleHandle(NULL);
    switch(msg)
    {
		case WM_CREATE:
        {
            hButtonReset = CreateWindowEx(0,
                                          WC_BUTTON,
                                          "Reset",
                                          WS_CHILD | WS_VISIBLE  | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                          240, 20, 80, 60,
                                          hwnd, (HMENU)BUTTON_ID1, hInst, NULL);
            hButtonRandom = CreateWindowEx(0,
                                          WC_BUTTON,
                                          "Random",
                                          WS_CHILD | WS_VISIBLE  | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                          240, 100, 80, 60,
                                          hwnd, (HMENU)BUTTON_ID2, hInst, NULL);
            hEditName = CreateWindowEx(0,
                                    WC_EDIT,
                                    "Name",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 20, 120, 25,
                                    hwnd, (HMENU)EDIT_ID, hInst, NULL);
            hLabelName = CreateWindowEx(0,
                                    "STATIC",
                                    "Name:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 20, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditSurname = CreateWindowEx(0,
                                    WC_EDIT,
                                    "Surname",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 50, 120, 25,
                                    hwnd, (HMENU)EDIT_ID, hInst, NULL);
            hLabelSurname = CreateWindowEx(0,
                                    "STATIC",
                                    "Surname:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 50, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditBirthdate = CreateWindowEx(0,
                                    WC_EDIT,
                                    "XXXX-XX-XX",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 80, 120, 25,
                                    hwnd, (HMENU)EDIT_ID, hInst, NULL);
            hLabelBirthdate = CreateWindowEx(0,
                                    "STATIC",
                                    "Birthdate:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 80, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditForm = CreateWindowEx(0,
                                    WC_EDIT,
                                    "Form",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 110, 120, 25,
                                    hwnd, (HMENU)EDIT_ID, hInst, NULL);
            hLabelForm = CreateWindowEx(0,
                                    "STATIC",
                                    "Form:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 110, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditNumber = CreateWindowEx(0,
                                    WC_EDIT,
                                    "Number",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 140, 120, 25,
                                    hwnd, (HMENU)EDIT_ID, hInst, NULL);
            hLabelNumber = CreateWindowEx(0,
                                    "STATIC",
                                    "Number:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 140, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditScore = CreateWindowEx(0,
                                    WC_EDIT,
                                    "Score",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 170, 120, 25,
                                    hwnd, (HMENU)EDIT_ID, hInst, NULL);
            hLabelScore = CreateWindowEx(0,
                                    "STATIC",
                                    "Score:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 170, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
        }
		break;
		case WM_COMMAND:
		{
		    switch(LOWORD(wParam))
		    {
                case BUTTON_ID1:
                {
                    SetWindowText(hEditName, TEXT("Ivan"));
                    SetWindowText(hEditSurname, TEXT("Ivanov"));
                    SetWindowText(hEditBirthdate, TEXT("2000-01-01"));
                    SetWindowText(hEditForm, TEXT("11-A"));
                    SetWindowText(hEditNumber, TEXT("1"));
                    SetWindowText(hEditScore, TEXT("12.0"));
                    break;
                }
                case BUTTON_ID2:
                {
                    srand(time(NULL));
                    pupil_t pupil = pupil_new();
                    pupil_randPupil(pupil);
                    char number[WORD_LENGTH];
                    sprintf(number, "%i", pupil_getNumber(pupil) );
                    char score[WORD_LENGTH];
                    sprintf(score, "%.2f", pupil_getScore(pupil));
                    SetWindowText(hEditName, TEXT(pupil_getName(pupil)));
                    SetWindowText(hEditSurname, TEXT(pupil_getSurname(pupil)));
                    SetWindowText(hEditBirthdate, TEXT(pupil_getBirthdate(pupil)));
                    SetWindowText(hEditForm, TEXT(pupil_getForm(pupil)));
                    SetWindowText(hEditNumber, TEXT(number));
                    SetWindowText(hEditScore, TEXT(score));
                }
		    }

		}
		break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

