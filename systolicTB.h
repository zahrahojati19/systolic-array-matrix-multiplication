#include "systolic.h"
#include "systolicCU.h"

SC_MODULE(systolicTB){
    sc_signal<sc_logic> clk, rst, done;
    sc_signal<sc_lv<8> > Win[9], Din[9];
	sc_signal<sc_lv<24> > Output[9], Si[3];
	sc_signal<sc_logic> busy[9], start[9];

    systolic<9>* array;
	CU<9>* systolicCU;
    SC_CTOR(systolicTB) {
        array = new systolic<9>("systolic_array_instance");
            (*array) (clk, rst,
			start[0], start[1], start[2], start[3], start[4], start[5], start[6], start[7], start[8],
			Win[0], Win[1], Win[2], Win[3], Win[4], Win[5], Win[6], Win[7], Win[8], 
			Din[0], Din[1], Din[2], Din[3], Din[4], Din[5], Din[6], Din[7], Din[8],
			Si[0], Si[1], Si[2],
			Output[0], Output[1], Output[2], Output[3], Output[4], Output[5], Output[6], Output[7], Output[8],
			busy[0], busy[1], busy[2], busy[3], busy[4], busy[5], busy[6], busy[7], busy[8]);
		
		systolicCU = new CU<9>("Controller_Inst");
		(*systolicCU) (clk, rst, busy[0], busy[1], busy[2], busy[3], busy[4], busy[5], busy[6], busy[7], busy[8],
			start[0], start[1], start[2], start[3], start[4], start[5], start[6], start[7], start[8], done);

        SC_THREAD(resetting);
		SC_THREAD(clocking);
		SC_THREAD(inGenerating);
		SC_THREAD(displaying);
		sensitive << done;
    }
    void resetting();
	void clocking();
	void inGenerating();
	void displaying();
};
void systolicTB::resetting() {
	while (true) {
		wait(5, SC_PS);
		rst = SC_LOGIC_0;
		wait(5, SC_PS);
		rst = SC_LOGIC_1;
		wait(10, SC_PS);
		rst = SC_LOGIC_0;
		wait();
	}
}

void systolicTB::clocking() {
	while (true) {
		wait(5, SC_PS);
		clk = SC_LOGIC_0;
		wait(5, SC_PS);
		clk = SC_LOGIC_1;
	}
}

void systolicTB::inGenerating() {
	while (true) {
		Si[0] = "000000000000000000000000";
		Si[1] = "000000000000000000000000";
		Si[2] = "000000000000000000000000";
		Din[0] = "00110000";Din[1] = "00110000";Din[2] = "00110000";
		Win[0] = "00111110";Win[1] = "00111110";Win[2] = "00111110";
		wait(clk.posedge_event());
		Din[0] = "00110000";Din[1] = "00110000";Din[2] = "00110000";
		Win[0] = "00111110";Win[1] = "00111110";Win[2] = "00111110";
		wait(clk.posedge_event());
		Din[0] = "00110000";Din[1] = "00110000";Din[2] = "00110110";
		Win[0] = "00111110";Win[1] = "00111110";Win[2] = "11111110";
		wait(60, SC_PS);
		wait();
	}
}

void systolicTB::displaying(){
    while (true) {
		for(int i = 0; i<9; i++)
			cout << " output" << i << " = " << Output[i] << " - Time : " << sc_time_stamp() << endl;
		wait();
	}
}