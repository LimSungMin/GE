
// GEDoc.h : CGEDoc Ŭ������ �������̽�
//


#pragma once


class CGEDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGEDoc();
	DECLARE_DYNCREATE(CGEDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	int m_switchVar;
	CString �̰����׽�Ʈ�����Դϴ�;
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGEDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
