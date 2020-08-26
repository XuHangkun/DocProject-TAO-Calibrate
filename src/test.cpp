#include "test.h"
#include "RadioActiveSource.h"
#include "MultiRadioActiveSource.h"
#include "TAORunData.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "globals.h"
#include <iostream>
#include <vector>
#include <string>
#include "TF1.h"

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

void TestMultiRadioActiveSource()
{
    using namespace std;
    std::string sources[3]={"Cs137","Ge68","Co60"};
    MultiRadioActiveSource* testSource=new MultiRadioActiveSource(sources,3,10);
    TF1* function=testSource->GetTFTotalMCShape();
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    function->Draw();
    c1->Print((ANATOP+"/result/test.pdf").c_str());
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    
}

void TestTAORunData()
{
    using namespace std;
    //Set Draw Option
    SetGlobalDrawOption();
    TAORunData* testTAORun=new TAORunData("Ge68",30,700);
    testTAORun->SetIfASBkg(true);
    cout<<testTAORun<<endl;
    TH1F* hist=testTAORun->GetHistOfTotalPE(true);
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    hist->Draw("E");
    c1->Print((ANATOP+"/result/test.pdf").c_str());
    c1->Print((ANATOP+"/result/test.pdf]").c_str());

}