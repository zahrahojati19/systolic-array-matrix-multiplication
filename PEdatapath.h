#include "PrimitivePE.h"

SC_MODULE(datapath) {
    sc_in<sc_logic> clk, rst;
    sc_in<sc_logic> startPE, busyPE, startLoad;
    sc_in<sc_lv<8> > Di, Wi;
    sc_in<sc_lv<24> > Si; 
    
    sc_out<sc_lv<24> > OutputToAdd; 
    sc_out<sc_lv<8> > OutputToMult;
    sc_out<sc_logic> DonePreload, Doneload, RegRes;
    
    sc_signal<sc_lv<16> > MultResult;
    sc_signal<sc_lv<24> > SumResult;
    sc_signal<sc_lv<8> > Wi_inter;
    sc_signal<sc_lv<8> > Di_inter;

    multiplier* mult;
    Adder8* Adder;
    dRegister<8>* weight;
    dRegister<8>* input;
    dRegister<24>* result;

    SC_CTOR(datapath) {
        weight = new dRegister<8>("Wi_Register");
            (*weight) (clk, rst, startPE, Wi, DonePreload, Wi_inter);
        input = new dRegister<8>("Di_Register");
            (*input) (clk, rst, startLoad, Di, Doneload, Di_inter);
        mult = new multiplier("Multiplier");
            (*mult) (Di_inter, Wi_inter,  MultResult);
        Adder = new Adder8("Adder");
            (*Adder) (MultResult, Si, SumResult);
        result = new dRegister<24>("Result_Register");
            (*result)(clk, rst, busyPE, SumResult, RegRes, OutputToAdd);
        SC_METHOD(combinantional);
        sensitive << startPE << busyPE << startLoad;
    }
    void combinantional();
};

void datapath :: combinantional() {
    OutputToMult = Di.read();
    //cout<<Si<<","<<MultResult<<","<<SumResult<<","<<OutputToAdd<<endl;
    //cout<<OutputToMult<<endl;
}