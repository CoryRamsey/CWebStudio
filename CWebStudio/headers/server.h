
static long long  actual_request = 0;

#define CWEB_DEFAULT_TIMEOUT 30
#define CWEB_DEFAULT_MAX_BODY 10485760
#define CWEB_DEFAULT_MAX_QUEUE 100
#define CWEB_DANGEROUS_SINGLE_PROCESS true
#define CWEB_SAFTY_MODE false



void  private_cweb_execute_request(
    int socket,
    struct CwebHttpResponse*(*request_handler)( struct CwebHttpRequest *request)
);

void private_cweb_send_error_mensage( const char*mensage,int status_code, int socket);


void private_cweb_treat_response(int new_socket);

void private_cweb_run_server_in_multiprocess(
    int port,
    struct CwebHttpResponse *(*request_handler)(struct CwebHttpRequest *request),
    int timeout,
    int max_process,
    int max_queue
);

void private_cweb_execute_request_in_safty_mode(
    int new_socket,
    int time_out,
    struct CwebHttpResponse *(*request_handler)(struct CwebHttpRequest *request)
);




void private_cweb_run_server_in_single_process(
    int port,
    struct CwebHttpResponse *(*request_handler)(struct CwebHttpRequest *request),
    int timeout,
    int max_queue
);



void cweb_run_server(
    int port,
    struct CwebHttpResponse *(*request_handler)(struct CwebHttpRequest *request),
    int timeout,
    int max_queue,
    bool single_process
    );
