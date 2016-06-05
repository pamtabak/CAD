/****************************/
/* THIS IS OPEN SOURCE CODE */
/****************************/

/* 
* File:    map-p6.h
* CVS:     $Id$
* Author:  Harald Servat
*          redcrash@gmail.com
*/

#ifndef FreeBSD_MAP_P6
#define FreeBSD_MAP_P6

enum NativeEvent_Value_P6Processor {
	PNE_P6_BACLEARS = PAPI_NATIVE_MASK,
	PNE_P6_BR_BOGUS,
	PNE_P6_BR_INST_DECODED,
	PNE_P6_BR_INST_RETIRED,
	PNE_P6_BR_MISS_PRED_RETIRED,
	PNE_P6_BR_MISS_PRED_TAKEN_RET,
	PNE_P6_BR_TAKEN_RETIRED,
	PNE_P6_BTB_MISSES,
	PNE_P6_BUS_BNR_DRV,
	PNE_P6_BUS_DATA_RCV,
	PNE_P6_BUS_DRDY_CLOCKS,
	PNE_P6_BUS_HIT_DRV,
	PNE_P6_BUS_HITM_DRV,
	PNE_P6_BUS_LOCK_CLOCKS,
	PNE_P6_BUS_REQ_OUTSTANDING,
	PNE_P6_BUS_SNOOP_STALL,
	PNE_P6_BUS_TRAN_ANY,
	PNE_P6_BUS_TRAN_BRD,
	PNE_P6_BUS_TRAN_BURST,
	PNE_P6_BUS_TRAN_DEF,
	PNE_P6_BUS_TRAN_IFETCH,
	PNE_P6_BUS_TRAN_INVAL,
	PNE_P6_BUS_TRAN_MEM,
	PNE_P6_BUS_TRAN_POWER,
	PNE_P6_BUS_TRAN_RFO,
	PNE_P6_BUS_TRANS_IO,
	PNE_P6_BUS_TRANS_P,
	PNE_P6_BUS_TRANS_WB,
	PNE_P6_CPU_CLK_UNHALTED,
	PNE_P6_CYCLES_DIV_BUSY,
	PNE_P6_CYCLES_IN_PENDING_AND_MASKED,
	PNE_P6_CYCLES_INT_MASKED,
	PNE_P6_DATA_MEM_REFS,
	PNE_P6_DCU_LINES_IN,
	PNE_P6_DCU_M_LINES_IN,
	PNE_P6_DCU_M_LINES_OUT,
	PNE_P6_DCU_MISS_OUTSTANDING,
	PNE_P6_DIV,
	PNE_P6_FLOPS,
	PNE_P6_FP_ASSIST,
	PNE_P6_FTP_COMPS_OPS_EXE,
	PNE_P6_HW_INT_RX,
	PNE_P6_IFU_FETCH,
	PNE_P6_IFU_FETCH_MISS,
	PNE_P6_IFU_MEM_STALL,
	PNE_P6_ILD_STALL,
	PNE_P6_INST_DECODED,
	PNE_P6_INST_RETIRED,
	PNE_P6_ITLB_MISS,
	PNE_P6_L2_ADS,
	PNE_P6_L2_DBUS_BUSY,
	PNE_P6_L2_DBUS_BUSY_RD,
	PNE_P6_L2_IFETCH,
	PNE_P6_L2_LD,
	PNE_P6_L2_LINES_IN,
	PNE_P6_L2_LINES_OUT,
	PNE_P6_L2M_LINES_INM,
	PNE_P6_L2M_LINES_OUTM,
	PNE_P6_L2_RQSTS,
	PNE_P6_L2_ST,
	PNE_P6_LD_BLOCKS,
	PNE_P6_MISALIGN_MEM_REF,
	PNE_P6_MUL,
	PNE_P6_PARTIAL_RAT_STALLS,
	PNE_P6_RESOURCE_STALL,
	PNE_P6_SB_DRAINS,
	PNE_P6_SEGMENT_REG_LOADS,
	PNE_P6_UOPS_RETIRED,
	PNE_P6_NATNAME_GUARD
};

extern Native_Event_LabelDescription_t P6Processor_info[];
extern hwi_search_t P6Processor_map[];

#endif
