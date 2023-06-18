#include <systemc.h>
#include <iostream>

SC_MODULE(controller) {
	sc_in<sc_logic> clk, rst, START, DonePreload, Doneload, RegRes;
	sc_out<sc_logic> startPE, startLoad, busyPE, done;

	enum states {ZERO, IDLE, PRELOADING, LOADING, MAC};

	sc_signal<states> ns, ps;

	SC_CTOR(controller) {
		ps.write(ZERO);
		ns.write(ZERO);

		SC_METHOD(evlCombinational);
			sensitive << DonePreload << Doneload << RegRes << ps;

		SC_METHOD(evlSequential);
			sensitive << clk << rst;
	}

	void evlCombinational();
	void evlSequential();
};

void controller::evlCombinational() {
	startPE = SC_LOGIC_0; busyPE = SC_LOGIC_0; startLoad = SC_LOGIC_0; done = SC_LOGIC_0;
	ns = IDLE;

	switch (ps.read()){
	case ZERO:
		if(START == '1') {ns = IDLE; break;}
		else {ns == ZERO; break;}
	case IDLE:
		{startPE = SC_LOGIC_1; ns = PRELOADING; break;}
	case PRELOADING:
		if (DonePreload == SC_LOGIC_1) {startLoad = SC_LOGIC_1; ns = LOADING;}
		else {startPE = SC_LOGIC_1; ns = PRELOADING;} break;
	case LOADING:
		if(Doneload == SC_LOGIC_1) {busyPE = SC_LOGIC_1; done = SC_LOGIC_1; ns = MAC;}
		else {startLoad = SC_LOGIC_1; ns = LOADING;} break;
	case MAC:
		if (RegRes == SC_LOGIC_1) {ns = IDLE;}	
		else {busyPE = SC_LOGIC_1; ns = MAC;} break;
	}
}

void controller::evlSequential() {
	if (rst == SC_LOGIC_1) ps = ZERO;
	else if (clk->event() && clk == SC_LOGIC_1){ps = ns;}
}