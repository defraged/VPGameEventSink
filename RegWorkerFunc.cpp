#include "RegWorkerFunc.h"

char **strArrGames;

bool GetGamesList(std::vector<CComBSTR> *vecGames)
{
	USES_CONVERSION;
	DWORD retval;
	HKEY m_vpgRoot;
	bool success = true;

	retval = RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT("Software\\Ubique\\VpGames32"), 
		0, KEY_READ, &m_vpgRoot);

	if(retval != ERROR_SUCCESS)
		success =  false;

    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i, retCode; 
	char *gameName;

    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        m_vpgRoot,                    // key handle 
		achKey,
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    if (cSubKeys)
    {
        for (i=0; i < cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
			gameName = new char[MAX_KEY_LENGTH];
            retCode = RegEnumKeyEx(m_vpgRoot, i,
                     gameName, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime);

			if(retCode == ERROR_SUCCESS)
				vecGames->push_back(SysAllocString(T2OLE((LPTSTR)gameName)));
			
			delete gameName;
			gameName = 0;
		}
	}

	RegCloseKey(m_vpgRoot);
	return success;
}

bool GetGamesList(DWORD *keyCount)
{
	USES_CONVERSION;
	DWORD retval;
	HKEY m_vpgRoot;
	bool success = true;

	retval = RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT("Software\\Ubique\\VpGames32"), 
		0, KEY_READ, &m_vpgRoot);

	if(retval != ERROR_SUCCESS)
		success =  false;

    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i, retCode; 
	
    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        m_vpgRoot,                    // key handle 
		achKey,
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    if (cSubKeys)
    {
		strArrGames = new char*[cSubKeys];
		*keyCount = cSubKeys;

        for (i = 0; i < cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
			strArrGames[i] = new char[MAX_KEY_LENGTH];
            retCode = RegEnumKeyEx(m_vpgRoot, i,
									strArrGames[i], 
									&cbName, 
									NULL, 
									NULL, 
									NULL, 
									&ftLastWriteTime);

			if(retCode != ERROR_SUCCESS)
				success = false;
		}
	}

	RegCloseKey(m_vpgRoot);
	return success;
}
//GetCurrentCLSID will grab the data of the specified registry key
//in this case the data will be the CLSID of a VP Game COM ocx.
bool GetCurrentCLSID(char *gameName, char **clsid)
{
	HKEY m_vpgRoot;
	bool success = true;

	if(RegOpenKeyEx(HKEY_CLASSES_ROOT, gameName, 
		0, KEY_READ, &m_vpgRoot) != ERROR_SUCCESS)
			success = false;

	DWORD retcode; //return value
	DWORD dataType = REG_SZ; //the data type
	DWORD BufferSize = MAX_REG_KEY_VALUE;
	BYTE *keyData;
	LPCTSTR valName = NULL;

	keyData = new BYTE[MAX_REG_KEY_VALUE]; //allocate memory buffer
	memset(keyData, '\0', sizeof(keyData));

	retcode = RegQueryValueEx(m_vpgRoot, valName, NULL, &dataType,
							keyData, &BufferSize);
	
	if(retcode==ERROR_SUCCESS)
		*clsid = (char*)keyData;
	else
		success = false;

	RegCloseKey(m_vpgRoot);
	return success;
}

bool FindGameCLSID(char *clsid)
{
	bool found = false;
	DWORD keyCount;

	if(GetGamesList(&keyCount) == false)
		return false;
	
	char* keyName;
	char* sclsid;
	
	UINT lenGmName;
	char* rootKey = "Software\\Ubique\\VpGames32\\"; //store our root key string
	UINT lenRootKey = strlen(rootKey);

	for(DWORD i = 0; i < keyCount; i++)
	{
		lenGmName = strlen(strArrGames[i]);
		keyName = new char[lenRootKey + lenGmName + 1];

		//concatenate root key, and gamename to create our whole keyname string.
		strcpy(keyName, rootKey);
		strcat(keyName, strArrGames[i]); 
		strcat(keyName, "\0"); //must null terminate string !

		GetCurrentCLSID(keyName, &sclsid);

		delete[] keyName;
		keyName = 0;
		delete[] strArrGames[i];
		strArrGames[i] = 0;

		if(strcmp(sclsid, clsid) == 0)
			found = true;
	
		delete[] sclsid;
		sclsid = 0;

		if(found == true)
			break;
	}

	delete[] strArrGames;
	strArrGames = 0;

	return found;
}