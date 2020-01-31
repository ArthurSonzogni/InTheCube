#include "game/FinishBlock.hpp"

FinishBlock::FinishBlock()
{
	geometry.left=0;
	geometry.top=0;
	geometry.right=0;
	geometry.bottom=0;
}

FinishBlock::FinishBlock(int x, int y, int width, int height)
{
	geometry.left=x;
	geometry.right=x+width;
	geometry.top=y;
	geometry.bottom=y+height;
}
