#define CWEB_DEBUG
#include "CWebStudio/CwebStudioMain.c"

#include <iostream>
#include <string>


struct CwebHttpResponse *main_sever(struct CwebHttpRequest *request ){

    unsigned char *body = request->content;
    int size = request->content_length;

    std::string rota = request->route;
    
    if(rota == "/get"){
       return cweb_send_file("bird.png",CWEB_AUTO_SET_CONTENT,200);
    }
    if(rota == "/set"){

            dtw_write_any_content("test.png", body, size);
            return cweb_send_text("uploaded",200);

    }
    else{
        return cweb_send_text("rota invalda",200);
    }

    
    
}

int main(){
    cweb_run_server(
        80,
        main_sever,
        20,
        1000000,
        false
    );
}