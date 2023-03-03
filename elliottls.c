#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*

The aims of this program:

Arguments:

Help menu (This)
-help

Create new file
-newfile [fileName]


Print file content
-readFile [fileName]


Print size of file
-bufferFile [fileName]
printf("%ld\n", (long long)someVar); 
*/


off_t sizeFile(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
    {
        return st.st_size;
    }
    return -1; 
}
int main( int argc, char *argv[] )
{
    bool debug = false;
    
    if (argc > 1){

            for (int i = 0; i<argc; i++)
            {
                if (strcmp("-debug",argv[i]) == 0)
                {
                    debug = true; // Enable debug flag
                    printf(ANSI_COLOR_RED"DEBUG MODE\n\n"ANSI_COLOR_RESET"Arguments passed:\n");
                    for (int i = 0; i<argc; i++) printf("%d \t %s \n", i, argv[i]); // List arguments passed
                    printf("\n");
                }
            }
            
        
        if (strcmp("-newFile",argv[1]) == 0 ) 
        {
            if (debug){
                printf("newFile");
                createFile(argv[2]);
            }
            else{
                createFile(argv[2]);
            }
            
        }
        else if (strcmp("-readFile",argv[1]) == 0 )
        {
            readFile(argv[2]);
        }
        else if (strcmp("-sizeFile",argv[1]) == 0 )
        {
            long double size;
            size = (long double)sizeFile(argv[2]);
            // Terrabytes
            if (size > (long double)1073741824000)
            {
                size = ((long double)sizeFile(argv[2])/((1000*1000*1000*1000)));
                printf("File:"ANSI_COLOR_GREEN" %s \n"ANSI_COLOR_RESET"Size:"ANSI_COLOR_RED" %.2Lf TB\n",argv[2],size);
            }
            // Gigabytes
            else if (size > (long double)1073741824)
            {
                size = ((long double)sizeFile(argv[2])/((1000*1000*1000)));
                printf("File: "ANSI_COLOR_GREEN"%s \n"ANSI_COLOR_RESET"Size:"ANSI_COLOR_MAGENTA" %.2Lf GB\n"ANSI_COLOR_RESET"",argv[2],size);
            }
            // Megabytes
            else if (size > (long double)1048576)
            {
                size = ((long double)sizeFile(argv[2])/((1000*1000)));
                printf("File: "ANSI_COLOR_GREEN"%s \n"ANSI_COLOR_RESET"Size:"ANSI_COLOR_YELLOW" %.2Lf MB\n"ANSI_COLOR_RESET"",argv[2],size);
            }
            // Kilobytes
            else if (size > (long double)1024)
            {
                size = ((long double)sizeFile(argv[2])/(1000));
                printf("File: "ANSI_COLOR_GREEN"%s \n"ANSI_COLOR_RESET"Size:"ANSI_COLOR_BLUE" %.2Lf KB\n"ANSI_COLOR_RESET"",argv[2],size);
            }
            // Bytes
            else
            {
                size = ((long double)sizeFile(argv[2]));
                printf("File: "ANSI_COLOR_GREEN"%s \n"ANSI_COLOR_RESET"Size:"ANSI_COLOR_GREEN" %Lf Bytes\n"ANSI_COLOR_RESET"",argv[2],size);
            }
            
        }
        else if (strcmp("-help",argv[1]) == 0 )
        {
            printf( ANSI_COLOR_GREEN "\nThe aims of this program:\n\nArguments:\n\nHelp menu (This)"ANSI_COLOR_RESET"\n-help\n\n"ANSI_COLOR_GREEN"Create new file"ANSI_COLOR_RESET"\n-newfile [fileName]\n\n\n"ANSI_COLOR_GREEN"Print file content"ANSI_COLOR_RESET"\n-readFile [fileName]"ANSI_COLOR_GREEN"\n\n\nPrint size of file"ANSI_COLOR_RESET"\n-bufferFile [fileName]\n\n");
        }
        
    }
}

void createFile(char fileName[])
{
    int fd;
    char text[1024];

    printf("Enter file data or [ENTER] to make blank\n");
    
    scanf("%[^\n]", text) == 10;

    fd = open(fileName, O_WRONLY | O_CREAT, 0644); // Read only OR Create file, 0644 access mode of file
    if (fd < 0)
    {
        printf("error number %d\n", errno);
        perror("Foo");
        exit(1);
    }

    write(fd,text, strlen(text)); // file, buffer, count(buffer size)
    close(fd); // Closes file descriptors for reuse
}

int bufferFile(char fileName[])
{
    int status;
    struct stat st;
    status = stat(fileName, &st);
    if(status == 0) {
        st.st_size;
    }
    return st.st_size;
}

void readFile(char fileName[])
{
    FILE* fp;
    int size;

    size = (int)bufferFile(fileName);
    printf("%i",size);
    
    fp = fopen(fileName, "r");
    char string[size];

    fgets(string,size,fp);
    printf("%s\n",string);
    fclose(fp);
}

/*
Notes

lseek(fd, 100, SEEK_SET); // seeking 100 bytes into file
lseek(fd, -100, SEEK_SET); // seeking 100 bytes into file

lseek(fd, -100, SEEK_END); // seeking 100 bytes from file en
lseek(fd, 100, SEEK_END); // extends file past file end, returns zeros and doesn't expand file untill written to
*/


/*
buffer = size of data read
size = size of objects read
num = number of objects read
fd = file descriptor
*/

/*
SEEK_SET Relitive to start of file
SEEK_CUR Relitive to current position of pointer
SEEK_END Relitive to end of file


fseek(fp, 0L, SEEK_END); // seek to end of file
size = ftell(fp);
rewind(fp);
fclose(fp);
*/