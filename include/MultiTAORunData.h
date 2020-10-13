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

#ifndef MULTITAORUNDATA
#define MULTITAORUNDATA 

#include "RadioActiveSource.h"
#include "TGraphErrors.h"
#include "TAORunData.h"
#include <string>
#include <vector>
#include "TF1.h"

/**
 * @brief:  Model of several radio active sources which
 *          are used for nonlinearity calibration
 */
class MultiTAORunData
{
private:
    //Names of radioactive sources
    std::vector<std::string> sources;

    //all calibration height is set to 0mm
    std::vector<TAORunData*> taoRunDatas;

    //Number of Parameters
    int NPars; 

    //min gamma energy
    float minGammaEnergy;
    float maxGammaEnergy;

    //Total spectrum of all radio active sources
    TH1F* totalPESpectrum; 

    //MCShape function for fit
    TF1* tfTotalMCShape;

    //initialize the tree
    void Initialize(std::vector<std::string> inSources,int Nfile,std::vector<std::string> dataSubPath);

    
    
public:
    MultiTAORunData(std::vector<std::string> inSources,std::vector<std::string> dataFiles,int Nfile);
    MultiTAORunData(std::string inSources[], int N,std::string dataFiles[],int NFile);
    ~MultiTAORunData();

    //MCShape function to fit total PE spectrum of multi. sources
    double TotalMCShape(double* x,double* pars);
    TF1*   GetTFTotalMCShape();
    TH1F*  GetTotalPESpectrum();
    void  AddBkg(float time=500);
    void  SubBkg(float time=500);
    void  ASBkg(float time=500);
    TAORunData*  GetTAORunData(std::string name);
    TAORunData*  GetTAORunData(int index);

    /*Update hist*/
    //paramas:
    //  syn: updata the total pe histograms in taorundatas
    void UpdateTotalPEHist(bool syn=true);
    void UpdateTotalPEHist(float xmin,float xmax,int NBins,bool syn=true);
    void UpdateTotalPEHist(int NBins,float* bins,bool syn=true);

    //Add K40 and Co60 Spectrum : For separate Fitting!
    void AddK40Co60Bkg(float time=5000);

    //Fill total PE into total PE histogram
    void FillTotalPESpectrum();

    //Fit total PE histogram use tfMCShape
    void FitTotalPESprectrum();

    //Get Fitting Bias
    TGraphErrors* GetFittingBias();

    

};




#endif

