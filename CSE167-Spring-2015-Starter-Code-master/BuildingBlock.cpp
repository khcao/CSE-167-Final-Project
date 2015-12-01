#include "BuildingBlock.h"
#include "MetroBlock.h"

#include <iostream>

using namespace std;

int nombreQuad = 10;

BuildingBlock::BuildingBlock()
{}

BuildingBlock::BuildingBlock(const Vector& _a, const Vector& _b, const Vector& _c) : a(_a), b(_b), c(_c),
ab(Norm(b - a)), bc(Norm(c - b)), ca(Norm(a - c))
{}

BuildingBlock::BuildingBlock(const Vector& _a, const Vector& _b, const Vector& _c, const vector<Centre> &_centres) : a(_a), b(_b), c(_c),
centres(_centres), ab(Norm(b - a)), bc(Norm(c - b)), ca(Norm(a - c))
{}

BuildingBlock::BuildingBlock(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d) : a(_a), b(_b), c(_c), d(_d),
ab(Norm(b - a)), bc(Norm(c - b)), cd(Norm(d - c)), da(Norm(a - d))
{}

BuildingBlock::BuildingBlock(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const vector<Centre> &_centres) : a(_a), b(_b), c(_c), d(_d),
centres(_centres), ab(Norm(b - a)), bc(Norm(c - b)), cd(Norm(d - c)), da(Norm(a - d))
{}


void BuildingBlock::constructBlock(const Quadrangle& _q, const vector< Centre>& _centres)
{
	//this is the type of block we want. We could theoretically add
	//controls as to what kind of block we want (IE industrial)
	 MetroBlock::constructBlock(_q, _centres[0]);
}
