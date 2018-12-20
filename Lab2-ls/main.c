#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

void letters(int mode,char str[]);

int main(int argc, char** argv){
        DIR* dp;
        struct dirent* dentry;
        char pd[11];
        pd[10] = '\0';
        struct stat* raz;
        raz = (struct stat*)calloc(1,sizeof(struct stat));

        if(argc != 2) {
            printf("usage: my_ls dirname\n");
            exit(1);
        }

        if(! (dp=opendir(argv[1])) ) {
            printf("opendir error\n");
            exit(2);
        }
    
        while(1) {
            dentry=readdir(dp);
            if(!dentry)
                break;
            stat(dentry->d_name,raz);
            letters(raz->st_mode,pd);
            printf("%s\t",pd);
            printf("%s\n", dentry->d_name);
        }
        return 0;
    }

void letters(int mode,char str[]){

	strcpy(str, "----------");	

	if(S_ISDIR(mode)) str[0] = 'd';
	if(S_ISCHR(mode)) str[0] = 'c';
	if(S_ISBLK(mode)) str[0] = 'b';

	if(mode & S_IRUSR) str[1] = 'r';
	if(mode & S_IWUSR) str[2] = 'w';
	if(mode & S_IXUSR) str[3] = 'x';

	if(mode & S_IRGRP) str[4] = 'r';
	if(mode & S_IWGRP) str[5] = 'w';
	if(mode & S_IXGRP) str[6] = 'x';

	if(mode & S_IROTH) str[7] = 'r';
	if(mode & S_IWOTH) str[8] = 'w';
	if(mode & S_IXOTH) str[9] = 'x';

}
