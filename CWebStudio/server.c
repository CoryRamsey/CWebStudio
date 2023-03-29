


void  private_cweb_execute_request(int new_socket, char *buffer,struct CwebHttpResponse*(*request_handle)( struct CwebHttpRequest *request)){

        // Lendo a solicitação HTTP do cliente
        cweb_print("Lendo a solicitação\n");
        int valread = read(new_socket, buffer, CEW_MAX_REQUEST_SIZE);
        //check if the request is valid
        if(valread <= 0){
            cweb_print("Erro ao ler a solicitação\n");
            return;
        }
        struct CwebHttpRequest *request  = private_cweb_create_http_request(
                buffer
        );
        cweb_print("criou a estrutura\n");
         struct CwebHttpResponse *response;
        response = request_handle(request);
        cweb_print("executou a lambda\n");        
        if(response == NULL){
            response = cweb_send_text(
                "Error 404",
                404
            );
        };
        
        char *response_str = response->generate_response(response);
        cweb_print("resposta gerada\n");
        
        send(new_socket, response_str,strlen(response_str) , 0);
        if(response->exist_content){
            send(new_socket, response->content, response->content_length, 0);
        }
        free(response_str);
        response->free(response);
        request->free(request);
        cweb_print("Limpou A memória\n");
        return ;
}

void private_cweb_send_error_mensage(int new_socket){
   
    struct CwebHttpResponse *response = cweb_send_text(
        "Error 500 Internal Server Error",
        500
    );
    char *response_str = response->generate_response(response);
    send(new_socket, response_str,strlen(response_str) , 0);
    send(new_socket, response->content, response->content_length, 0);

    free(response_str);
    response->free(response);
    
}

void cweb_run_sever(int port,struct CwebHttpResponse*(*request_handle)( struct CwebHttpRequest *request)){

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[CEW_MAX_REQUEST_SIZE] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Faluire to create socket");
        exit(EXIT_FAILURE);
    }

    // Configurando a estrutura de endereço do servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Vinculando o socket à porta especificada
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("Faluire to bind socket");
        exit(EXIT_FAILURE);
    }

    // Waiting for connections
    if (listen(server_fd, 3) < 0) {
        perror("Faluire to listen connections");
        exit(EXIT_FAILURE);
    }

    // Main loop
    while(1) {
        actual_request++;
        // Accepting a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("Faluire to accept connection");
            exit(EXIT_FAILURE);
        }

        cweb_print("----------------------------------------\n");
        cweb_print("Executando Request:%ld\n",actual_request);
        
        #ifdef CWEB_SINGLE_PROCESS

            private_cweb_execute_request(new_socket, buffer, request_handle);
            cweb_print("Request executado\n");

        #else
            cweb_print("Creating a new process\n");
            pid_t pid = fork();
            if(pid == 0){
                //means that the process is the child
                alarm(CWEB_TIMEOUT);
                private_cweb_execute_request(new_socket, buffer, request_handle);
                cweb_print("Request executado\n");
                alarm(0);
                exit(0);
            }
            else if(pid < 0){
                perror("Faluire to create a new process");
                exit(EXIT_FAILURE);
            }
            else{
                cweb_print("----------------------------------------\n");
                cweb_print("New request %ld\n", actual_request);
                cweb_print("Waiting for child process\n");
                pid_t wpid;
                int status = 0;
                while(wpid = wait(&status) > 0);
                        
                if(WIFEXITED(status)){
                    cweb_print("Sucess\n");
                    
                }else{
                    pid_t pid2 = fork();
                    if(pid2 == 0){
                        cweb_print("Sending error mensage\n");
                        alarm(2);
                        private_cweb_send_error_mensage(new_socket);
                        alarm(0);
                        exit(0);
                    }
                    else if(pid2 < 0){
                        perror("Faluire to create a new process");
                        exit(EXIT_FAILURE);
                    }
                    else{
                        pid_t wpid2;
                        int status2 = 0;
                        while(wpid2 = wait(&status2) > 0);
                        if(WIFEXITED(status2)){
                            cweb_print("Mensage sent\n");
                        }else{
                            cweb_print("Error sending mensage\n");
                        }

                    }
                }
                
         
            }
    
        #endif
            close(new_socket);
            cweb_print("Conexão fechada\n");

            //clear the buffer 
            memset(buffer, 0, CEW_MAX_REQUEST_SIZE);
            cweb_print("Buffer limpo\n");
    }
    
}
