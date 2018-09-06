#pragma once

#ifndef _REGFUNC_H
#define _REGFUNC_H

#include "stdafx.h"

bool GetGamesList(std::vector<CComBSTR> *vecGames);
bool GetGamesList(DWORD *keyCount);
//GetCurrentCLSID will grab the data of the specified registry key
//in this case the data will be the CLSID of a VP Game.
bool GetCurrentCLSID(char *gameName, char **clsid);
bool FindGameCLSID(char* clsid);

#endif