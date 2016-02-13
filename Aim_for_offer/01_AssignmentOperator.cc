
class CMyString
{
public:
	CMyString(char* pData = NULL);
	CMyString(const CMyString& str);
	~CMyString(void);

private:
	char* m_pData;
};

CMyString& CMyString::operator=(const CMyString& rhs)
{
	if (this != &rhs)
	{
		CMyString strTemp(rhs);

		char* pTemp = m_pData;
		m_pData = strTemp.m_pData;
		strTemp.m_pData = pTemp;
	}

	return *this
}

CMyString& CMyString::operator=(CMyString rhs)
{
	using std::swap;
	swap(m_pData,rhs.m_pData);
	return *this;
}
