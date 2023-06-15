#include <systemc.h>
#include <iostream>
using namespace std;

//Multiplier
SC_MODULE(multiplier) {
    sc_in<sc_lv<8> > Di, Wi;
    sc_out<sc_lv<16> > result;

    SC_CTOR(multiplier){
        SC_METHOD(multiplying);
        sensitive << Di << Wi;
    }
    void multiplying();
};
void multiplier :: multiplying() {
	sc_lv<16> vout;
	vout = Di.read().to_uint() * Wi.read().to_uint();
	result.write(vout); 
    //cout<<result<<endl;
}

//Register
template <int T> 
SC_MODULE(dRegister) {
	sc_in<sc_logic> clk, rst, cen;
	sc_in<sc_lv<T> > regin;
    sc_out<sc_logic> ready;
	sc_out<sc_lv<T> > regout;
	SC_CTOR(dRegister) {
		SC_METHOD(registering);
		sensitive << rst << clk;
	}
	void registering();
};
template <int T>
void dRegister<T>::registering() {
	sc_lv<T> tmp;
	if (rst =='1') {
		for (int i = 0; i < T; i++)
			tmp[i] = sc_logic(0);
		regout = tmp;
	}
	else if ((clk->event()) && (clk == '1')){
		if (cen == '1') {
            regout = regin;
            ready = SC_LOGIC_1;
            //cout<<regout.read()<<endl;
        }
	}
};

//Adder
SC_MODULE(Adder8) {
    sc_in<sc_lv<16> > MultProduct;
    sc_in<sc_lv<24> > Si;
    sc_out<sc_lv<24> > result;

    SC_CTOR(Adder8) {
        SC_METHOD(adding);
        sensitive << MultProduct << Si;
    }
    void adding();
};
void Adder8 :: adding() {
    sc_lv<24> vout; 
    sc_int<24> prod;
    prod.range(15,0) = MultProduct;
    prod.range(23,16) = "00000000";
    vout = prod.to_uint() + Si.read().to_uint(); 
	result.write(vout); 
    //cout<<MultProduct.read().to_uint()<<","<<prod<<","<<Si<<","<<result<<endl;
}