#include "PE_toplevel.h"

template <int PEnum>
SC_MODULE(systolic) {
    int side = sqrt(PEnum);
    sc_in<sc_logic> clk, rst;
    sc_in<sc_logic> start[PEnum];
    sc_in<sc_lv<8> > Wi[PEnum], Di[PEnum];
    sc_in<sc_lv<24> > Si[3];
	sc_out<sc_lv<24> > Output[PEnum];
    sc_out<sc_logic> busy[PEnum];

    sc_signal<sc_lv<8> > resultToMultiply[PEnum];

    PE* TOP[PEnum];
    SC_CTOR(systolic) {
        for(int i=0;i<9;i++) TOP[i] = new PE("top_instance"+i);
            (*TOP[0]) (clk, rst, start[0], Wi[0], Di[0], Si[0], resultToMultiply[0], Output[0], busy[0]);
            (*TOP[1]) (clk, rst, start[1], Wi[1], Di[1], Output[0], resultToMultiply[1], Output[1], busy[1]);
            (*TOP[2]) (clk, rst, start[2], Wi[2], Di[2], Output[1], resultToMultiply[2], Output[2], busy[2]);

            (*TOP[3]) (clk, rst, start[3], Wi[3], resultToMultiply[0], Si[1], resultToMultiply[3], Output[3], busy[3]);
            (*TOP[4]) (clk, rst, start[4], Wi[4], resultToMultiply[1], Output[3], resultToMultiply[4], Output[4], busy[4]);
            (*TOP[5]) (clk, rst, start[5], Wi[5], resultToMultiply[2], Output[4], resultToMultiply[5], Output[5], busy[5]);

            (*TOP[6]) (clk, rst, start[6], Wi[6], resultToMultiply[3], Si[2], resultToMultiply[6], Output[6], busy[6]);
            (*TOP[7]) (clk, rst, start[7], Wi[7], resultToMultiply[4], Output[6], resultToMultiply[7], Output[7], busy[7]);
            (*TOP[8]) (clk, rst, start[8], Wi[8], resultToMultiply[5], Output[7], resultToMultiply[8], Output[8], busy[8]);

        SC_METHOD(operation);
        sensitive << clk << rst;
    }
    void operation();
};
template <int PEnum>
void systolic<PEnum> :: operation() {
   for(int i=0;i<9;i++){
        //cout<<start[i]<<endl;
        //cout<<i<<":"<<Di[i%3]<<","<<Output[i]<<","<<resultToMultiply[i]<<endl;
    }
}