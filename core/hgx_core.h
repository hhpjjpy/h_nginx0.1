#ifndef HGX_CORE_H
#define HGX_CORE_H

typedef struct hgx_module_s      hgx_module;
typedef struct hgx_conf_s        hgx_conf;
typedef struct hgx_cycle_s       hgx_cycle;
typedef struct hgx_pool_s        hgx_pool;
typedef struct hgx_log_s         hgx_log;
typedef struct hgx_array_s       hgx_array;
typedef struct hgx_open_file_s   hgx_open_file;
typedef struct hgx_command_s     hgx_command;
typedef struct hgx_file_s        hgx_file;
typedef struct hgx_event_s       hgx_event;
typedef struct hgx_connection_s  hgx_connection;

typedef void(*hgx_event_handler_pt)(hgx_event *ev);

#define  HGX_OK		    0
#define  HGX_ERROR     -1
#define  HGX_AGAIN     -2
#define  HGX_BUSY      -3
#define  HGX_DONE      -4
#define  HGX_DECLINED  -5
#define  HGX_ABORT     -6d



#include "../base/hgx_palloc.h"




#endif