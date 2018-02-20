#ifndef matCFSTd_H
#define matCFSTd_H
#include <iostream>
#include <vector>
#include "tribackbone.h"
#include "unLoadPath1.h"
#include "unLoadPath2.h"
#include "generalPath.h"

class matCFSTd
{
public:
    matCFSTd(double E, double f1, double f2, double b1, double b2, double revRatio, double dFactor);
    matCFSTd();
    ~matCFSTd();

    void nextStress(double strain_next);
    void next();
    void revertToLast();
    void reset();


    double E_ini, f1, f2, b1, b2, revRatio, dFactor;
    double Ystrain;
    double E, strain, stress;
    double stressOri, stressOri_next;
    double E_next, strain_next, stress_next;
    double strainCum, strainCum_next;


    
private:
    void initial();
    void getDataFromPath();
    unsigned int nextCondition;
    double stressD(double strain, double stress);
    generalPath* getCurLP();

    TriBackbone BB;
    unLoadPath1 LP1, LP1_next;
    unLoadPath2 LP2, LP2_next;
};

#endif
