#include <iostream>
#include "ap_int.h"
#include "utils/x_hls_utils.h"
#include<stdint.h>
#include "hls_stream.h"
#include "ap_axi_sdata.h"

void eventStreamDuplicate(ap_uint<32> config,
		hls::stream< ap_uint<16> > &xStreamIn, hls::stream< ap_uint<16> > &yStreamIn,
		hls::stream< ap_uint<64> > &tsStreamIn, hls::stream< ap_uint<1> > &polStreamIn,
		hls::stream< ap_uint<16> > &custDataStreamIn,
		hls::stream< ap_uint<16> > &xStreamOut0, hls::stream< ap_uint<16> > &yStreamOut0,
		hls::stream< ap_uint<64> > &tsStreamOut0, hls::stream< ap_uint<1> > &polStreamOut0,
		hls::stream< ap_uint<16> > &custDataStreamOut0,
		hls::stream< ap_uint<16> > &xStreamOut1, hls::stream< ap_uint<16> > &yStreamOut1,
		hls::stream< ap_uint<64> > &tsStreamOut1, hls::stream< ap_uint<1> > &polStreamOut1,
		hls::stream< ap_uint<16> > &custDataStreamOut1)
{
#pragma HLS PIPELINE
#pragma HLS INTERFACE s_axilite port=config bundle=config

#pragma HLS INTERFACE axis register both port=custDataStreamOut1
#pragma HLS INTERFACE axis register both port=polStreamOut1
#pragma HLS INTERFACE axis register both port=tsStreamOut1
#pragma HLS INTERFACE axis register both port=yStreamOut1
#pragma HLS INTERFACE axis register both port=xStreamOut1

#pragma HLS INTERFACE axis register both port=custDataStreamOut0
#pragma HLS INTERFACE axis register both port=polStreamOut0
#pragma HLS INTERFACE axis register both port=tsStreamOut0
#pragma HLS INTERFACE axis register both port=yStreamOut0
#pragma HLS INTERFACE axis register both port=xStreamOut0

#pragma HLS INTERFACE axis register both port=custDataStreamIn
#pragma HLS INTERFACE axis register both port=polStreamIn
#pragma HLS INTERFACE axis register both port=tsStreamIn
#pragma HLS INTERFACE axis register both port=yStreamIn
#pragma HLS INTERFACE axis register both port=xStreamIn

	ap_uint<16> x, y;
	ap_uint<1> pol;
	ap_uint<64> ts;
	ap_uint<16> custData;

	xStreamIn >> x;
	yStreamIn >> y;
	polStreamIn >> pol;
	tsStreamIn >> ts;
	custDataStreamIn >> custData;

	if(config.range(1, 0) == 0)
	{
		xStreamOut0 << x;
		yStreamOut0 << y;
		polStreamOut0 << pol;
		tsStreamOut0 << ts;
		custDataStreamOut0 << custData;
	}
	else if(config.range(1, 0) == 1)
	{
		xStreamOut1 << x;
		yStreamOut1 << y;
		polStreamOut1 << pol;
		tsStreamOut1 << ts;
		custDataStreamOut1 << custData;
	}
	else if(config.range(1, 0) == 2)
	{
		xStreamOut0 << x;
		yStreamOut0 << y;
		polStreamOut0 << pol;
		tsStreamOut0 << ts;
		custDataStreamOut0 << custData;

		xStreamOut1 << x;
		yStreamOut1 << y;
		polStreamOut1 << pol;
		tsStreamOut1 << ts;
		custDataStreamOut1 << custData;
	}
	else
	{
	}
}
