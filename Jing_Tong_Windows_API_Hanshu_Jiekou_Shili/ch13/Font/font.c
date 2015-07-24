/* ************************************
*����ͨWindows API��
* ʾ������
* font.c
* 13.4.6 ��������
**************************************/
/* ͷ�ļ� */
#include <Windows.h>
#include <stdio.h>
/* �������� */
BOOL CALLBACK EnumFamCallBack(LPLOGFONT , LPNEWTEXTMETRIC , DWORD , LPVOID ) ;
DWORD ListFont();
// main
int main()
{
	// ����DC
	ListFont(NULL);
}
/*************************************
* DWORD ListFont(HWND hwnd)  
* ����	�о�ָ�����ڵ�DC�������е�����
**************************************/
DWORD ListFont(HWND hwnd)
{
	// ���DC
	HDC hdc = GetDC(hwnd);
    // ���ڼ���
	int aFontCount[] = { 0, 0, 0 }; 
	// ����EnumFontFamilies����ʼ�о٣�
	
    EnumFontFamilies(hdc, (
		LPCTSTR) NULL, // �о���������
        (FONTENUMPROC) EnumFamCallBack,// �ص�����ΪEnumFamCallBack
		(LPARAM) aFontCount); //���ݸ�EnumFamCallBack�Ĳ���

	// ��ʾͳ����Ϣ
	printf("Number of raster fonts: %d\n",aFontCount[0]);
	printf("Number of vector fonts: %d\n",aFontCount[1]);
	printf("Number of TrueType fonts: %d\n",aFontCount[2]);
	// ����
	return 0;
}
 
/*************************************
* EnumFamCallBack
* ����	�����оٻص�������
*			ÿ�о�һ������ᱻ����һ��
* ����	lplf�������LOGFONT�ṹ
*			lpntm���ַ��ĳ߶�����
*			FontType����������
*			lParam��ͨ��EnumFontFamilies������������Ĳ������������ڼ���
**************************************/
BOOL CALLBACK EnumFamCallBack(
							  LPLOGFONT lplf, 
							  LPNEWTEXTMETRIC lpntm, 
							  DWORD FontType, 
							  LPVOID aFontCount) 
{ 
	// ��ò���
    PINT aiFontCount = (PINT) aFontCount; 
	// �ж��������ͣ����������Ϣ�����������ͽ��м���
    if (FontType & RASTER_FONTTYPE) 
	{
		printf(" RASTER TYPE \t");
        aiFontCount[0]++; 
	}
    else if (FontType & TRUETYPE_FONTTYPE)
	{
		printf(" TRUETYPE \t");
        aiFontCount[2]++;
	}
    else 
	{
		printf(" VECTOR TYPE \t");
        aiFontCount[1]++; 
	}
	// ��ʾ������Ϣ
	printf("%s\tItalic = %d\n",lplf->lfFaceName,lplf->lfItalic);
    // ����
	if (aiFontCount[0] || aiFontCount[1] || aiFontCount[2]) 
        return TRUE; 
    else 
        return FALSE; 
} 