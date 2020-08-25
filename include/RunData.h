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
#ifndef RUNDATA
#define RUNDATA

#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

/**
 * @brief: ABC of run data model of high energy experiments
 */
class RunData
{
private:

protected:

    TChain* mainTree;         //the tree which include all variables we need
    int NEtries;             //number of entries in mainTree

public:
    RunData();
    ~RunData();

    /*Open the file and initialize the tree*/
    virtual void Initialize()=0;

    /*Close the file*/
    virtual void Finalize()=0;
};

#endif