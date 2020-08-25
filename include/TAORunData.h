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

#ifndef TAORUNDATA
#define TAORUNDATA

#include "RunData.h"
#include <string>
#include <vector>
#include "TH1F.h"
#include "RadioActiveSource.h"


/**
 * @brief: run data model of TAO
 */
class TAORunData : public RunData
{
private:
    //General information

    std::string source;        //source name
    int calibHeight;
    RadioActiveSource* radioActiveSource;
    //Physical data
    int currentEntry;
    float capTime;          //neutron capture time
    int totalPE;            //total PE of a event
    int NCompton;           //Numbers of compton scattering of a gamma
    float Edep;             //energy deposit in GdLS
    int NParticles;
    std::vector<int> PDGCode;   //pdg code of primary particles
    std::vector<double> hitTime; //hit time of photon on PMT
    float EDepCenterX;     //X value of energy deposit position
    float EDepCenterY;     //Y value of energy deposit position
    float EDepCenterZ;     //Z value of energy deposit position
    
public:
    TAORunData(std::string inSource,int inNFile,int inCalibHeight=0);
    ~TAORunData();

    /*Open the file and initialize the tree*/
    virtual void Initialize();

    /*Close the file*/
    virtual void Finalize();

    /*get function*/
    inline float GetCapTime();
    inline int GetCurrentEntry();
    inline int GetTotalPE();
    inline int GetNCompton();
    inline float GetEdep();
    inline int GetNParticles();
    std::vector<int>& GetPDGCode();
    std::vector<double>& GetHitTime();
    inline float GetEdepCenterX();
    inline float GetEdepCenterY();
    inline float GetEdepCenterZ();

    /*read n'th event in mainTree*/
    void GetEntry(int n);

    /*get histgrom of total PE*/
    TH1F* GetHistOfTotalPE(bool ifFit=false);
        
};

inline int TAORunData::GetCurrentEntry()
{
    return currentEntry;
}

inline float TAORunData::GetCapTime()
{
    return capTime;
}

inline int TAORunData::GetTotalPE()
{
    return totalPE;
}

inline int TAORunData::GetNCompton()
{
    return NCompton;
}

inline float TAORunData::GetEdep()
{
    return Edep;
}

inline int TAORunData::GetNParticles()
{
    return NParticles;
}

inline float TAORunData::GetEdepCenterX()
{
    return EDepCenterX;
}

inline float TAORunData::GetEdepCenterY()
{
    return EDepCenterY;
}

inline float TAORunData::GetEdepCenterZ()
{
    return EDepCenterZ;
}
#endif
