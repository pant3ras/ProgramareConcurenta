#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void afisare_meniu()
{
  printf("Introduceti numarul de ordine sau comanda dorita din urmatoarea lista:\n1.quit\n2.myfind\n3.wc\n");
} 

int compare(char username1[],char username2[])
{
  if (strlen(username1)==strlen(username2))
  {int i=0;
    for (i=0;i<strlen(username1);i++)
    {if (username1[i]!=username2[i])
        return 0;}
        return 1;
  }
  else
      return 0;
}

int logare(char username[])
{
    int log_flag;
    pid_t child_pid;
    switch(child_pid=fork())
    {
  case -1:
      {  //eroare la crearea copilului
    fprintf(stderr,"fork -1\n");
    exit(-1);}
  case 0: //suntem in copil
    {    FILE *fd;
        if (NULL==(fd=fopen("usernames","r"))){
      fprintf(stderr,"open -1\n");
      exit(-1);}
      char c;
      char possible_username[30];
      int i=0;
      for (i=0; i<30; i++)
          possible_username[i]='\0';
      while((c = fgetc(fd)) != EOF){
          if (c!='\n')
        strncat(possible_username, &c,1);
          else {
        if (compare(possible_username,username)==1){
            log_flag = 1;
            exit(EXIT_SUCCESS);
        } else {
            int i=0;
            for (i=0;i<30;i++)
          possible_username[i]='\0';
        }
          }
      }
      if (compare(possible_username,username) == 1){
          log_flag = 1;
          exit(EXIT_SUCCESS);}
          exit(EXIT_FAILURE);
    }
  default: 
    {//suntem in parinte
        wait(&log_flag);
        return (log_flag);}
    }
}

int quit()
{
    while (wait (NULL) != -1);
    printf("Programul si-a terminat executia\n");
    return 0;
}

void myfind()
{
   char file_name[30],option_cautare='\0',director[30];
    int i=0;
    for (i=0;i<30;i++)
  file_name[i]='\0';
printf("Doriti sa efectuati cautarea:\n1.Intr-un director\n2.In tot sistem de directoare\n");
   gets(&option_cautare);
    printf("Introduceti numele fisierului cautat : ");
    gets(file_name);
    int pfd[2];
    if (pipe (pfd) == -1){
       fprintf (stderr, "pipe\n");
       exit (1);
    } 
    switch (fork ()){

     case -1:  
     //eroare la forc 
      fprintf (stderr, "fork - 1\n");
      exit (1); 

  case 0 : 
      if(option_cautare=='1')
    {for (i=0;i<30;i++)
     director[i]='\0';
      printf("Specificati calea directorului unde doriti sa efectuati cautarea : ");
    gets(director);}
   // copilul 
      close (1);
      if (dup (pfd[1]) != 1){
    fprintf (stderr, "dup - 1\n");
    exit (1);
      }        
      close (pfd[0]);
      close (pfd[1]);
      if(option_cautare=='1')
      execlp ("find", "find", director,"-maxdepth","1","-name", file_name, "-printf","%p - %t - %s bytes - %M\n", NULL);
    else 
      execlp ("find", "find","-name", file_name, "-printf","%p - %t - %s bytes - %M\n", NULL);
      fprintf (stderr, "exec - 1\n");
      exit (1);
      
  default : 
  {  //parinte
      close(pfd[1]);
      char c,linia[100];
      int i=0,gasire_flag=0;
      for (i=0;i<100;i++){
    linia[i]='\0';
      }
     while(read(pfd[0],&c,1)){
      gasire_flag=1;
    if (c=='\n'){
        printf("Au fost cititi %d octeti : ",strlen(linia));
        int i;
        for (i=0;i<strlen(linia);i++){
              printf("%c",linia[i]);}
              printf("\n");
           for (i=0;i<strlen(linia);i++){
    linia[i]='\0';
      }
    }
    else
        strncat(linia,&c,1);
      }
      close(pfd[0]);
      if(gasire_flag==0)
        printf("Nu a fost gasit nici un fisier cu nume introdus\n");
    }
    }
}

void wc()
{
   char file_name[30];
    int i=0;
    for (i=0;i<30;i++)
  file_name[i]='\0';
    printf("Introduceti numele fisierului cautat : ");
    gets(file_name);
    int pfd[2];
    if (pipe (pfd) == -1){
       fprintf (stderr, "pipe\n");
       exit (1);
    } 
    switch (fork ()){

     case -1:  
     //eroare la forc 
      fprintf (stderr, "fork - 1\n");
      exit (1); 

  case 0 : 
   // copilul 
      close (1);
      if (dup (pfd[1]) != 1){
    fprintf (stderr, "dup - 1\n");
    exit (1);
      }        
      close (pfd[0]);
      close (pfd[1]);
      execlp ("wc", "wc",file_name,"-m","-w","-l",NULL);
      fprintf (stderr, "exec - 1\n");
      exit (1);
      
  default : 
  {  //parinte
      close(pfd[1]);
      char c,linia[100];
      int i=0,gasire_flag=0;
      for (i=0;i<100;i++){
    linia[i]='\0';
      }
     while(read(pfd[0],&c,1)){
      gasire_flag=1;
    if (c=='\n'){
        printf("Au fost cititi %d octeti : ",strlen(linia));
        int i;
        for (i=0;i<strlen(linia);i++){
              printf("%c",linia[i]);}
              printf("\n");
           for (i=0;i<strlen(linia);i++){
    linia[i]='\0';
      }
    }
    else
        strncat(linia,&c,1);
      }
      close(pfd[0]);
      if(gasire_flag==0)
        printf("Nu a fost gasit nici un fisier cu nume introdus\n");
    }
    }
}




int main()
{
    char string [255],answer[20];
    while(1){
  printf ("Introduceti username-ul dumneavoastra: ");
  gets(string);
  if (logare(string)!=0){
      printf("Username-ul %s nu exista in baza de date\n Doriti sa incercati logarea inca o data? Y/N : ",string);
      gets(answer);
      if (strcmp(answer,"y")==0 ||strcmp(answer,"Y")==0)
    continue;
      else
      {quit();
    break;}
  }
  else{
      while(1){
    printf("Logare a fost efectuata cu succes.\n");
    afisare_meniu();
    char comanda[20];
    gets(comanda);
    if (strcmp(comanda,"1")==0 || strcmp(comanda,"quit")==0){
        quit();break;}
    else if (strcmp(comanda,"2")==0 || strcmp(comanda,"myfind")==0)
        myfind();
    else if (strcmp(comanda,"3")==0 || strcmp(comanda,"wc")==0)
      wc();
    else{ 
        printf("Nu ati introdus corect codul comenzii.Doriti sa mai incercati inca o data? Y/N : ");
        gets(answer);
        if (strcmp(answer,"y")==0 ||strcmp(answer,"Y")==0)
      continue;
        else
        {quit();
      break;}
    }
    printf("\nComanda dumneavoastra a fost efectuata cu succes.Doriti sa mai incercati inca o data? Y/N : ");
    gets(answer);
    if (strcmp(answer,"y")==0 ||strcmp(answer,"Y")==0)
        continue;
    else
    {quit();
        break;}
      }
  }
  break;
    }
    return 0;
}