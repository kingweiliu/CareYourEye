#pragma once

#define CK_GapBetweenShow L"GapBetweenShow"
#define CK_ShowLong L"ShowLong"

class CConfig
{
public:
	
	~CConfig(void);

	static CConfig* Instance();

	INT GetIntValue(const CStringW &, INT def);
	void SetIntValue(const CStringW & key, INT value);

private:
	CConfig(void);
	static CConfig * m_instance;
};

