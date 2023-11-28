#include "state.h"
#include "dataTest.h"

State m1_start = {
    {
    {0,0,0,0},
    {3,1,2,3},
    {3,4,5,6},
    {3,7,8,9}
    }
};

State m1_end = {
    {
    {3,6,3,9},
    {2,1,2,0},
    {2,4,5,0},
    {2,7,8,0}
    }
};

State m2_start= {
    {
    {3,1,5,9},
    {2,2,6,0},
    {2,3,7,0},
    {2,4,8,0}
    }
};

State m2_end = {
    {
    {3,6,1,7},
    {2,2,8,0},
    {1,3,0,0},
    {3,4,9,5}
    }
};



State m3_start = {
    {
    {3,1,2,3},
    {3,4,5,6},
    {3,7,8,9},
    {0,0,0,0}
    }
};  

State m3_end = {
    {
    {3,8,1,7},
    {2,2,6,0},
    {2,3,5,0},
    {2,4,9,0}
    }
};


State m4_start = {
    {
    {3,7,8,9},
    {3,6,5,4},
    {2,2,3,0},
    {1,1,0,0}
    }
};  

State m4_end = {
    {
    {3,1,2,3},
    {3,4,5,6},
    {0,0,0,0},
    {3,7,8,9}
    }
};

int stateToCopy[4][4];



void getEtatTest(int id, State *ed, State *ef){
    switch (id)
    {
    case 1:
        *ed = m1_start;
        *ef = m1_end;
        break;
    case 2:
        *ed = m2_start;
        *ef = m2_end;
        break;
    case 3:
        *ed = m3_start;
        *ef = m3_end;
        break;
    case 4:
        *ed = m4_start;
        *ef = m4_end;
        break;
    default:
        break;
    }
 }


 
