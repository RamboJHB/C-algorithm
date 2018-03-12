char* connect(char* s,char* t){
    char* r = s;
    
    while(*s)s++;
    while(*t){
        *s=*t;
        s++;
        t++;
    }
    *s='\0';
    return r;
}
