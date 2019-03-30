#include "Teleporter.hpp"

Teleporter::Teleporter(int X, int Y,int Width,int Height, int XTeleport, int YTeleport)
{
	xTeleport=XTeleport;
	yTeleport=YTeleport;
	geometry.left=X;
	geometry.top=Y;
	geometry.right=X+Width-1;
	geometry.bottom=Y+Height-1;
}
