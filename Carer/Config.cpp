#include "StdAfx.h"
#include "Config.h"

#define HKEY_APP L"Software\\LJW\\remind"

CConfig* CConfig::m_instance = NULL;

CConfig::CConfig(void)
{
}

CConfig::~CConfig(void)
{
}

CConfig* CConfig::Instance(){
	if (!m_instance)
	{
		m_instance = new CConfig;
	}
	return m_instance;
}

INT CConfig::GetIntValue(const CStringW & key, INT defValue){
	CRegKey reg(HKEY_CURRENT_USER);
	reg.Create(HKEY_CURRENT_USER, HKEY_APP);	
	DWORD dwValue = defValue;
	reg.QueryDWORDValue(key, dwValue);
	return dwValue;
}

void CConfig::SetIntValue(const CStringW & key, INT value){
	CRegKey reg(HKEY_CURRENT_USER);	
	reg.Create(HKEY_CURRENT_USER, HKEY_APP);	
	reg.SetDWORDValue(key, value);
}
