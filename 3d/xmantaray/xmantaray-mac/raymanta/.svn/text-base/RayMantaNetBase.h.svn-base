#ifndef _NETBASE_H_
#define _NETBASE_H_
#include <iostream>

#include <unistd.h>

class RayMantaNetBase
{
public:
	RayMantaNetBase() {}
	RayMantaNetBase(RayMantaNetBase const& n) {}
	virtual ~RayMantaNetBase() {}

	inline virtual int lock(pid_t pid) = 0; 
	inline virtual int get_status(pid_t pid) = 0; 
	inline virtual void set_status(pid_t pid, int s) = 0; 
public:	 
	RayMantaNetBase &operator=(RayMantaNetBase const& n) { return *this; }
};

#endif
