
#define CEW_MAX_REQUEST_SIZE 15000
#include "CWebStudio/CwebStudioMain.c"


struct CwebHttpResponse *main_sever(struct CwebHttpRequest *request ){
        // Enviando uma resposta HTTP ao cliente
        //dtw_write_string_file_content("saida.txt", raw_entrys);
        if(strcmp(request->route, "/teste") == 0){
            char teste[5];
            memcpy(teste, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",100);
            return cweb_send_text("Hello World", 200);
        }

        //char teste[5];
        //memcpy(teste, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        return cweb_send_file("captura1.png", CWEB_AUTO_SET_CONTENT, 200);

}

int main(){

    /*
    char *content = dtw_load_string_file_content("saida.txt");
    struct CwebHttpRequest *request = private_cwe_create_http_request(content);
    request->represent(request);
    request->free(request);
    free(content);
    */

    cweb_run_sever(8082, main_sever,SAFE_MODE);
    return 0;
}