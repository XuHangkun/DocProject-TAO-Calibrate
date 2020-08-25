#include "test.h"
#include "RadioActiveSource.h"
#include "TAORunData.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "globals.h"
#include <iostream>
#include <vector>
#include <string>

void TestRadioActiveSource()
{
    using namespace std;
    RadioActiveSource* testSource=new RadioActiveSource("Ge68",10,750);
    RadioActiveSource* testSource1=new RadioActiveSource("Cs137",2,-500);
    RadioActiveSource* testSource2=new RadioActiveSource("Co60",3,850);
    cout<<(*testSource)<<(*testSource1)<<(*testSource2)<<endl;
    //delete testSource;
    vector<string> fileNames=testSource->GetFileNames();
    for(int i=0;i<fileNames.size();i++){
        cout<<fileNames[i]<<endl;
    } 
}

void TestTAORunData()
{
    using namespace std;
    //Set Draw Option
    //SetGlobalDrawOption();
    TAORunData* testTAORun=new TAORunData("Ge68",10,0);
    cout<<testTAORun<<endl;
    TH1F* hist=testTAORun->GetHistOfTotalPE(true);
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    hist->Draw();
    c1->Print((ANATOP+"/result/test.pdf").c_str());
    c1->Print((ANATOP+"/result/test.pdf]").c_str());

}