
#define CWEB_DEBUG

#include "CWebStudio.c"
struct CwebHttpResponse *main_sever(struct CwebHttpRequest *request ){

    if(strcmp(request->route, "/test") == 0){
        ///making an error 
        int x = 1/0;
        //Your application will crash here if you are using single process 
        //because the error is not handled
    }
    return cweb_send_text("Hello World", 200);
    
}

int main(){

   cweb_run_server(5001, main_sever); 

   return 0;
}