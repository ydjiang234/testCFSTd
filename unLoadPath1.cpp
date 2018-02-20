#include <iostream>
#include <vector>
#include "generalPath.h"
#include "unLoadPath1.h"
#include "unLoadPath2.h"
#include <float.h>


unLoadPath1::unLoadPath1(std::vector<double> xdata, std::vector<double> ydata, int direction) : generalPath(xdata, ydata)
{
    this->direction = direction;
    this->initial();
}

unLoadPath1::unLoadPath1() : generalPath() {}

unLoadPath1::~unLoadPath1() {}

unLoadPath2 unLoadPath1::unload(double x, double y, double curE, double curRev)
{
    double Rev, tempx1;
    std::vector<double> tempxdata, tempydata;
    if (this->isLinear(x) == false) {
        if (std::abs(y) <= curRev)
            curRev = std::abs(y);


        if (this->direction==1) {
            Rev = -1 * curRev;
        } else {
            Rev =  curRev;
        }
        tempx1 = x - (y - Rev) / curE;
        
        if (this->direction==1) {
            tempxdata = {this->xdata[0], tempx1, x, this->xdata.back()};
            tempydata = {this->ydata[0], Rev, y, this->ydata.back()};
        } else {
            tempxdata = {this->xdata[0], x, tempx1, this->xdata.back()};
            tempydata = {this->ydata[0], y, Rev, this->ydata.back()};
        }
    }
    //std::cout<<tempxdata[0]<<' '<<tempxdata[1]<<' '<<tempxdata[2]<<' '<<tempxdata[3]<<std::endl;
    //std::cout<<tempydata[0]<<' '<<tempydata[1]<<' '<<tempydata[2]<<' '<<tempydata[3]<<std::endl;
    return unLoadPath2(tempxdata, tempydata);
}

unsigned int unLoadPath1::isLeave(double nextX)
{
    unsigned int out;
    if (this->isInRange(nextX)) {
        if (this->isLinear(this->curX)) {
            out = 0;
        } else {
            if (this->direction * (nextX - this->curX) > 0) {
                out = 0;
            } else {
                out = 21;
            }
        }
    } else {
        out = 3;
    }
    return out;
}

double unLoadPath1::getE(double x)
{
    double out;
    if (this->isInRange(x)) {
        if (x <= this->xdata[1]) {
            if (this->direction==1) {out = this->E;} else {out = this->E1;}
        } else if (x <= this->xdata[2]) {
            if (this->direction==1) {out = this->E1;} else {out = this->E;}
        }
    } else {
        out = DBL_EPSILON;
    }
    return out;
}

void unLoadPath1::initial()
{
    if (this->direction==1) {
        this->linearRange.push_back(this->xdata[0]);
        this->linearRange.push_back(this->xdata[1]);
        this->E = (this->ydata[1] - this->ydata[0]) / (this->xdata[1] - this->xdata[0]);
        this->E1 = (this->ydata[2] - this->ydata[1]) / (this->xdata[2] - this->xdata[1]);
    } else {
        this->linearRange.push_back(this->xdata[1]);
        this->linearRange.push_back(this->xdata[2]);
        this->E = (this->ydata[2] - this->ydata[1]) / (this->xdata[2] - this->xdata[1]);
        this->E1 = (this->ydata[1] - this->ydata[0]) / (this->xdata[1] - this->xdata[0]);
    }
    
    
}
