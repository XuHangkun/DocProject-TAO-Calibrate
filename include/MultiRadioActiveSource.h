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

#ifndef MULTIRADIOACTIVESOURCE
#define MULTIRADIOACTIVESOURCE 

#include "RadioActiveSource.h"
#include <string>
#include <vector>
#include "TF1.h"

/**
 * @brief:  Model of several radio active sources which
 *          are used for nonlinearity calibration
 */
class MultiRadioActiveSource
{
private:
    //Names of radioactive sources
    std::vector<std::string> sources;

    //all calibration height is set to 0mm
    std::vector<RadioActiveSource*> radioActiveSources;

    //Number of Parameters
    int NPars; 

    //min gamma energy
    float minGammaEnergy;
    float maxGammaEnergy;

    //MCShape function for fit
    TF1* tfTotalMCShape;
    


    
public:
    MultiRadioActiveSource(std::vector<std::string> inSources,int Nfile);
    MultiRadioActiveSource(std::string inSources[], int N,int NFile);
    ~MultiRadioActiveSource();

    //MCShape function to fit total PE spectrum of multi. sources
    double TotalMCShape(double* x,double* pars);
    TF1*   GetTFTotalMCShape();

    

};




#endif

