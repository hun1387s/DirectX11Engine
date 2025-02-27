#pragma once

#define SINGLE(Type)	private:\
							Type();\
							Type(const Type& _origin) = delete;\
						public:\
							~Type();\
							friend class CSingleton<Type>;

#define _DEVICE CDevice::GetInst()->GetDevice()
#define _CONTEXT CDevice::GetInst()->GetContext()

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_NONE(key)		  KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_PRESSED(key)	  KEY_CHECK(key, KEY_STATE::PRESSED)
#define KEY_TAP(key)		  KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_RELEASED(key)	  KEY_CHECK(key, KEY_STATE::RELEASED)

#define DT CTimeMgr::GetInst()->GetDeltaTime()

//typedef Vector3 Vec3;


