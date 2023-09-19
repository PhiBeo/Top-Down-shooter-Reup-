#include "Gun.h"

Gun::Gun(int id, float fireRate, int maxAmmo) : 
	_id(id),
	_fireRate(fireRate),
	_maxAmmo(maxAmmo)
{
}

Gun::~Gun()
{
}

int Gun::getId() const
{
	return _id;
}

float Gun::getFireRate() const
{
	return _fireRate;
}

int Gun::getMaxAmmo() const
{
	return _maxAmmo;
}

