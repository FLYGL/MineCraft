#pragma once
#include "../Block/ChunkBlock.h"

struct IChunk
{
	virtual ChunkBlock getBlock(int x, int y, int z) const = 0;
	virtual bool setBlock(int x, int y, int z, ChunkBlock block) = 0;
};