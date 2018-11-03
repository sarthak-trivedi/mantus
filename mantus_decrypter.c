#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int enc[] = {5,2,7,6,8,1,9,10,4,3,
	15,12,17,13,19,11,16,20,14,18,
	23,21,27,25,28,29,30,22,24,26,
	37,34,31,39,38,32,33,40,35,36,
	44,41,48,50,46,42,47,43,45,49,
	55,57,59,56,58,60,51,53,54,52,
	68,66,64,62,70,69,67,65,63,61,
	73,75,71,77,80,79,76,74,72,78,
	82,84,86,88,90,81,83,85,87,89,
	100,98,96,94,92,99,97,95,93,91,
	110,107,106,109,108,103,101,105,102,104,
	112,114,116,118,120,119,117,115,113,111,
	124,127,122,129,128,123,130,121,125,126,
	139,137,135,133,131,140,138,136,134,132,
	144,146,148,150,141,143,145,147,149,142,
	159,157,155,153,151,152,160,154,156,158,
	163,166,169,170,162,165,168,161,164,167,
	180,177,174,171,178,175,172,179,176,173,
	189,186,183,181,184,187,190,182,185,188,
	192,194,196,198,200,191,193,195,197,199,
	203,205,207,209,202,204,206,208,210,201,
	220,218,216,214,212,219,217,215,213,211,
	222,225,228,223,229,226,230,227,224,221,
	232,234,236,238,240,231,233,235,237,239,
	250,249,248,247,246,245,244,243,242,241,
	253,0,252,251,254};

int dec[255];

void decrypt_dir(char *dir_name);
void decrypt_file(char *file_name);
void make_dec();
int file_exists(char *file_name);

int main(void) {
  //STARTING ENCRYPTION FROM THE CURRENT FOLDER
  make_dec();
  decrypt_dir(".");
  return(0);
}

void decrypt_dir(char *dir_name){
  
  
  DIR *d;
  struct dirent *dir;
  d = opendir(dir_name);
  char *path = (char*)malloc(strlen(dir_name)+35);
  
  if (d) {
   while ((dir = readdir(d)) != NULL) {
      
      if(dir->d_type == DT_DIR){
        if(strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0){
          // GOES INTO FOLDERS RECURSIVELY
          strcpy(path, dir_name);
            strcat(path, "/");
          decrypt_dir(strcat(path, dir->d_name));
        }
      }else{
        if(strcmp("mantus_decrypter.c",dir->d_name) != 0 && strcmp("mantus.c",dir->d_name) != 0 && strstr(dir->d_name, ".mantus")){
          //ENCRYPT ONLY IF IT IS NOT MANTUS
          
          strcpy(path, dir_name);
            strcat(path, "/");
            printf("Decrypting : %s%s\n",path,dir->d_name);
          decrypt_file(strcat(path, dir->d_name));
          
        }
          
      }
      
   }
    closedir(d);
  }
}

void decrypt_file(char *file_name){
 
  

    FILE *fm,*fr;
    char c;
    char new_file[strlen(file_name)];
    char *temp = (char *)malloc(8);
    strcpy(new_file, file_name);
    temp = strstr(new_file, ".mantus");
    *(temp) = '\0';

   if(file_exists(new_file)){ 
      //if file already exisists then don't overwrite
      remove(file_name);
      return;
    }

    fr = fopen(file_name,"r");
    fm = fopen(new_file,"w");
    while(1){
        c = fgetc(fr);
         if(c==EOF){
            break;
        }
        
            fputc(dec[c], fm);
    }
    remove(file_name);
    fclose(fm);
    fclose(fr);

}

void make_dec(){
    int i = 0;
    for(i=0; i<255;i++){
        dec[enc[i]] = i;
    }
}

int file_exists(char *file_name){
  FILE *f;
  if(f = fopen(file_name, "r")){
    return 1;
  }else{
    return 0;
  }
}