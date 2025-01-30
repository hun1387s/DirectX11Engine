#pragma once

#define SINGLE(Type)	private:\
							Type();\
							Type(const Type& _origin) = delete;\
						public:\
							~Type();\
							friend class CSingleton<Type>;

#define _DEVICE CDevice::GetInst()->GetDevice()
#define _CONTEXT CDevice::GetInst()->GetContext()

//typedef Vector3 Vec3;
