#include "test.h"
#include "RadioActiveSource.h"
#include <iostream>

void TestRadioActiveSource()
{
    using namespace std;
    RadioActiveSource* testSource=new RadioActiveSource("Ge68",10,750);
    RadioActiveSource* testSource1=new RadioActiveSource("Cs137",2,-500);
    RadioActiveSource* testSource2=new RadioActiveSource("Co60",3,850);
    cout<<(*testSource)<<(*testSource1)<<(*testSource2)<<endl;
    //delete testSource;
}