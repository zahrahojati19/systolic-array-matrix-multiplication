#include <systemc.h>
#include <iostream>

template <int PEnum>
SC_MODULE(CU) {
    sc_in<sc_logic> clk, rst, done[PEnum];
	sc_out<sc_logic> start[PEnum], FIN;
    
    enum states {IDLE, LOAD0, LOAD1, LOAD2, LOAD3, LOAD4, LOAD5, DONE};
    sc_signal<states> ns, ps;

    SC_CTOR(CU) {
        ps.write(IDLE);
        ns.write(IDLE);

		SC_METHOD(evlCombinational);
			sensitive << ps << done[0] << done[1] << done[2] << done[3] << done[4] << done[5] << done[6]  << done[7]  << done[8];

		SC_METHOD(evlSequential);
			sensitive << clk << rst;
	}

	void evlCombinational();
	void evlSequential();
};

template <int PEnum>
void CU<PEnum>::evlCombinational() {
	FIN = SC_LOGIC_0;
	ns = IDLE;

	switch (ps.read()){
	case IDLE:
		{start[0] = SC_LOGIC_1; ns = LOAD0; break;}
	case LOAD0:
		if (done[0] == SC_LOGIC_1) {
			start[0] = SC_LOGIC_1; start[1] = SC_LOGIC_1; start[3] = SC_LOGIC_1; ns = LOAD1; break;
		}
		else {start[0] = SC_LOGIC_1; ns = LOAD0;break;} 
	case LOAD1:
		if (done[3] == SC_LOGIC_1) {
			start[0] = SC_LOGIC_1; start[1] = SC_LOGIC_1; start[3] = SC_LOGIC_1;
			start[2] = SC_LOGIC_1; start[4] = SC_LOGIC_1; start[6] = SC_LOGIC_1; ns = LOAD2; break;
		}
		else {start[0] = SC_LOGIC_1; start[1] = SC_LOGIC_1; start[3] = SC_LOGIC_1; ns = LOAD1; break;} 
	case LOAD2:
		if (done[6] == SC_LOGIC_1) {
			start[1] = SC_LOGIC_1; start[3] = SC_LOGIC_1;
			start[2] = SC_LOGIC_1; start[4] = SC_LOGIC_1; start[6] = SC_LOGIC_1;
			start[7] = SC_LOGIC_1; start[5] = SC_LOGIC_1; ns = LOAD3; break;
		}
		else {
			start[0] = SC_LOGIC_1; start[1] = SC_LOGIC_1; start[3] = SC_LOGIC_1;
			start[2] = SC_LOGIC_1; start[4] = SC_LOGIC_1; start[6] = SC_LOGIC_1; ns = LOAD2; break;
		} 
	case LOAD3:
		if (done[7] == SC_LOGIC_1) {
			start[2] = SC_LOGIC_1; start[4] = SC_LOGIC_1; start[6] = SC_LOGIC_1;
			start[7] = SC_LOGIC_1; start[5] = SC_LOGIC_1; start[8] = SC_LOGIC_1; ns = LOAD4; break;
		}
		else {
			start[1] = SC_LOGIC_1; start[3] = SC_LOGIC_1;
			start[2] = SC_LOGIC_1; start[4] = SC_LOGIC_1; start[6] = SC_LOGIC_1;
			start[7] = SC_LOGIC_1; start[5] = SC_LOGIC_1; ns = LOAD3; break;}
	case LOAD4:
		if (done[8] == SC_LOGIC_1) {
			start[7] = SC_LOGIC_1; start[5] = SC_LOGIC_1; start[8] = SC_LOGIC_1; ns = LOAD5; break;
		}
		else {
			start[2] = SC_LOGIC_1; start[4] = SC_LOGIC_1; start[6] = SC_LOGIC_1;
			start[7] = SC_LOGIC_1; start[5] = SC_LOGIC_1; start[8] = SC_LOGIC_1;  ns = LOAD4; break;}
	case LOAD5:
		if (done[8] == SC_LOGIC_1) {
			start[8] = SC_LOGIC_1; ns = DONE; break;
		}
		else {
			start[7] = SC_LOGIC_1; start[5] = SC_LOGIC_1; start[8] = SC_LOGIC_1; ns = LOAD5; break;}
	case DONE:
		{cout<<"done"<<endl; FIN = SC_LOGIC_1; break;}
	}
}

template <int PEnum>
void CU<PEnum>::evlSequential() {
	if (rst == SC_LOGIC_1) ps = IDLE;
	else if (clk->event() && clk == SC_LOGIC_1){ ps = ns;}
}