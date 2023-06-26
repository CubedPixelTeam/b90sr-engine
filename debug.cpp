#include <PA9.h>
#include "fdz.h"
#include "debug.h"

int debugMenu(){
    u8 select = 0;
    while(1){
        select += Pad.Newpress.Down - Pad.Newpress.Up;
        PA_ClearTextBg(1);
        PA_OutputSimpleText(1,0,select,">");
        PA_OutputSimpleText(1,1,0,"fdz1");
        PA_OutputSimpleText(1,1,1,"fdz2");
        if(Pad.Newpress.A){
            switch(select){
                case 0:
                fdz1Func();
                return 0;
                break;
                case 1:
                fdz2Func();
                return 0;
                break;
            }
        }
        PA_WaitForVBL();
    }
    return 0;
}