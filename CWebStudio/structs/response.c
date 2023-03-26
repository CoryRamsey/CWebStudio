

struct CwebHttpResponse *create_http_response(){
    struct CwebHttpResponse *self = (struct CwebHttpResponse *)malloc(
        sizeof(struct CwebHttpResponse)
    );
    self->status_code = 200;
    self->headers = cweb_create_dict();
    self->content_length = 0;
    self->exist_content = false;
    self->content = NULL;
    self->free = private_cweb_http_response_free;
    self->set_content = private_cweb_http_set_content;
    self->generate_response = private_cweb_generate_response;
    self->add_header = private_cweb_http_add_header;
    return self;
}

char *private_cweb_generate_response(struct CwebHttpResponse*self){
    char *response_string = (char*)malloc(1000);
    sprintf(response_string, "HTTP/1.1 %d OK\r", self->status_code);
    struct CwebDict *headers = self->headers;

    sprintf(response_string, "%s\r\nContent-Length: %d\r\n", response_string, self->content_length);
    
    for(int i = 0; i < headers->size; i++){
        struct CwebKeyVal *key_val = headers->keys_vals[i];
        char *key = key_val->key;
        char *value = key_val->value;
        sprintf(response_string, "%s\r%s: %s\r\n", response_string, key, value);
    }
    sprintf(response_string, "%s\r\n", response_string);
        
    return response_string;
}

void private_cweb_http_response_free(struct CwebHttpResponse *self){
    self->headers->free(self->headers);
    free(self->content);
    free(self);
}

void private_cweb_http_set_content(struct CwebHttpResponse *self, unsigned char *content,int content_length){
    self->content = (unsigned char*)malloc(content_length);
    memcpy(self->content, content, content_length);
    self->exist_content = true;
    self->content_length = content_length;
}

void private_cweb_http_add_header(struct CwebHttpResponse *self,const char *key,const  char *value){
    self->headers->set(self->headers, key, value);
}