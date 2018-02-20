#include <elementAPI.h>
#include "testCFSTd.h"
#include <Vector.h>
#include <Channel.h>
#include <math.h>
#include <float.h>
#include "matCFSTd.h"

#ifdef _USRDLL
#define OPS_Export extern "C" _declspec(dllexport)
#elif _MACOSX
#define OPS_Export extern "C" __attribute__((visibility("default")))
#else
#define OPS_Export extern "C"
#endif


static int numtestCFSTd = 0;

OPS_Export void *OPS_testCFSTd()
{
    // print out some KUDO's
    if (numtestCFSTd == 0) {
        opserr << "testCFSTd uniaxial material - Written by Yadong Jiang\n";
        numtestCFSTd = 1;
    }

    // Pointer to a uniaxial material that will be returned
    UniaxialMaterial *theMaterial = 0;

    //
    // parse the input line for the material parameters
    //

    int    iData[1];
    double dData[9];
    int numData;
    numData = 1;
    if (OPS_GetIntInput(&numData, iData) != 0) {
        opserr << "WARNING invalid uniaxialMaterial testCFSTd tag" << endln;
        return 0;
    }

    numData = 9;
    if (OPS_GetDoubleInput(&numData, dData) != 0) {
        opserr << "WARNING invalid E & f1 & f2 & b1 & b2 & revRatio & dFactor & Efactor & Rfactor\n";
        return 0;
    }

    //
    // create a new material
    //

    theMaterial = new testCFSTd(iData[0], dData[0], dData[1], dData[2], dData[3], dData[4], dData[5], dData[6], dData[7], dData[8]);

    if (theMaterial == 0) {
        opserr << "WARNING could not create uniaxialMaterial of type testCFSTd\n";
        return 0;
    }

    // return the material
    return theMaterial;
}


testCFSTd::testCFSTd(int tag, double E, double f1, double f2, double b1, double b2, double revRatio, double Dfactor, double Efactor, double Rfactor):UniaxialMaterial(tag, 0)
{
    this->curMat = matCFSTd(E, f1, f2, b1, b2, revRatio, Dfactor, Efactor, Rfactor);
}


testCFSTd::testCFSTd() :UniaxialMaterial(0, 0)
{
}

testCFSTd::~testCFSTd()
{
    //do nothing here
}

int testCFSTd::setTrialStrain(double strain, double strainRate)
{
    if (fabs(strain - this->curMat.strain) < DBL_EPSILON)
    {
        return 0;
    } else {
        this->curMat.nextStress(strain);
        return 0;
    }
}

double testCFSTd::getStrain(void)
{
    return this->curMat.strain_next;
}

double testCFSTd::getStress(void)
{
    return this->curMat.stress_next;
}

double testCFSTd::getTangent(void)
{
    return this->curMat.E_next;
}

double testCFSTd::getInitialTangent(void)
{
    return this->curMat.E_ini;
}

int testCFSTd::commitState(void)
{
    this->curMat.next();
    return 0;
}

int testCFSTd::revertToLastCommit(void)
{

    this->curMat.revertToLast();
    return 0;
}

int testCFSTd::revertToStart(void)
{
    this->curMat.reset();
    return 0;
}

UniaxialMaterial *testCFSTd::getCopy(void)
{
    testCFSTd *theCopy = new testCFSTd(this->getTag(), this->curMat.E_ini, this->curMat.f1, this->curMat.f2, this->curMat.b1, this->curMat.b2, this->curMat.revRatio, this->curMat.Dfactor, this->curMat.Efactor, this->curMat.Rfactor);
    theCopy->curMat = this->curMat;
    //opserr << this->i << endln;
    return theCopy;
}

int testCFSTd::sendSelf(int commitTag, Channel &theChannel)
{
    int res = 0;
    /*
    static Vector data(2);
    data(0) = this->getTag();
    data(1) = this->curMat;
    res = theChannel.sendVector(this->getDbTag(), commitTag, data);
    if (res < 0)
        opserr << "testCFSTd::sendSelf() - failed to send data\n";
    */
    return res;
}
int testCFSTd::recvSelf(int commitTag, Channel &theChannel, FEM_ObjectBroker &theBroker)
{
    int res = 0;
    /*
    static Vector data(2);
    res = theChannel.recvVector(this->getDbTag(), commitTag, data);
    if (res < 0) {
        opserr << "testCFSTd::recvSelf() - failed to receive data\n";
    }
    else {
        this->setTag(data(0));
        this->curMat = data(1);
    }
    */
    return res;
}

void testCFSTd::Print(OPS_Stream &s, int flag)
{
    s << "testCFSTd tag: " << this->getTag() << endln;
}



