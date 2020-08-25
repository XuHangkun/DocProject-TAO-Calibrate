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
*  @brief    ABC of physics run data                                         *
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
/**
 * @brief:  model of radio active source
 */
class RadioActiveSource
{
private:
    std::string source;  //source name
    int calibHeight;     //calibbration height
    int NFile;
    float gammaEnergy;   //Gamma Energy

    //Fit parameters
    int NPars;
    float initialAmp;
    float initialMean;
    float initialSigma;
    float initialELeapFrac;
    float matchMean;
    TGraph* gr_ELeap;
public:
    RadioActiveSource(std::string inSource,int inNFile,int inCalibHeight);
    ~RadioActiveSource();

    int GetNPars() { return NPars; }
    float GetInitialAmp() { return initialAmp; }
    float GetInitialMean() { return initialMean; }
    float GetInitialSigma() { return initialSigma; }
    float GetInitialELeapFrac() { return initialELeapFrac; }

    //Manage files, return file list of root files
    std::vector<std::string> GetFileNames();

    //read xml file and get fit parameters
    void ReadInitialFitPars();

    //Gaus, ELeapSepc and totalSpec
    double Gaus(double* x,double* par);
    double ELeapSpec(double* x,double* par);
    double MCShape(double* x,double* par);

    //Get the range of total PE spectrum ( Min )
    float GetTotalPEHistXMin();
    //Get the range of total PE spectrum ( Max )
    float GetTotalPEHistXMax();
    //Get avaliable bin number of total PE spectrum
    int GetTotalPEHistNBins();

    //Get unique label
    std::string GetSourceLabel();

};





#endif