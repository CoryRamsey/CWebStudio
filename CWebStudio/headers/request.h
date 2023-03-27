

struct CwebHttpRequest{
    char *raw_entrys;
    char *url;
    char *route;
    char *method;
    struct CwebDict *params;
    struct CwebDict *headers;
    int content_length;
    unsigned char *content;
    void (*interpret_first_line)(struct CwebHttpRequest *self, char *first_line);
    void (*interpret_headders)(struct CwebHttpRequest *self, struct DtwStringArray *line_headers);
    void (*free)(struct CwebHttpRequest *request);
    void (*represent)(struct CwebHttpRequest *request);
};
//algorithm functions


struct CwebHttpRequest *private_cwe_request_constructor();


struct CwebHttpRequest *private_cwe_create_http_request(char *raw_entrys);
void private_cwe_interpret_first_line(struct CwebHttpRequest *self, char *first_line);

void private_cwe_interpret_headders(
    struct CwebHttpRequest *self,
    struct DtwStringArray *line_headers
);

void private_cwe_free_http_request(struct CwebHttpRequest *self);
void private_cwe_represent_http_request(struct CwebHttpRequest *self);

