#pragma once

#include <string>
#include "../world/Block/BlockId.h"
#include "../Util/NonCopyable.h"

struct Material : public NonCopyable
{
	enum ID
	{
		Nothing,
		Grass,
		Dirt,
		Stone,
		OakBark,
		OakLeaf,
		Sand,
		Water,
		Cactus,
		Rose,
		TallGrass,
		DeadShrub
	};
	
	const static Material NOTHING, GRASS_BLOCK,
		DIRT_BLOCK, STONE_BLOCK, OAK_BARK_BLOCK, OAK_LEAF_BLOCK,
		SAND_BLOCK,WATER_BLOCK,CACTUS_BLOCK,ROSE,TALL_GRASS,
		DEAD_SHRUB;

	Material(Material::ID id, int maxStack, bool isBlock, std::string&& name);
	BlockId toBlockID() const;
	static const Material& toMaterial(BlockId id);
	const Material::ID id;
	const int maxStackSize;
	const bool isBlock;
	const std::string name;
};


namespace std
{
	template<>
	struct hash<Material::ID>
	{
		size_t operator()(const Material::ID& id) const
		{
			std::hash<Material::ID> hasher;
			return hasher(id);
		}
	};
}