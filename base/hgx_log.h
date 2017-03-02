#ifndef  HGX_LOG_H
#define  HGX_LOG_H

typedef struct hgx_log_s hgx_log;

struct hgx_logs{
	int log_fd;
	void *date;
};

hgx_log* hgx_log_init_stderr();

hgx_log* hgx_log_create_errlog();
char *ngx_set_error_log_levels();



#endif