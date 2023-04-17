#define CWEB_DEBUG
#include "CWebStudio.c"

struct CwebHttpResponse *main_sever(struct CwebHttpRequest *request ){
    sleep(5);
    char *tag = request->get_param(request,"tag");
    if(tag == NULL){
        return cweb_send_text("not passed tag",200);
    }

    char formated_text [100];
    sprintf(formated_text,"passed tag: %s",tag);
    return cweb_send_text(formated_text,200);


}

int main(int argc, char *argv[]){

    cweb_run_server(
        8080,
        main_sever,
        2,
        CWEB_DEFAULT_MAX_BODY,
        CWEB_SAFTY_MODE
    );
}