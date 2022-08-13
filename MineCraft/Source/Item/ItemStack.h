#pragma once

#include "Material.h"

class ItemStack
{
public:
	ItemStack(Material material, int amount);
	void add(int amount);
	void remove();
private:
	Material m_material;
	int numInStack;
};