/*****************************************************************************
*  OpenST Basic tool library                                                 *
*  Copyright (C) 2020 Xu Hangkun  xuhangkun@ihep.ac.cn                       *
*                                                                            *
*  This file is part of OST.                                                 *
*                                                                            *
*  This program is free software; you can redistribute it and/or modify      *
*  it under the terms of the GNU General Public License version 3 as         *
*  published by the Free Software Foundation.                                *
*                                                                            *
*  You should have received a copy of the GNU General Public License         *
*  along with OST. If not, see <http://www.gnu.org/licenses/>.               *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*  @file     RunData.h                                                       *
*  Details.                                                                  *
*                                                                            *
*  @author   Xu Hangkun                                                      *
*  @email    xuhangkun@ihep.ac.cn                                            *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2020-08-24                                                      *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2020/08/24 | 1.0.0.1   | Xu Hangkun     | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef RADIOACTIVESOURCE
#define RADIOACTIVESOURCE

#include <string>
#include "TGraph.h"
#include <vector>
#include <iostream>
#include "TF1.h"
#include "globals.h"
#include "TVector3.h"

/**
 * @brief:  model of radio active source
 */
class RadioActiveSource
{
private:
    std::string source;         //source name
    TVector3 calibPosition;     //calibbration Position
    float kinetic;              //Gamma Energy

    //Fit parameters
    int   NPars;
    float initialAmp;
    float initialMean;
    float initialSigma;
    float initialELeapFrac;
    float matchMean;
    TGraph* gr_ELeap;
    TF1* tfMCShape;

public:
    RadioActiveSource(std::string inSource,float inCalibHeight);
    RadioActiveSource(std::string inSource,float inKinetic,float inCalibHeight);
    RadioActiveSource(std::string inSource,TVector3 inCalibPos);
    RadioActiveSource(std::string inSource,float inKinetic,TVector3 inCalibPos);
    ~RadioActiveSource();

    /*Get and Set function*/
    std::string GetSourceName() { return source; }
    void SetSourceName(std::string value) { source=value; }

    TVector3 GetCalibPosition() { return calibPosition; }
    float GetCalibPosX() { return calibPosition.X(); }
    float GetCalibPosY() { return calibPosition.Y(); }
    float GetCalibPosZ() { return calibPosition.Z(); }
    
    void SetCalibPosition(TVector3 value) { calibPosition=value; }
       
    int GetNPars() { return NPars; }
    void SetNPars(int value) { NPars=value; }

    float GetInitialAmp() { return initialAmp; }
    void SetInitialAmp(float value) { initialAmp=value; }

    float GetInitialMean() { return initialMean; }
    void SetInitialMean(float value) { initialMean=value; }

    float GetInitialSigma() { return initialSigma; }
    void SetInitialSigma(float value) { initialSigma=value; }

    float GetInitialELeapFrac() { return initialELeapFrac; }
    void SetInitialELeapFrac(float value) { initialELeapFrac=value; }

    float GetMatchMean() { return matchMean; }
    void SetMatchMean(float value) { matchMean=value; }

    float GetKinetic() { return kinetic; }
    void SetKinetic(float value) { kinetic=value; }

    TF1* GetTFMCShape() { return tfMCShape; }
    TGraph* GetELeapSpec() { return gr_ELeap; }


    //read xml file and get fit parameters
    bool ReadInitialFitPars();

    //Query the kinetic energy of radioactive particle
    void QuerySourceKinetic();

    //Gaus, ELeapSepc and totalSpec
    double Gaus(double* x,double* par);
    double ELeapSpec(double* x,double* par);
    double MCShape(double* x,double* par);


    //Get unique label
    std::string GetSourceLabel();

    //Output
    friend std::ostream & operator<<(std::ostream & os, const RadioActiveSource radioAS); 

};

#endif
