#ifndef SIPM
#define SIPM

#include "TVector3.h"
#include <vector>
#include <iostream>
#include "TF1.h"
#include "TF2.h"

class SiPM
{
public:
    SiPM();
    ~SiPM();

    static const int NSIPM=4074;      //number of PMT
    //Read SiPM infomation
    void Initialize();
    //Calculate Solid Angle of SiPM
    void CalSiPMSolidAngle();
    void CalGapCorrectFactor();

    //Get and Set function
    float GetSiPMPositionX(int id) { return position[id].X(); }
    float GetSiPMPositionY(int id) { return position[id].Y(); }
    float GetSiPMPositionZ(int id) { return position[id].Z(); }
    TVector3 GetSiPMPosition(int id) { return position[id]; }
    float GetGapCorrectFactor(int id) { return gapCorrectFactor[id]; }
    float GetSolidAngle() { return SiPMSolidAngle; }
    float GetCoverRatio() { return CoverRatio; }
    double CalSiPMSolidAngle(int sipmId,TVector3 refPoint=TVector3(0,0,930.2));

    //Reload operator
    friend std::ostream& operator<<(std::ostream& os,const SiPM sipm);

private:
    float SiPMX;                      //Size of SiPM
    float SiPMY;
    float SiPMPosR;                   //Radius of SiPM center
    float CoverRatio;
    float gapCorrectFactor[NSIPM];    //factor to correct the effect caused by gad becween SiPM
    int ID[NSIPM];                    //SiPM id
    TVector3 position[NSIPM];         //position 
    float darkNoise[NSIPM];           //Dark noise

    float SiPMSolidAngle;             //Solid angle of a SiPM, relative to center
    float eTheta[NSIPM];
    float nTheta[NSIPM];
    float ePhi[NSIPM];
    float nPhi[NSIPM];

    TF2* tf_SiPMSolidAngle;
};

double fSiPMSolidAngle(double *val,double* par);


#endif
