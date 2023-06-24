#include "PEtestbench.h"

int sc_main (int argc , char *argv[])
{
	PETB* TOP = new PETB("PETB_Instance");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("Exponential");
	sc_trace(VCDFile, TOP->clk, "clk");
	sc_trace(VCDFile, TOP->rst, "rst");
	sc_trace(VCDFile, TOP->START, "START");
    sc_trace(VCDFile, TOP->Wi, "Wi");
    sc_trace(VCDFile, TOP->Di, "Di");
	sc_trace(VCDFile, TOP->Si, "Si");
	sc_trace(VCDFile, TOP->resultToAdd, "resultToAdd");
	sc_trace(VCDFile, TOP->resultToMultiply, "resultToMultiply");
	sc_trace(VCDFile, TOP->done, "done");
    sc_start(200, SC_PS);
    return 0;
}
