#include "PEdatapath.h"
#include "PEcontroller.h"

SC_MODULE(PE) {
    sc_in<sc_logic> clk, rst, START; 
	sc_in<sc_lv<8> > Wi, Di;
    sc_in<sc_lv<24> > Si;
    sc_out<sc_lv<8> > resultToMultiply;
	sc_out<sc_lv<24> >  resultToAdd;
    sc_out<sc_logic> done;

    sc_signal<sc_logic> startPE, busyPE, startLoad;
    sc_signal<sc_logic> DonePreload, Doneload, RegRes;

    datapath* DP;
    controller* CU;

    SC_CTOR(PE) {
        DP = new datapath("datapath_inst");
        (*DP) (clk, rst, startPE, busyPE, startLoad, Di, Wi, Si, resultToAdd, resultToMultiply, DonePreload, Doneload, RegRes);
        CU = new controller("controller_inst");
        (*CU) (clk, rst, START, DonePreload, Doneload, RegRes, startPE, startLoad, busyPE, done);
    }
};