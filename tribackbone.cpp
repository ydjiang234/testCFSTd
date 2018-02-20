#include "tribackbone.h"
#include "generalPath.h"
#include <float.h>
#include <iostream>
#include <vector>

TriBackbone::TriBackbone(std::vector<double> xdata, std::vector<double> ydata) : generalPath(xdata, ydata)
{
    this->initial();
}

TriBackbone::TriBackbone() : generalPath(){};

TriBackbone::~TriBackbone() {}

unLoadPath1 TriBackbone::unload(double x, double y, double curE, double curRev)
{
    double Rev, tempx1;
    std::vector<double> tempxdata, tempydata;
    int tempDirection;
    if (this->isLinear(x) == false)
    {
        if (std::abs(y) <= curRev)
            curRev = std::abs(y);

        if (x > 0) {
            Rev = -1 * curRev;
            tempDirection = -1;
        } else {
            Rev = curRev;
            tempDirection = 1;
        }
        tempx1 = x - (y - Rev) / curE;

        if (x > 0) {
                tempxdata = {-x, tempx1, x};
                tempydata = {-y, Rev, y};
            } else {
                tempxdata = {x, tempx1, -x};
                tempydata = {y, Rev, -y};
            }
    }
    
    return unLoadPath1(tempxdata, tempydata, tempDirection);
}

unsigned int TriBackbone::isLeave(double nextX)
{
    unsigned int out;
    if (this->isInRange(nextX)) {
        if (this->isLinear(this->curX)) {
            out = 0;
        } else {
            if (this->curX * (nextX - this->curX) < 0) {
                out = 1;
            } else {
                out = 0;
            }
        }
    } else {
        out = 0;
    }

    return out;
}

double TriBackbone::getE(double x)
{
    double out;
    if (this->isInRange(x)) {
        if (x <= this->xdata[1]) {
            out = this->E2;
        } else if (x <= this->xdata[2]) {
            out = this->E1;
        } else if (x <= this->xdata[3]) {
            out = this->E;
        } else if (x <= this->xdata[4]) {
            out = this->E1;
        } else if (x <= this->xdata[5]) {
            out = this->E2;
        }
    } else {
        out = DBL_EPSILON;
    }
    return out;
}

void TriBackbone::initial()
{
    this->linearRange.push_back(this->xdata[2]) ;
    this->linearRange.push_back(this->xdata[3]) ;
    this->E = (this->ydata[3] - this->ydata[2]) / (this->xdata[3] - this->xdata[2]);
    this->E1 = (this->ydata[4] - this->ydata[3]) / (this->xdata[4] - this->xdata[3]);
    this->E2 = (this->ydata[5] - this->ydata[4]) / (this->xdata[5] - this->xdata[4]);
}

