#include "PE_toplevel.h"

SC_MODULE(PETB) {
 
	sc_signal<sc_logic> clk, rst, START, done;
	sc_signal<sc_lv<8> > Wi, Di;
	sc_signal<sc_lv<24> > Si;
	sc_signal<sc_lv<8> > resultToMultiply;
	sc_signal<sc_lv<24> > resultToAdd;

	PE* PE1;

	SC_CTOR(PETB){
		PE1 = new PE("PE_TB");
			(*PE1) (clk, rst, START, Wi, Di, Si, resultToMultiply, resultToAdd, done);
		SC_THREAD(clockGeneration);
		SC_THREAD(resetAssertion);
		SC_THREAD(inWaveform);
		SC_METHOD(displaying);
		sensitive << done.posedge_event();
	}
	void clockGeneration();
	void resetAssertion();
	void inWaveform();
	void displaying();
};

void PETB::clockGeneration() {
	while (true) {
		wait(5, SC_PS);
		clk = SC_LOGIC_0;
		wait(5, SC_PS);
		clk = SC_LOGIC_1;
	}
}
void PETB::resetAssertion() {
	while (true) {
		wait(0, SC_PS);
		rst = SC_LOGIC_0;
		wait(5, SC_PS);
		rst = SC_LOGIC_1;
		wait(5, SC_PS);
		rst = SC_LOGIC_0;
		wait();
	}
}
void PETB::inWaveform() {
	while (true) {
			START = SC_LOGIC_1;
			Wi = "11111111";
			Di = "11100011";
			Si = "000000110000000010000001";
		wait(15, SC_PS);
			START = SC_LOGIC_1;
			Di = "11111000";
			Wi = "11010111";
			Si = "001100000000000010000001";
		wait(20, SC_PS);
			START = SC_LOGIC_1;
			Wi = "11000111";
			Di = "10100011";
			Si = "000000000000000000000000";
		wait(20, SC_PS);
			START = SC_LOGIC_1;
			Wi = "11110001";
			Di = "10010011";
		wait(20, SC_PS);
			START = SC_LOGIC_0;
			Wi = "00111101";
			Di = "10111101";
		wait();
	}
}

void PETB::displaying(){
	cout << " result To Add = " << resultToAdd.read() << ", result To Multiply = " << resultToMultiply.read() <<endl; 
}