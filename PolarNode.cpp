#include "PolarNode.h"

typedef std::pair<int, int> Pi;

PolarNode::PolarNode() :BottomLeft({ 0,50 }), BottomRight({ 10,50 }),
TopLeft({ 0,80 }), TopRight({10,80}),occupancy(1) {

}

PolarNode::PolarNode(Pi BL) : BottomLeft(BL),occupancy(1){
	BottomRight = std::make_pair(BL.first + width, BL.second);
	TopLeft = std::make_pair(BL.first, BL.second + height);
	TopRight = std::make_pair(BL.first + width, BL.second + height);

}

void PolarNode::updateCoordinates(Pi BL) {
	BottomLeft = BL;
	BottomRight = std::make_pair(BL.first + width, BL.second);
	TopLeft = std::make_pair(BL.first, BL.second + height);
	TopRight = std::make_pair(BL.first + width, BL.second + height);
}

void PolarNode::updateOccupancy(int occ) {
	occupancy = occ;
}

