#define CWEB_DEBUG
#include "CWebStudio/CwebStudioMain.h"

struct CwebHttpResponse *main_sever(struct CwebHttpRequest *request ){
    if(actual_request > 10){
        request->free(request);
        exit(0);
    }
    return cweb_send_text("Hello World", 200);
}

int main(){
    for(int i =3000;i< 4000;i++){
     cweb_run_server(i,main_sever,3,true);
     
    }

}