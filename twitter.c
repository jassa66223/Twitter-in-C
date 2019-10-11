#include<stdio.h>
#include<conio.h>
#include<string.h>

char namee[50] = "none";
int position   = 0;

void follow_him(char name[50],char users[50]){
	FILE *f;
	char inp[50],user_name[50];
	f = fopen("following.txt","a+");
	int len = strlen(name),calculate=-1;
	while(len>=0){
		name[len] = name[len-1];
		len--;
	}
	name[0] = '*';
	while(fscanf(f,"%s",&inp) != EOF){
		calculate+=strlen(inp)+1;
		if(inp[0] == '*'){
			strcpy(user_name,inp);
			continue;
		}
		
		if(strcmp(user_name,name) == 0){
		    len =1;
			if(strcmp(inp,users)==0){
				printf("\nYou are already following him");
				len =0;
				break;
			}
			
		}
		if(len == 1){
			break;
		}
		
	}
	if(len != 1 && len != 0){
		FILE *f_f;
		f_f = fopen("following.txt","a");
		fprintf(f_f,"\n %s %s",name,users);
		fclose(f_f);
		printf("\n\n ------------------------ DONE ------------------------");
	}
	if(len == 1){
	   FILE *f_f,*f1;
	   char scanning[50];
	   
	   f_f = fopen("following.txt","r");
	   f1 = fopen("database1.txt","w");
	   
	   while(fscanf(f_f,"%s",&scanning) != EOF){
	   	if(scanning[0] == '*'){
	   		fprintf(f1,"\n %s",scanning);
		   }
		   else{
		   	fprintf(f1," %s",scanning);
		   }
	   } 
	   fclose(f1);
	   fclose(f_f);
	   f_f = fopen("following.txt","w");
	   fclose(f_f);
	   
	   f1 = fopen("database1.txt","r");
	   f_f = fopen("following.txt","a");
	   
	   while(fscanf(f1,"%s",&scanning) != EOF){
	   	if(scanning[0] == '*'){
	   		if(strcmp(name,scanning)==0){
	   			fprintf(f_f,"\n %s",scanning);
	   			fprintf(f_f," %s",users);
			   }else{
			   	fprintf(f_f,"\n %s",scanning);
			   }
		   }
		   else{
		   	fprintf(f_f," %s",scanning);
		   }
	   }
	   fclose(f_f);
	   fclose(f1);
	   f1 = fopen("database1.txt","w");
	   fclose(f1);
	   	printf("\n\n ------------------------ DONE ------------------------");
	 }
	fclose(f);
}

void signup(){
	
	FILE *f;
	char name[50],scan_name[50];
	char pass[50],scan_pass[50];
	int cal=0;
	
	printf("\n\n Enter Name - ");
	scanf("%s",&name);
	printf("\n\n Enter Password - ");
	scanf("%s",&pass);
	
	f = fopen("database.txt","a+");
	while(fscanf(f,"%s,%s",&scan_name,&scan_pass) != EOF){
		
		if(strcmp(scan_name,name) == 0){
			printf("\n\n This name already exist");
			cal++;
			printf("\n\n This name already exist");
			signup();
			fclose(f);
			break;
		}
		
	}
	
	fprintf(f,"\n%s %s",name,pass);
	printf("\n\n DONE");
	fclose(f);
	strcpy(namee,name);
}
void signin(){
	char name[50],pass[50],scan_name[50],scan_pass[50];
	FILE *f;
	int cal =0,pos =1;
	
	printf("\n\n Enter Name - ");
	scanf("%s",&name);
	printf("\n\n Enter Password - ");
	scanf("%s",&pass);
	
	f = fopen("database.txt","r");
	
	while(fscanf(f,"%s %s",scan_name,scan_pass) != EOF){
		if(strcmp(name,scan_name) == 0){
			if(strcmp(pass,scan_pass) == 0){
				strcpy(namee,name);
				cal++;
				fclose(f);
				break;
			}
			else{
				printf("\n\nPassword is wrong");
				fclose(f);
				break;
			}
		}
	}
	if(cal == 0){
		printf("\n\nCheck your user name again");
		fclose(f);
	}
}
void home(char name[50]){
	
	int len = strlen(name);
	while(len>=0){
		name[len] = name[len-1];
		len--;
	}
	name[0] = '*';
	
	FILE *f_f;
	char scanning[50],node[50],data[500][50],status[100];
	f_f = fopen("following.txt","r");
	static int jassa=0;
	while(fscanf(f_f,"%s",&scanning) != EOF){
		if(scanning[0] == '*'){
			strcpy(node,scanning);
			continue;
		}
		if(strcmp(name,node)==0){
			int j = strlen(scanning);
			while(j>=0){
				scanning[j] = scanning[j-1];
				j--;
			}
			scanning[0] = '*';
		    strcpy(data[jassa],scanning);
			jassa++;
		}
	}
	fclose(f_f);
	if(jassa ==0){
		printf("\n\n You are not following anyone.");
	}else{
		
		f_f = fopen("posts.txt","r");
		char scan[50];
		while(fscanf(f_f,"%s %s",&scan,&status) != EOF){
		    int j =0;
			while(j<jassa){
				if(strcmp(data[j],scanning) == 0){
					printf("%s \n \t %s",scan,status);
				}
				j++;
			}
		}
		fclose(f_f);
	}
	
}
void find_friend(char name[50]){
	
	FILE *f;
	char users[50],pass[50],data[50][50];
	int cal=0;
	
	 f = fopen("database.txt","r");
	while(fscanf(f,"%s %s",&users,&pass) != EOF){
		strcpy(data[cal],users); 
		printf("\n %d - %s",cal,users);
		cal++;
	}
	printf("\n\nWho do you want to follow ?  - ");
	int length = cal;
	scanf("%s",&users);
	cal =0;
	while(cal < length){
	
		if(strcmp(data[cal],users) == 0){
		 follow_him(name,users);
		 cal = -1;
		 break;
		}
		cal++;
	}
	if(cal != -1){
		printf("Not found");
		fclose(f);
	}else{
		fclose(f);
	}
	
}
void new_post(char name[50]){
	
	int len = strlen(name);
	while(len>=0){
		name[len] = name[len-1];
		len--;
	}
	name[0] = '*';
	
	char con[100] = "snjdn";
	printf("\n Type your status - \n \t");
	scanf("%s",&con);
	
	FILE *ff;
	ff = fopen("posts.txt","a");
	fprintf(ff,"\n%s %s",name,con);
	fclose(ff);
}
void following(char name[50]){
	FILE *f;
	int len = strlen(name);
	char node[50],scanning[50];
	while(len>=0){
		name[len] = name[len-1];
		len--;
	}
	name[0] = '*';
	
	f = fopen("following.txt","r");
	
	printf("\n\n\n ------------------------------------------ People you are following ----------------------------------------------------");
	while(fscanf(f,"%s",&scanning) != EOF){
		
		if(scanning[0] == '*'){
			strcpy(node,scanning);
			continue;
		}
			if(strcmp(node,name) ==0){
				printf("\n\n------------------ %s ------------------",scanning);
			}
		
	}
}

void main(){
    
    if(strcmp(namee,"none") == 0){
    	int value;
    	printf(" \n\n Sign Up - 1 \n\n");
    	printf("\n\n Sign In - 2 \n\n");
    	scanf("%d",&value);
    	
    	switch(value){
    		case 1:{
    			signup();
    		    main();
				break;
			}
			case 2:{
				signin();
				main();
				break;
			}
			default:{
				printf("\n\nNot a valid input \n\n ");
				main();
				break;
			}
		}
    	
	}else{
		int value;
		printf("\n\n Home - 1");
		printf("\n\n Following - 2");
		printf("\n\n Find Friends - 3");
		printf("\n\n New Post - 4 \n\n");
		scanf("%d",&value);
		
		switch(value){
			case 1:{
				home(namee);
				main();
				break;
			}
			case 2:{
				following(namee);
				main();
				break;
			}
			case 3:{
				find_friend(namee);
				main();
				break;
			}
			case 4:{
				new_post(namee);
				home(namee);
				break;
			}
			default:{
				printf("\n\n Not a valid input \n\n");
				main();
				break;
			}
		}
	}
}
