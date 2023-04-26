


unsigned char *cweb_load_any_content(const char * path,int *size,bool *is_binary){
    FILE *file = fopen(path,"rb");
    if(file == NULL){
        free(file);
        return NULL;
    }
    fseek(file,0,SEEK_END);
    *size = ftell(file);
    fseek(file,0,SEEK_SET);
    unsigned char *content = (unsigned char*)malloc(*size +1);
    fread(content,1,*size,file);

    *is_binary = false;
    for(int i = 0;i < *size;i++){
        if(content[i] == 0){
            *is_binary = true;
            break;
        }
    }
    if(!*is_binary){
        content[*size] = '\0';
    }

    fclose(file);
    return content;
}


char *cweb_load_string_file_content(const char * path){
    FILE *file = fopen(path,"r");
    if(file == NULL){
        return NULL;
    }
    fseek(file,0,SEEK_END);
    int size = ftell(file);
    fseek(file,0,SEEK_SET);
    char *content = (char*)malloc(size +1);
    fread(content,1,size,file);
    content[size] = '\0';
    fclose(file);
    return content;
}


unsigned char *cweb_load_binary_content(const char * path,int *size){
    FILE *file = fopen(path,"rb");
    if(file == NULL){
        return NULL;
    }
    fseek(file,0,SEEK_END);
    *size = ftell(file);
    fseek(file,0,SEEK_SET);
    unsigned char *content = (unsigned char*)malloc(*size);
    fread(content,1,*size,file);
    fclose(file);
    return content;
}





char *cweb_parse_string_to_lower(const char *old_string){
     
    int string_size = strlen(old_string);
    char *new_string = (char*)malloc(string_size + 2);
    for(int i = 0; i < string_size; i++){
        new_string[i] = tolower(old_string[i]);
    }
    new_string[string_size] = '\0';
    return new_string;
}


char *cweb_parse_string_to_upper(const char *old_string){
    
    int string_size = strlen(old_string);
    char *new_string = (char*)malloc(string_size + 2);
    for(int i = 0; i < string_size; i++){
        new_string[i] = toupper(old_string[i]);
    }
    new_string[string_size] = '\0';
    return new_string;
}

char *cweb_normalize_string(const char *old_string,const char *invalid_chars){
    
    int string_size = strlen(old_string);
    char *lower_string = cweb_parse_string_to_lower(old_string);
    char *new_string = (char*)malloc(string_size + 2);
    int new_string_size = 0;

    for(int i = 0; i < string_size; i++){
        if(strchr(invalid_chars,lower_string[i]) == NULL){
            new_string[new_string_size] = lower_string[i];
            new_string_size++;
        }        
    }
    new_string[new_string_size] = '\0';
    free(lower_string);
    return new_string;
}

const char *cweb_generate_content_type(const char *file_name){
        int file_name_size = strlen(file_name);
        char extension[100];
        int extension_size = 0;
        //iterate in negative
        for(int i = file_name_size-1; i >=0; i--){
            char current_char = file_name[i];
            if(current_char =='.'){
                break;
            }
            extension[extension_size] = current_char;
            extension_size+=1;
        }
        printf("extension: %s",extension);
        
        char *content_type_created = (char*)malloc(100);
       
        if(strcmp(extension, "html") == 0){
            strcpy(content_type_created, "text/html");
        }
       
        else if(strcmp(extension, "css") == 0){
            strcpy(content_type_created, "text/css");
        }
       
        else if(strcmp(extension, "js") == 0){
            strcpy(content_type_created, "text/javascript");
        }
        else if(strcmp(extension, "png") == 0){
            strcpy(content_type_created, "image/png");
        }
        else if(strcmp(extension, "jpg") == 0){
            strcpy(content_type_created, "image/jpeg");
        }
        else if(strcmp(extension, "jpeg") == 0){
            strcpy(content_type_created, "image/jpeg");
        }
        else{
            strcpy(content_type_created, "text/plain");
        }
     


        return content_type_created;
}