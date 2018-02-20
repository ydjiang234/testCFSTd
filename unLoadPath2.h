#ifndef UNLOADPATH2_H
#define UNLOADPATH2_H

#include <iostream>
#include <vector>
#include "generalPath.h"

class unLoadPath2 : public generalPath
{
public:
    
    //Four Points
    unLoadPath2(std::vector<double> xdata, std::vector<double> ydata);
    unLoadPath2();
    ~unLoadPath2();
    
    unLoadPath2 unload(double x, double y, double curE, double curRev);
    unsigned int isLeave(double nextX);

    double getE(double x);

    
    unsigned int direction;//1 - low to high, 2 - high to low
    
private:
    virtual void initial();
    
};


#endif
