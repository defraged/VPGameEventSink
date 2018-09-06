#include "JoeEncryption.h"

ULONG JoeDecrypt(char* EncryptedKey)
{
	BYTE *numbBytes;
	LONG numbCnt;
	LONG *Numbers;
	DWORD dataPos = 0;
	LONG secretNumber;
	SIZE_T lngLen = sizeof(LONG);

	strrev(EncryptedKey);
	size_t encKeyLen = strlen(EncryptedKey);

	//convert character zero's into null character 0
	for(int i = 0; i < encKeyLen; i++)
		if(EncryptedKey[i] == 48)
			EncryptedKey[i] -= 48;

	numbBytes = reinterpret_cast<BYTE*>(EncryptedKey);

	CopyMemory((void*)&numbCnt, EncryptedKey, lngLen);
	char temp[sizeof(long)*8+1];
	ltoa(encKeyLen, temp, 10);

	::MessageBox(NULL, temp, "", MB_OK);
	if(numbCnt == 9)
		::MessageBox(NULL, "ok", "asdfasdf", MB_OK);

	/*dataPos += lngLen;
	Numbers = new LONG[numbCnt];

	for(INT i = 0; i < numbCnt; i++)
	{
		CopyMemory((void*)&Numbers[i], reinterpret_cast<BYTE*>(EncryptedKey)+dataPos, lngLen);
		dataPos += lngLen;
	}

	secretNumber = Numbers[numbCnt - 1];

	for(INT h = 0; h < numbCnt - 2; h+=2)
		secretNumber -= ((Numbers[h] * 255) + Numbers[h+1]);

	delete[] Numbers;
	Numbers = 0;

	return (ULONG)secretNumber;*/return 0;
}