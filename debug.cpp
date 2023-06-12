#include <PA9.h>
#include "fdz.h"
#include "debug.h"

int debugMenu(){
    PA_InitText(0,0);
    PA_InitText(1,0);
    int select = 0;
    PA_OutputSimpleText(1,0,0,"B90sR debug menu.");
    while(1){
        PA_ClearTextBg(0);
        PA_OutputSimpleText(0,0,select,">");
        PA_OutputSimpleText(0,1,0,"Fever Dream Zone Act 1");
        if(Pad.Newpress.A){
            switch(select){
                case 0:
                fdz1Func();
                return 0;
                break;
            }
        }
        PA_WaitForVBL();
    }
    return 0;
}