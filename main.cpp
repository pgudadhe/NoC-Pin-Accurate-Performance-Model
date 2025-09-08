// main.cpp
#include "systemc.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "source.h"
#include "sink.h"
#include "router.h"

using namespace std;

int sc_main(int argc, char *argv[])
{
	sc_signal<packet> 	sig_source[16];
	sc_signal<packet> 	sig_input[16];
	sc_signal<packet> 	sig_zero[64];
	sc_signal<packet> 	sig_sink[16];
	sc_signal<packet> 	sig_output[64];

	sc_signal<bool> sig_ack_src[64], sig_ack_out[64];
	sc_signal<bool> sig_ack_sink[16], sig_ack_in[64];
	sc_signal<bool> sig_ack_zero[64];

	sc_signal<sc_uint<4>> src_id[16];
	sc_signal<sc_uint<4>> snk_id[16];
	sc_signal<sc_uint<4>> id[16];
	sc_signal<int> chk_dest_node;
	sc_signal<sc_uint<4>> chk_src_node;
	sc_signal<packet> sigoutput[16];
	int src_node, dest_node, sim_duration;
	sc_clock s_clock("S_CLOCK", 21, SC_NS); // source clock
	sc_clock r_clock("R_CLOCK", 3, SC_NS); // router clock
	sc_clock d_clock("D_CLOCK", 3, SC_NS); // destination clock

	source * sources[16];
	sink * sinks[16];
	//router * routers[16];

	for(int src = 0; src < 16; src++) 
	{
		string src_name = "source" + to_string(src);
		sources[src] = new source(sc_gen_unique_name(src_name.c_str()));
		sources[src]->packet_out(sig_source[src]);
		sources[src]->source_id(src_id[src]);
		sources[src]->ach_in(sig_ack_src[src]);
		sources[src]->CLK(s_clock);
		sources[src]->d_est(chk_dest_node);
		sources[src]->ch_k(chk_src_node);

		string sink_name = "sink" + to_string(src);
		sinks[src] = new sink(sc_gen_unique_name(sink_name.c_str()));
		sinks[src]->packet_in(sig_sink[src]);
		sinks[src]->ack_out(sig_ack_sink[src]);
		sinks[src]->sink_id(snk_id[src]);
		sinks[src]->sclk(d_clock);
		sinks[src]->packet_out_sink(sigoutput[src]);
	}



	router router0("router0");
	router0.in0(sig_source[0]);
	router0.in1(sig_output[2]);
	router0.in2(sig_output[12]);
	router0.in3(sig_zero[1]);
	router0.in4(sig_zero[2]);

	router0.router_id(id[0]);
	
	router0.out0(sig_sink[0]);
	router0.out2(sig_output[0]);
	router0.out3(sig_output[1]);
	router0.out1(sig_zero[3]);
	router0.out4(sig_zero[4]);

	router0.inack0(sig_ack_sink[0]);
	router0.inack1(sig_ack_in[2]);
	router0.inack2(sig_ack_in[12]);
	router0.inack3(sig_ack_zero[1]);
	router0.inack4(sig_ack_zero[2]);

	router0.outack0(sig_ack_src[0]);
	router0.outack2(sig_ack_in[0]);
	router0.outack3(sig_ack_in[1]);
	router0.outack1(sig_ack_zero[3]);
	router0.outack4(sig_ack_zero[4]);

	router0.rclk(r_clock);

	router router1("router1");
	router1.in0(sig_source[1]);
	router1.in1(sig_output[0]);
	router1.in2(sig_output[7]);
	router1.in3(sig_output[16]);
	router1.in4(sig_zero[5]);

	router1.router_id(id[1]);
	
	router1.out0(sig_sink[1]);
	router1.out4(sig_output[2]);
	router1.out3(sig_output[3]);
	router1.out2(sig_output[4]);
	router1.out1(sig_zero[6]);

	router1.inack0(sig_ack_sink[1]);
	router1.inack1(sig_ack_in[0]);
	router1.inack2(sig_ack_in[7]);
	router1.inack3(sig_ack_in[16]);
	router1.inack4(sig_ack_zero[5]);

	router1.outack0(sig_ack_src[1]);
	router1.outack4(sig_ack_in[2]);
	router1.outack3(sig_ack_in[3]);
	router1.outack2(sig_ack_in[4]);
	router1.outack1(sig_ack_zero[6]);

	router1.rclk(r_clock);
	
	router router2("router2");
	
	router2.in0(sig_source[2]);
	router2.in1(sig_output[4]);
	router2.in2(sig_output[9]);
	router2.in3(sig_output[17]);
	router2.in4(sig_zero[7]);

	router2.router_id(id[2]);
	
	router2.out0(sig_sink[2]);
	router2.out1(sig_zero[19]);
	router2.out2(sig_output[5]);
	router2.out3(sig_output[6]);
	router2.out4(sig_output[7]);

	router2.inack0(sig_ack_sink[2]);
	router2.inack1(sig_ack_in[4]);
	router2.inack2(sig_ack_in[9]);
	router2.inack3(sig_ack_in[17]);
	router2.inack4(sig_ack_zero[7]);

	router2.outack0(sig_ack_src[2]);
	router2.outack1(sig_ack_zero[19]);
	router2.outack2(sig_ack_in[5]);
	router2.outack3(sig_ack_in[6]);
	router2.outack4(sig_ack_in[7]);

	router2.rclk(r_clock);

	router router3("router3");
	
	router3.in0(sig_source[3]);
	router3.in1(sig_output[5]);
	router3.in2(sig_output[21]);
	router3.in3(sig_zero[8]);
	router3.in4(sig_zero[9]);

	router3.router_id(id[3]);
	
	router3.out0(sig_sink[3]);
	router3.out3(sig_output[8]);
	router3.out4(sig_output[9]);
	router3.out2(sig_zero[20]);
	router3.out1(sig_zero[21]);

	router3.inack0(sig_ack_sink[3]);
	router3.inack1(sig_ack_in[5]);
	router3.inack2(sig_ack_in[21]);
	router3.inack3(sig_ack_zero[8]);
	router3.inack4(sig_ack_zero[9]);

	router3.outack0(sig_ack_src[3]);
	router3.outack3(sig_ack_in[8]);
	router3.outack4(sig_ack_in[9]);
	router3.outack2(sig_ack_zero[20]);
	router3.outack1(sig_ack_zero[21]);

	router3.rclk(r_clock);

	router router4("router4");
	router4.in0(sig_source[4]);
	router4.in1(sig_output[1]);
	router4.in2(sig_output[13]);
	router4.in3(sig_output[26]);
	router4.in4(sig_zero[10]);

	router4.router_id(id[4]);
	
	router4.out0(sig_sink[4]);
	router4.out2(sig_output[10]);
	router4.out3(sig_output[11]);
	router4.out1(sig_output[12]);
	router4.out4(sig_zero[22]);

	router4.inack0(sig_ack_sink[4]);
	router4.inack1(sig_ack_in[1]);
	router4.inack2(sig_ack_in[13]);
	router4.inack3(sig_ack_in[26]);
	router4.inack4(sig_ack_zero[10]);

	router4.outack0(sig_ack_src[4]);
	router4.outack2(sig_ack_in[10]);
	router4.outack3(sig_ack_in[11]);
	router4.outack1(sig_ack_in[12]);
	router4.outack4(sig_ack_zero[22]);

	router4.rclk(r_clock);

	router router5("router5");
	
	router5.in0(sig_source[5]);
	router5.in1(sig_output[3]);
	router5.in2(sig_output[10]);
	router5.in3(sig_output[20]);
	router5.in4(sig_output[30]);

	router5.router_id(id[5]);
	
	router5.out0(sig_sink[5]);
	router5.out4(sig_output[13]);
	router5.out3(sig_output[14]);
	router5.out2(sig_output[15]);
	router5.out1(sig_output[16]);

	router5.inack0(sig_ack_sink[5]);
	router5.inack1(sig_ack_in[3]);
	router5.inack2(sig_ack_in[10]);
	router5.inack3(sig_ack_in[20]);
	router5.inack4(sig_ack_in[30]);

	router5.outack0(sig_ack_src[5]);
	router5.outack4(sig_ack_in[13]);
	router5.outack3(sig_ack_in[14]);
	router5.outack2(sig_ack_in[15]);
	router5.outack1(sig_ack_in[16]);

	router5.rclk(r_clock);
	
	router router6("router6");
	
	router6.in0(sig_source[6]);
	router6.in1(sig_output[6]);
	router6.in2(sig_output[15]);
	router6.in3(sig_output[22]);
	router6.in4(sig_output[31]);

	router6.router_id(id[6]);
	
	router6.out0(sig_sink[6]);
	router6.out1(sig_output[17]);
	router6.out2(sig_output[18]);
	router6.out3(sig_output[19]);
	router6.out4(sig_output[20]);

	router6.inack0(sig_ack_sink[6]);
	router6.inack1(sig_ack_in[6]);
	router6.inack2(sig_ack_in[15]);
	router6.inack3(sig_ack_in[22]);
	router6.inack4(sig_ack_in[31]);

	router6.outack0(sig_ack_src[6]);
	router6.outack1(sig_ack_in[17]);
	router6.outack2(sig_ack_in[18]);
	router6.outack3(sig_ack_in[19]);
	router6.outack4(sig_ack_in[20]);

	router6.rclk(r_clock);

	router router7("router7");
	
	router7.in0(sig_source[7]);
	router7.in1(sig_output[8]);
	router7.in2(sig_output[18]);
	router7.in3(sig_output[35]);
	router7.in4(sig_zero[11]);

	router7.router_id(id[7]);
	
	router7.out0(sig_sink[7]);
	router7.out1(sig_output[21]);
	router7.out4(sig_output[22]);
	router7.out3(sig_output[23]);
	router7.out2(sig_zero[23]);

	router7.inack0(sig_ack_sink[7]);
	router7.inack1(sig_ack_in[8]);
	router7.inack2(sig_ack_in[18]);
	router7.inack3(sig_ack_in[35]);
	router7.inack4(sig_ack_zero[11]);

	router7.outack0(sig_ack_src[7]);
	router7.outack1(sig_ack_in[21]);
	router7.outack4(sig_ack_in[22]);
	router7.outack3(sig_ack_in[23]);
	router7.outack2(sig_ack_zero[23]);

	router7.rclk(r_clock);

	router router8("router8");
	
	router8.in0(sig_source[8]);
	router8.in1(sig_output[11]);
	router8.in2(sig_output[27]);
	router8.in3(sig_output[38]);
	router8.in4(sig_zero[12]);

	router8.router_id(id[8]);
	
	router8.out0(sig_sink[8]);
	router8.out2(sig_output[24]);
	router8.out3(sig_output[25]);
	router8.out1(sig_output[26]);
	router8.out4(sig_zero[24]);

	router8.inack0(sig_ack_sink[8]);
	router8.inack1(sig_ack_in[11]);
	router8.inack2(sig_ack_in[27]);
	router8.inack3(sig_ack_in[38]);
	router8.inack4(sig_ack_zero[12]);

	router8.outack0(sig_ack_src[8]);
	router8.outack2(sig_ack_in[24]);
	router8.outack3(sig_ack_in[25]);
	router8.outack1(sig_ack_in[26]);
	router8.outack4(sig_ack_zero[24]);

	router8.rclk(r_clock);

	router router9("router9");
	
	router9.in0(sig_source[9]);
	router9.in1(sig_output[14]);
	router9.in2(sig_output[24]);
	router9.in3(sig_output[34]);
	router9.in4(sig_output[41]);

	router9.router_id(id[9]);
	
	router9.out0(sig_sink[9]);
	router9.out4(sig_output[27]);
	router9.out3(sig_output[28]);
	router9.out2(sig_output[29]);
	router9.out1(sig_output[30]);

	router9.inack0(sig_ack_sink[9]);
	router9.inack1(sig_ack_in[14]);
	router9.inack2(sig_ack_in[24]);
	router9.inack3(sig_ack_in[34]);
	router9.inack4(sig_ack_in[41]);

	router9.outack0(sig_ack_src[9]);
	router9.outack4(sig_ack_in[27]);
	router9.outack3(sig_ack_in[28]);
	router9.outack2(sig_ack_in[29]);
	router9.outack1(sig_ack_in[30]);

	router9.rclk(r_clock);
	
	router router10("router10");
	
	router10.in0(sig_source[10]);
	router10.in1(sig_output[19]);
	router10.in2(sig_output[29]);
	router10.in3(sig_output[36]);
	router10.in4(sig_output[43]);

	router10.router_id(id[10]);
	
	router10.out0(sig_sink[10]);
	router10.out1(sig_output[31]);
	router10.out2(sig_output[32]);
	router10.out3(sig_output[33]);
	router10.out4(sig_output[34]);

	router10.inack0(sig_ack_sink[10]);
	router10.inack1(sig_ack_in[19]);
	router10.inack2(sig_ack_in[29]);
	router10.inack3(sig_ack_in[36]);
	router10.inack4(sig_ack_in[43]);

	router10.outack0(sig_ack_src[10]);
	router10.outack1(sig_ack_in[31]);
	router10.outack2(sig_ack_in[32]);
	router10.outack3(sig_ack_in[33]);
	router10.outack4(sig_ack_in[34]);

	router10.rclk(r_clock);

	router router11("router11");
	
	router11.in0(sig_source[11]);
	router11.in1(sig_output[23]);
	router11.in2(sig_output[32]);
	router11.in3(sig_output[46]);
	router11.in4(sig_zero[13]);

	router11.router_id(id[11]);
	
	router11.out0(sig_sink[11]);
	router11.out1(sig_output[35]);
	router11.out4(sig_output[36]);
	router11.out3(sig_output[37]);
	router11.out2(sig_zero[25]);

	router11.inack0(sig_ack_sink[11]);
	router11.inack1(sig_ack_in[23]);
	router11.inack2(sig_ack_in[32]);
	router11.inack3(sig_ack_in[46]);
	router11.inack4(sig_ack_zero[13]);

	router11.outack0(sig_ack_src[11]);
	router11.outack1(sig_ack_in[35]);
	router11.outack4(sig_ack_in[36]);
	router11.outack3(sig_ack_in[37]);
	router11.outack2(sig_ack_zero[25]);

	router11.rclk(r_clock);

	router router12("router12");
	
	router12.in0(sig_source[12]);
	router12.in1(sig_output[25]);
	router12.in2(sig_output[40]);
	router12.in3(sig_zero[14]);
	router12.in4(sig_zero[15]);

	router12.router_id(id[12]);
	
	router12.out0(sig_sink[12]);
	router12.out1(sig_output[38]);
	router12.out2(sig_output[39]);
	router12.out3(sig_zero[26]);
	router12.out4(sig_zero[27]);

	router12.inack0(sig_ack_sink[12]);
	router12.inack1(sig_ack_in[25]);
	router12.inack2(sig_ack_in[40]);
	router12.inack3(sig_ack_zero[14]);
	router12.inack4(sig_ack_zero[15]);

	router12.outack0(sig_ack_src[12]);
	router12.outack1(sig_ack_in[38]);
	router12.outack2(sig_ack_in[39]);
	router12.outack3(sig_ack_zero[26]);
	router12.outack4(sig_ack_zero[27]);

	router12.rclk(r_clock);

	router router13("router13");
	
	router13.in0(sig_source[13]);
	router13.in1(sig_output[28]);
	router13.in2(sig_output[39]);
	router13.in3(sig_output[45]);
	router13.in4(sig_zero[16]);

	router13.router_id(id[13]);
	
	router13.out0(sig_sink[13]);
	router13.out4(sig_output[40]);
	router13.out1(sig_output[41]);
	router13.out2(sig_output[42]);
	router13.out3(sig_zero[28]);

	router13.inack0(sig_ack_sink[13]);
	router13.inack1(sig_ack_in[28]);
	router13.inack2(sig_ack_in[39]);
	router13.inack3(sig_ack_in[45]);
	router13.inack4(sig_ack_zero[16]);

	router13.outack0(sig_ack_src[13]);
	router13.outack4(sig_ack_in[40]);
	router13.outack1(sig_ack_in[41]);
	router13.outack2(sig_ack_in[42]);
	router13.outack3(sig_ack_zero[28]);

	router13.rclk(r_clock);
	
	router router14("router14");
	
	router14.in0(sig_source[14]);
	router14.in1(sig_output[33]);
	router14.in2(sig_output[42]);
	router14.in3(sig_output[47]);
	router14.in4(sig_zero[17]);

	router14.router_id(id[14]);
	
	router14.out0(sig_sink[14]);
	router14.out1(sig_output[43]);
	router14.out2(sig_output[44]);
	router14.out4(sig_output[45]);
	router14.out3(sig_zero[29]);

	router14.inack0(sig_ack_sink[14]);
	router14.inack1(sig_ack_in[33]);
	router14.inack2(sig_ack_in[42]);
	router14.inack3(sig_ack_in[47]);
	router14.inack4(sig_ack_zero[17]);

	router14.outack0(sig_ack_src[14]);
	router14.outack1(sig_ack_in[43]);
	router14.outack2(sig_ack_in[44]);
	router14.outack4(sig_ack_in[45]);
	router14.outack3(sig_ack_zero[29]);

	router14.rclk(r_clock);

	router router15("router15");
	
	router15.in0(sig_source[15]);
	router15.in1(sig_output[37]);
	router15.in2(sig_output[44]);
	router15.in3(sig_zero[18]);
	router15.in4(sig_zero[19]);

	router15.router_id(id[15]);
	
	router15.out0(sig_sink[15]);
	router15.out1(sig_output[46]);
	router15.out4(sig_output[47]);
	router15.out2(sig_zero[30]);
	router15.out3(sig_zero[31]);

	router15.inack0(sig_ack_sink[15]);
	router15.inack1(sig_ack_in[37]);
	router15.inack2(sig_ack_in[44]);
	router15.inack3(sig_ack_zero[18]);
	router15.inack4(sig_ack_zero[19]);

	router15.outack0(sig_ack_src[15]);
	router15.outack1(sig_ack_in[46]);
	router15.outack4(sig_ack_in[47]);
	router15.outack2(sig_ack_zero[30]);
	router15.outack3(sig_ack_zero[31]);

	router15.rclk(r_clock);

	//  trace file
	sc_trace_file *tf = sc_create_vcd_trace_file("graph");
	// External Signals
	sc_trace(tf, s_clock, "s_clock");
	sc_trace(tf, d_clock, "d_clock");
	sc_trace(tf, r_clock, "r_clock");

	for(int idx = 0; idx < 16; idx++) 
	{
		id[idx].write(idx);
		src_id[idx].write(idx);
		snk_id[idx].write(idx);

		string source_id_str = "sig_source[" + to_string(idx) + "]";
		sc_trace(tf, sig_source[idx], source_id_str.c_str());

		string sink_id_str = "sig_sink[" + to_string(idx) + "]";
		sc_trace(tf, sig_sink[0], sink_id_str.c_str());
	}


	cout << "Enter source node [0:15]: ";
	cin >> src_node;
	cout << "Enter Destination node [0:15]: ";
	cin >> dest_node;
	cout << "Enter simulation duration [in nanoseconds. 1000ns for 47 packets]: ";
	cin >> sim_duration;

	chk_dest_node.write(dest_node);
	chk_src_node.write(src_node);

	cout << endl;
	cout << "---------------------------------------------------" << endl;
	cout << endl
		 << " NoC Perf Model: 4X4 Mesh Topology Pin-Accurate " << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "There are 16 nodes (arranged in 4x4 mesh) and each node has a 5x5 Wormhole router.  " << endl;

	sc_start(sim_duration, SC_NS); 

	sc_close_vcd_trace_file(tf);

	cout << "---------------------------------------------------" << endl;
	cout << "Simulation ended..." << endl;


	cout << "Total Tx: " << sources[src_node]->pkt_snt << endl;

	cout << "Total Rx: " << sinks[dest_node]->pkt_recv << endl;


	// Deleting all dynamically allocated modules
	for(int src = 0; src < 16; src++) 
	{
		//cout << "Deleting node# " << src << endl;
		delete sources[src];
		delete sinks[src];
		//delete routers[src];
	}

	return 0;
}
