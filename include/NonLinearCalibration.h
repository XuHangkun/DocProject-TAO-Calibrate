#ifndef NONLINEARCALIBRATION
#define NONLINEARCALIBRATION

#include <vector>

//Photon Absorption in Source Enclosure
void PhotonAbsInEnclosure();


//Fitting Bias Styde
std::vector<float> MultiSourceFitBias(int NK40Gamma=5000, int NCo60Gamma=50000);
void OptimizeEventNumbers();
#endif
