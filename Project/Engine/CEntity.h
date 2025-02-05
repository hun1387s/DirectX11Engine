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

public:
	CEntity();
	CEntity(const CEntity& _origin);
	~CEntity();

};

