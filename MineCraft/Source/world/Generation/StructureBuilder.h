#pragma once

#include <vector>
#include "../Block/BlockId.h"

class Chunk;
class StructureBuilder
{
	struct Block
	{
		Block(BlockId id, int x, int y, int z) : id(id), x(x), y(y), z(z)
		{

		}
		BlockId id;
		int x, y, z;
	};
public:
	void build(Chunk& chunk);
	void makeColumn(int x, int z, int yStart, int height, BlockId block);
	void fill(int y, int xStart, int xEnd, int zStart, int zEnd, BlockId block);
	void addBlock(int x, int y, int z, BlockId block);
private:
	std::vector<Block> m_blocks;
};