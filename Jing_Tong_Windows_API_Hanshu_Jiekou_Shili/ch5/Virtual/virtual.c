/* ************************************
*����ͨWindows API�� 
* ʾ������
* virtual.c
* 5.4.2  ������ͷſɶ���д�������ڴ�ҳ��
**************************************/

/* ͷ�ļ���*/
#include <windows.h>
#include <stdio.h>

/*************************************
* int main(void)
* ����	��ʾ�����ڴ��ʹ��
*
* ����	δʹ��
**************************************/
int main(void)
{	
	SIZE_T sizeVirtual = 4000;		//��С
	LPVOID lpRound = (LPVOID)0x100000FF;	//��ַ
	MEMORY_BASIC_INFORMATION  mbi;	//�ڴ���Ϣ

	//�����ڴ棬ֱ�ӷ������ύ���ڴ�
	LPVOID lpAddress = VirtualAlloc(
		lpRound,sizeVirtual,
		MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE
		);
	if(lpAddress == NULL)
	{
		printf("VirtualAlloc error: %d\n",GetLastError());
		return 1;
	}
	printf("Alloc:MEM_COMMIT|MEM_RESERVE\n");
	//�������ݵ��ڴ���
	CopyMemory(lpAddress,"hello",lstrlen("hello"));
	printf("���䡢���Ƴɹ�����ַ��0x%.8x�����ݣ�%s\n",
		lpAddress,lpAddress);
	//��ȡ�ڴ���Ϣ����ӡ
	VirtualQuery(lpAddress,&mbi,sizeof(mbi));
	printf("ʹ��VirtualQuery��õ���Ϣ��\n"
		"BaseAddress:0x%.8x\tAllocationBase:0x%.8x\t"
		"AllocationProtect:0x%.8x\tRegionSize:%u\t"
		"State:0x%.8x\tProtect:0x%.8x\tType:0x%.8x\n",
		mbi.BaseAddress,mbi.AllocationBase,
		mbi.AllocationProtect,mbi.RegionSize,
		mbi.State,mbi.Protect,mbi.Type
		);

	////����ΪREAD-ONLY����
	//if(!VirtualProtect(lpAddress,0,PAGE_READONLY,NULL))
	//{
	//	printf("VirtualProtect error: %d",GetLastError());
	//	return 1;
	//}
	////����READ-ONLY����,�쳣
	//CopyMemory(lpAddress,"read only",lstrlen("read only"));
	//printf(lpAddress);
	////��ȡ�ڴ���Ϣ����ӡ
	//VirtualQuery(lpAddress,&mbi,sizeof(mbi));
	//printf("ʹ��VirtualQuery��õ���Ϣ��\n"
	//	"BaseAddress:0x%.8x\tAllocationBase:0x%.8x\t"
	//	"AllocationProtect:0x%.8x\tRegionSize:%d\t"
	//	"State:0x%.8x\tProtect:0x%.8x\tType:0x%.8x\n",
	//	mbi.BaseAddress,mbi.AllocationBase,
	//	mbi.AllocationProtect,mbi.RegionSize,
	//	mbi.State,mbi.Protect,mbi.Type
	//	);

	//DECOMMIT�ͷţ�ҳ�潫��Ϊ����״̬
	printf("Free: DECOMMIT\n");
	if(!VirtualFree(lpRound,sizeVirtual,MEM_DECOMMIT))
	{
		printf("VirtualFree error: %d",GetLastError());
		return 1;
	}
	//��ȡ�ڴ���Ϣ����ӡ
	VirtualQuery(lpAddress,&mbi,sizeof(mbi));
	printf("ʹ��VirtualQuery��õ���Ϣ��\n"
		"BaseAddress:0x%.8x\tAllocationBase:0x%.8x\t"
		"AllocationProtect:0x%.8x\tRegionSize:%u\t"
		"State:0x%.8x\tProtect:0x%.8x\tType:0x%.8x\n",
		mbi.BaseAddress,mbi.AllocationBase,
		mbi.AllocationProtect,mbi.RegionSize,
		mbi.State,mbi.Protect,mbi.Type
		);
	//�ͷ��ڴ�
	printf("Free:RELEASE\n");
	if(!VirtualFree(lpAddress,0,MEM_RELEASE))
	{
		printf("VirtualFree error: %d",GetLastError());
		return 1;
	}
	return 0;
}