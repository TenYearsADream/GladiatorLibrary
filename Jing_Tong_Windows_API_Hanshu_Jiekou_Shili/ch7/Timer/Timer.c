/* ************************************
*����ͨWindows API�� 
* ʾ������
* Timer.c
* 6.5.5  ��ʾʹ�ÿɵȴ���ʱ��
**************************************/
/* Ԥ���붨�� *Windows 2000*��*/
#define _WIN32_WINNT 0x0500
/* ͷ�ļ���*/
#include <windows.h>
#include <stdio.h>
/* �������塡*/
#define ONE_SECOND 10000000			// ��
/* ���Ͷ��塡*/
// TimerAPCProc ����
typedef struct _APC_PROC_ARG {
	TCHAR *szText;
	DWORD dwValue;
} APC_PROC_ARG;

/*************************************
* VOID CALLBACK TimerAPCProc(
*				LPVOID lpArg,
*				DWORD dwTimerLowValue,
*				DWORD dwTimerHighValue )
* ����	��ʾ��ʱ����ʹ��
*
* ����	δʹ��
**************************************/
VOID CALLBACK TimerAPCProc(
						   LPVOID lpArg,
						   DWORD dwTimerLowValue,
						   DWORD dwTimerHighValue )

{
	APC_PROC_ARG *pApcData = (APC_PROC_ARG *)lpArg;
	// ��ʾ��Ϣ
	printf( "Message: %s\nValue: %d\n\n", pApcData->szText,
		pApcData->dwValue);
	MessageBeep(MB_OK);
}

/*************************************
* void main( void ) 
* ����	��ʾ��ʱ����ʹ��
*
* ����	δʹ��
**************************************/
void main( void ) 
{
	HANDLE          hTimer;
	BOOL            bSuccess;
	INT64			qwDueTime;
	LARGE_INTEGER   liDueTime;
	APC_PROC_ARG    ApcData;

	ApcData.szText = "Message to apc proc.";
	ApcData.dwValue = 1;
	hTimer = CreateWaitableTimer(
		NULL,                   // Ĭ�ϰ�ȫ����
		FALSE,                  // �Զ�����
		"MyTimer" );			// ����
	if ( !hTimer ) 
	{
		printf("CreateWaitableTimer failed with Error %d.", 
			GetLastError() );
		return;
	} 
	else 
	{
		__try 
		{
			// ����
			qwDueTime = -5 * ONE_SECOND;
			// ת��Ϊ LARGE_INTEGER ���ݽṹ
			liDueTime.LowPart  = (DWORD) ( qwDueTime & 0xFFFFFFFF );
			liDueTime.HighPart = (LONG)  ( qwDueTime >> 32 );

			bSuccess = SetWaitableTimer(
				hTimer,           // ��ʱ�����
				&liDueTime,       // �ӳ�ʱ�䣬��һ����λ��ʱ��
				2000,             // ��ʱ�������ÿ2����λһ��
				TimerAPCProc,     // ��λʱ�������õ�����
				&ApcData,         // ���̲���
				FALSE );          // �����ù���ϵͳ
			// �ж��Ƿ񴴽��ɹ�
			if ( bSuccess ) 
			{
				for ( ; ApcData.dwValue <= 4; ApcData.dwValue ++ ) 
				{
					// �ڶ�������������Ϊ TRUE����ʾ����ʱ�����APC������ʱ����
					SleepEx(
						INFINITE,     // ���޵ȴ�
						TRUE );
					// ÿ����һ�Σ�dwValueֵ������
				}
			} 
			else 
			{
				printf( "SetWaitableTimer failed with Error %d.",
					GetLastError() );
			}
		} 
		__finally 
		{
			CloseHandle( hTimer );
		}
	}
}