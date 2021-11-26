#ifndef _GLOBALS_H
#define _GLOBALS_H

//--------------------------------------------------------------------
// Include Files
#include "lrun.h"
#include "web_api.h"
#include "lrw_custom_body.h"

//--------------------------------------------------------------------
// Global Variables
int needed;
int count,SeatCount;
char *tName;
double trans_time;
double waste_time;
int status = LR_PASS;
#endif // _GLOBALS_H
end_transaction(char *tName, int status){
trans_time= lr_get_transaction_duration(tName);
waste_time= lr_get_transaction_wasted_time(tName);
lr_save_int(status,"TRANSACTION_STATUS");
lr_save_string(tName,"TRANSACTION_NAME");
lr_end_transaction(tName,status);
lr_save_int(trans_time*1000-waste_time*1000,"RESPONSE_TIME");
web_custom_request("InfluxDB",
"URL=http://localhost:8086/write?db=bd_bisiness",
"Method=POST",
"Body=business_metrics,name={TRANSACTION_NAME},status={TRANSACTION_STATUS} response_time={RESPONSE_TIME}",
LAST); }
