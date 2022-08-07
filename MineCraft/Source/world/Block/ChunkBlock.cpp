#include "ChunkBlock.h"
#include "BlockDatabase.h"

ChunkBlock::ChunkBlock(Block_t id):id(id)
{
}

ChunkBlock::ChunkBlock(BlockId id) : id(static_cast<Block_t>(id))
{

}

const BlockData& ChunkBlock::getData()const
{
	return BlockDatabase::get().getData(static_cast<BlockId>(id));
}

const BlockType& ChunkBlock::getType() const
{
	return BlockDatabase::get().getBlock(static_cast<BlockId>(id));
}