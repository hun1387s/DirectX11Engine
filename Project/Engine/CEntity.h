#pragma once


class CEntity
{
private:
	static UINT NextID;

private:
	wstring		Name;
	UINT		ID;

public:
	const wstring& GetName() { return Name; }
	void SetName(const wstring& _name) { Name = _name; }
	UINT GetID() { return ID; }

	// 자기 자신을 복제한 객체를 반환
	//virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _origin);
	virtual	~CEntity();

};

