#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#define ROT_MIN '!'
#define ROT_MAX '~'
#define ROT_SIZE (ROT_MAX - ROT_MIN + 1)
#define ROT_HALF (ROT_SIZE / 2)

void randomPasswordGenerator(void)
{
    char chr1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char chr2[] = "abcdefghijklmnopqrstuvwxyz";
    char chr3[] = "0123456789";
    char chr4[] = "!#$%&'()*+,-./:;<=>?@[\"]\\^_`{|}~";
    printf("\nEnter the length of the password you want to generate. (minimum 10 , maximum 25) : \n");
    int n;
    scanf("%d",&n);
    if (isalpha(n)==0)
        printf("\n");
    	else{
        	printf("Invalid Input\nExiting..");
        	exit(0);
    	}
	if(n < 10){
	  	printf("\033[1;31m The minimum length must be atleast 10 characters!\x1b[0m\n");
	  	randomPasswordGenerator();
	}
	if(n>25){
		printf("\033[1;31m The maximum length must be atmost 25 characters!\x1b[0m\n");
		randomPasswordGenerator();
	}
	if (n>=10 && n<=25){
	printf("\n\nHere is a random password of %d characters for you: ",n );  
	char pass[n];
	srand((unsigned int) time(0) + getpid());
	for(int i = 0; i < n; i++)
	{
        int a = rand() % 4;
        switch(a)
        {
            case 0 : pass[i] = chr1[rand() % 26];
            	break;
            case 1 : pass[i] = chr2[rand() % 26];
            	break;
            case 2 : pass[i] = chr3[rand() % 10];
                break;
            case 3 : pass[i] = chr4[rand() % 13];
            	break;
            default : printf("");
            	break;
        }
    }
        int c = n;
        while(c--)
                printf("\033[0;32m%c\x1b[0m", pass[n-1-c]);
                printf("\n");
	}
}



static char *rotate_encrypt(const char *key, const char *value)
{
	char *rv = strdup(value);
	size_t i, len = strlen(rv);
	for (i = 0; i < len; ++i) {
		int ch;
		if (rv[i] < ROT_MIN || rv[i] > ROT_MAX)
			continue;
		/* Temporary storage in an int to avoid overflowing a char. */
		ch = rv[i] + ROT_HALF;
		if (ch > ROT_MAX) {
			rv[i] = ch - ROT_SIZE;
		} 
		else {
			rv[i] = ch;
		}
	}
	return rv;
}


void passvault(){
  	FILE *fp;
  	FILE *pFile;
  	char* p = " Password : ";
  	char* u = "\nUsername : ";
  	char dummy[] = " ";
  	char select; 
  	char ch; 
  	char* EnterPass;
  	char* EnterUserId;
  	char* Decrypted;
  	char* passkey; //Rssy@491
  	char key[] = "Rssy@491";
  	char* str;
	
	start:   // User Decision input
	printf("\n\n Please Select from below options : ");
	printf("\n To Store passwords press w : ");
	printf("\n To See stored passwords press r : ");
	printf("\n To go back to main menu press m : \n To Exit Press e : ");
	printf("\n\n Enter the selected operation : ");
	//select = getchar();
	scanf("%s",&select);
	switch(select){
	    case 'w':                    //writing the file
			fp = fopen("myfile.txt","a+");
			fgets(dummy, 50, stdin);
			u=rotate_encrypt(NULL,u);
			fputs(u,fp);
			u = "\nUsername : ";                    //UserName
			printf("\n Enter Username : ");
			EnterUserId=getpass("");
			EnterUserId=rotate_encrypt(NULL,EnterUserId);//implemented encryption
			fputs(EnterUserId,fp);
			p=rotate_encrypt(NULL,p);
			fputs(p,fp);                    //Password
  			EnterPass = getpass("\n Enter Password :");
  			EnterPass=rotate_encrypt(NULL,EnterPass);
			fputs(EnterPass,fp);
		  	p = " Password : ";
		  	fflush(fp);
		  	fclose(fp);
	  		printf("\n\t PASSWORD STORED SUCCESSFULLY!! ");

	goto start;

      	case 'r':

			printf("\n\n Enter Password Key To Open Vault : ");
		  	fflush(stdin);
		  	passkey = getpass("");
  		  	if(strncmp(passkey, "Rssy@491",8) == 0){                 // READING THE FILE
		
		    	fp = fopen ("myfile.txt","r+");
		        char line[1024];
		        while (fgets(line, sizeof(line), fp) != NULL) {
		            char *s = rotate_encrypt(NULL, line);
		            fputs(s, stdout);
		            free(s);
		        }
		      	fclose(fp);
		      	goto start;
		  	}    // If password Entered Correct
		
		  	else{
		    	printf("\n\n\t Incorrect Password!! \n");
		      	exit(0);
		  	}

  		case 'm':
  			menu();

    	case 'e':
      		footer();
      		exit(0);

	}
}


void quitOrContinue(void){
  	char option=0;
  	printf("===============================================");
  	printf("\n\nOperation Completed Successfuly!");
  	checkpoint:
  	printf("\n\nPlease select one option from below :\nEnter 1 to Continue \nEnter 2 to go back to main menu\n3 To Exit\n\n");
  	scanf("%s", &option);
	switch(option){
		case '1':
		    printf("\n");
		    randomPasswordGenerator();
		    quitOrContinue();
		case '2':
		    menu();
		case '3':
		    footer();
			exit(0);
		default:
			printf("\nPlease select one option from below :\nEnter 1 to Continue \nEnter 2 to go back to main menu\n3 To Exit\n\n");
			goto checkpoint;
	}
}





void menu(void){
	
	char select='0';
	Begin:
	printf("\n\n===============================================");			//Interface
	printf("\n\nWelcome to Secure Password Manager!!");
	printf("\n\nChoose from:");
	printf("\n \033[1;31m 1. Secure Password Vault\x1b[0m");
	printf("\n \033[1;34m 2. PassX - A simple password complexity checker tool.\x1b[0m");
	printf("\n \033[0;32m 3. Strong random Password Generator\x1b[0m");
	printf("\n \033[1;33m 4. Exit\x1b[0m");
	printf("\n\n===============================================");
	
	printf("\n\n Please select from above options : \n\n");
	scanf("%s",&select);
	switch(select){
		case '1':
		    passvault();
	    goto Begin;
	
		case '2':
		    header();
	    	check();
		goto Begin;
	
		case '3':
			randomPasswordGenerator();
	    	quitOrContinue();
    	goto Begin;	

		case '4':
    		footer();
			exit(0);

		default:
			printf("\nPlease select a valid option from the above menu");
		goto Begin;
	}
}



void header(){
    printf("\nWelcome to PassX - A simple password complexity checker tool.\n\n");
    printf("\n\t\t\t\t\tBest password practice : \n\t\t\t\t\t1. at least 10 characters long\n\t\t\t\t\t2. include numbers\n\t\t\t\t\t3. include lowercase letters\n\t\t\t\t\t4. include uppercase letters\n\t\t\t\t\t5. include special symbols\n");
}

void footer(){
	printf("\n\t\t\t\t\t----------------------------------- \n");
	printf("\t\t\t\t\t        Thanks for visiting \n");
	printf("\t\t\t\t\t----------------------------------- \n\n");
}

void check(){
    char char_set_lowercase[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char char_set_uppercase[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char char_set_special_chars[32] = {'!','@','#','$','%','^','&','*','(',')','_','}','{','>','<','\'','\"','~','[',']','+','-','/','?',',','.',':',';','`','\\','|'};
    char char_set_numbers[] = "0123456789";
    int choice = 0;
    printf("\n\nEnter your choice from below options to continue : \n1. Check password complexity\n2. Go back to main menu. \n");
    scanf("%d", &choice);
    //printf("Choice : %d",choice);
    int line_num = 1;
    int find_result = 0;
    if (choice == 1){
        while (choice == 1){
            char password[30];
            printf("\nEnter password to check its complexity,bruteforce time and status : ");
            scanf("%s", password);
            int passlength = strlen(password);
            //printf("Pass length is : %d",passlength);
            int len_char_set_lo = 0, len_char_set_up = 0, len_char_set_sp = 0, len_char_set_num = 0;
            for(int i=0; i<passlength; i++){
                for(int j=0; j<25; j++){
                    if(password[i] == char_set_lowercase[j]){
                        len_char_set_lo = 26;
                        break;
                    }
                    else if(password[i] == char_set_uppercase[j]){
                        len_char_set_up = 26;
                        break;
                    }
                    else if(password[i] == char_set_special_chars[j]){
                        len_char_set_sp = 32;
                        break;
                    }
                    else if(password[i] == char_set_numbers[j]){
                        len_char_set_num = 10;
                        break;
                    }
                }
            }
            int total_length_of_char_sets = len_char_set_lo + len_char_set_up + len_char_set_sp + len_char_set_num;
            float pass_complexity = (log(total_length_of_char_sets)/log(2))*passlength;
			// We assume that on average, the password will be cracked when half of the possible passwords are checked.
            printf("\n==========================================================================================\n");
            printf("\n\nPassword Complexity : %0.2f", pass_complexity);
            float time_to_break_pass = round(((1.5 * pow(10, -14)) * (pow(total_length_of_char_sets, passlength)))/(2*60*60*24*365));
            int counter = 0;
            char ch[500];
            FILE *fptr;
            fptr = fopen("password.txt","r");
            while(fgets(ch, 500, fptr) != NULL) {
	        	if((strstr(ch, password))){
                    printf("\nYour password can be cracked under a minute as it is in common password list.");
                    counter ++;
                    break;
                }
            }
            fclose(fptr);
            if (time_to_break_pass <= 0.00f  && counter < 1){
                printf("\nYour password can be cracked under few months.");
            }
            else if(time_to_break_pass > 0.00f && counter < 1){
                printf("\nTime to bruteforce a password : %0.2f years", time_to_break_pass);
            }
            //checking if password is only alphanumeric, only digits or only alphabets.
            int flag_for_alpha = 1;
            for(int i=0; i< strlen(password) && flag_for_alpha == 1; i++ ){
                if( isalpha(password[i])) flag_for_alpha = 1;
                else flag_for_alpha = 0;
            }
            if (flag_for_alpha)
                printf("\n\x1b[31m[+] WARNING!\x1b[0m Your password only contains alphabets. Make sure to include special characters to increase password strength.");

            int flag_for_dig = 1;
            for(int i=0; i< strlen(password) && flag_for_dig == 1; i++ ){
                if( isdigit(password[i])) flag_for_dig = 1;
                else flag_for_dig = 0;
                }
            if (flag_for_dig)
                printf("\n\x1b[31m[+] WARNING!\x1b[0m Your password only contains digits. Make sure to include special characters to increase password strength.");

            int flag_for_alnum = 1;
            if (flag_for_alpha == 0 && flag_for_dig  == 0){
                for(int i=0; i< strlen(password) && flag_for_alnum == 1; i++ ){
                    if( isalnum(password[i])) flag_for_alnum = 1;
                    else flag_for_alnum = 0;
                    }
                if (flag_for_alnum)
                    printf("\n\x1b[31m[+] WARNING!\x1b[0m Your password only contains alphabets and numbers. Make sure to include special characters to increase password strength.");
            }
            if (pass_complexity <= 50){
                printf("\nPassword Strength : \x1b[31mWeak\x1b[0m");
            }
            else if (pass_complexity > 50 && pass_complexity <= 90){
                printf("\nPassword Strength : \x1b[36mAverage password\x1b[0m");
            }
            else if (pass_complexity > 90 && pass_complexity <= 120){
                printf("\nPassword Strength : \x1b[34mGood Password\x1b[0m");
            }
            else if (pass_complexity > 120){
                printf("\nPassword Strength : \x1b[32mBest Password\x1b[0m");
            }
            printf("\n\n\n==========================================================================================");
            int sec_choice = 0;
            printf("\n\nPress 1 to check again or 2 to go back to main menu or 3 to exit\n");
            scanf("%d", &sec_choice);
            if (sec_choice == 1){}
            else if (sec_choice == 2){

                menu();
            }
            else if (sec_choice==3){
                footer();
                exit(0);
            }
            else if (sec_choice != 1 || sec_choice != 2 || sec_choice != 3 || isalpha(sec_choice)){
                printf("\nWrong choice!!. Choose only from 1 or 2.\n[+]Program exiting....\n\n");
                exit(0);
            }
        }
    }
    else if (choice == 2){
        printf("\n");
    }

    else{
        printf("\nWrong input!!. Choose only from 1 or 2.\n[+]Program exiting....\n\n");
		exit(0);
    }

}

int main(){
	
	menu();
	return 0;
}
