

void private_cweb_execute_request(
    int socket,
    struct CwebHttpResponse *(*request_handler)(struct CwebHttpRequest *request)
    ){
    cweb_print("Parsing Request\n");
    struct CwebHttpRequest *request = cweb_request_constructor(socket);

    int result = request->parse_http_request(request);
    
    if(result == INVALID_HTTP){
        cweb_print("Invalid HTTP Request\n");
        request->free(request);
        return;
    }

    if(result == READ_ERROR){
        cweb_print("Read Error \n");
        request->free(request);
        return;
    }
    if(result == MAX_HEADER_SIZE){
        cweb_print("Max Header Size\n");
        request->free(request);
        return;
    }

    cweb_print("created request\n");
    cweb_print("Request method: %s\n", request->method);
    cweb_print("Request url: %s\n", request->url);



    struct CwebHttpResponse *response;
    #ifndef CWEB_NO_STATIC
        response = private_cweb_generate_static_response(request);
        if(response == NULL){
            response = request_handler(request);
        }
    #else
        response = request_handler(request);
    #endif

    cweb_print("executed client lambda\n");


    //means that the main function respond nothing
    if (response == NULL){

        #ifndef CWEB_NO_STATIC

            char *formated_html = cweb_load_string_file_content("static/404.html");
            if(formated_html != NULL){
                response = cweb_send_var_html_cleaning_memory(
                        formated_html,
                        404);
            }
            else{
                response = cweb_send_text(
                        "Error 404",
                        404
                );
            }

        #else

            response = cweb_send_text(
                    "Error 404",
                    404
            );

        #endif


    }

    char *response_str = response->generate_response(response);
    cweb_print("Response created\n");

    send(socket, response_str, strlen(response_str), MSG_NOSIGNAL);


    //envia todo o content de uma vez 

    // Enviando conteúdo byte a byte
    if (response->exist_content)
    {
        size_t sent = 0;
        while (sent < response->content_length)
        {
            size_t chunk_size = response->content_length - sent;
          
            ssize_t res = send(socket, response->content + sent, chunk_size, MSG_NOSIGNAL);
            if (res < 0)
            {
                break;
            }
            sent += res;
        }
    }
    
    free(response_str);
    response->free(response);
    request->free(request);
    cweb_print("Cleared memory\n");
}


void private_cweb_send_error_mensage( const char*mensage,int status_code, int socket)
{
    struct CwebHttpResponse *response = cweb_send_text(mensage,status_code);
    char *response_str = response->generate_response(response);
    send(socket, response_str, strlen(response_str), 0);
    send(socket, response->content, response->content_length, 0);

    free(response_str);

}

