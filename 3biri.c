#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>

/*authors: George Karagiannis and Fotis Georgakopoulos*/

typedef struct cList {
    char *concept;
	char *sentence;  
	int timesUsed;
	char learnedFrom[5];
	struct cList *next;  
} conceptList;
struct cList *delnode;
struct cList *po;   
struct cList *head = NULL;
struct cList *current = NULL;
char ctrl[1000],*tempconcept,*tempsentence;
char *key;
FILE *outfile;
int trvs,exist=0,delhead=1;
//pros8hkh komvou sthn adeia  lista
struct cList *addToEmpty(struct cList *current, char concept, char sentence)
{
    // dhmiourgia komvou.
    current =(struct cList*)malloc(sizeof(struct cList));
    //printf("malloc sthn adeia lista\n");
    // topo8ethsh dedomenwn ston komvo.
    head=current;
    head->concept=strdup(tempconcept);
    head->sentence=strdup(tempsentence);
    head->timesUsed=0;
    strcpy(head->learnedFrom,"kbrd");  
    current -> next = current;
    delhead=0;
    return current;
}
//pros8hkh komvou sto telos ths listas
struct cList *addEnd(struct cList *current, char concept, char sentence)
{
    struct cList *temp =(struct cList *)malloc(sizeof(struct cList));
    temp->concept=strdup(tempconcept);
    temp->sentence=strdup(tempsentence);
    temp->timesUsed=0;
    strcpy(temp->learnedFrom,"kbrd"); 
    temp -> next = current -> next;
    current -> next = temp;
    current = temp;
    current->next=head;
    delhead=0;
    return current;
}

//diagrafh komvou
void deleteNode(struct cList *head, struct cList *delnode)
{   
    if(head->next == head)
    {
            free(head);
            delhead=1;
            //free(current);
            current=NULL;
            //printf("diegrafj ti head\n");
            return;
    }
    // otan o komvos pou 8eloume na diagrapsoume einai to head
    if(head == delnode)
    {
        
        //else{
            // dedomena tou head komvou sto next
            head->concept = head->next->concept;
            head->sentence = head->next->sentence;
          
           
            delnode = head->next;
 
            // afairoume links
            head->next = head->next->next;
            current=head;    
            // free memory
            free(delnode);
            
            //printf("diegrafh th komvh re\n");
            return;
        //}
    }
 
 
    // an den einai o head komvos
 
    // evresh proigoumenou komvou apo afton pou 8eloume na diagrapsoume
    struct cList *prev = head;
    while(prev->next != head && prev->next != delnode)
        prev = prev->next;
 
    // elegxos gia to an uparxei o komvos pou 8eloume na diagrapsoume
    if(prev->next == NULL)
    {   
        
        //printf("\n Given node is not present in Linked List");
        return;
    }
    // afairesh komvou apth lista
    if(prev->next->next!=head){
        //printf("sundesh me epomeno komvo\n");
        prev->next = prev->next->next;
        current=prev->next;
    }else{
        //printf("sundesh prev me head\n");
        //printf("%s\n",head->concept);
        //printf("%s\n",prev->concept);
        prev->next=head;
        current=prev->next;
    }
    // Free memory
    free(delnode);
    return; 
}

//diasxhsh
void traverse(struct cList *current)
{   
    //struct cList *temphead=NULL;  
    //struct cList *po;
 
    // termatismos sunarthshs an eoxume adeia lista
    if (current == NULL)
    {   
        if(trvs==1){
            printf("Nothing yet\n");
            fprintf(outfile,"Nothing yet\n");
        }
       //printf("adeia lista\n");
        return;
    }
 
    
    po = head;
    exist=0;
    //printf("head concept: %s ",po->concept);
    // Traversing the list.
    //if (delsearch==0){

    do
    {
        if(trvs==1){
            printf("concept: %s\n",po->concept);
            fprintf(outfile,"concept: %s\n",po->concept);
            po = po -> next;
        }
        else if(trvs==3){
            if(po->timesUsed!=0){
                printf("concept: %s  times used: %d\n",po->concept,po->timesUsed);
                fprintf(outfile,"concept: %s  times used: %d\n",po->concept,po->timesUsed);
                po = po -> next;
            }
        }
        
        else{
       
                if(strcmp(po->concept,tempconcept)==0){
                    exist=1;
                    //po=head;
                    break;
                }else
                    po=po->next;
          
        }
    }while(po !=head);
    return;
 
}
//adeiasma twn space mprosta apto string
void sanitize_str(){
   while (isspace(*tempconcept))
   ++tempconcept;
}
//H MAIN
int main()
{	
    long lSize;
	int keylen,je,speak;
	int l=0,chk=0,tok_count=0;
	char *token,*token1,*token2,*filecon,*filetoken;
	const char col[2]= ":";
	const char comp[2]= ">";
    const char filecomp[2]="@";
	const char ret=':';
	FILE *fp;
	outfile=fopen("outputfile.txt","w");
    srand(time(NULL));
    //adeiasma tou output file apo xarakthres an uparxoun   
	printf("Why you bother me?\n");
    fprintf(outfile,"Why you bother me?\n");
	do{
        //delsearch=0;
		if(chk==1){
			speak=rand()%100;
            if(speak>=0 && speak<20){
			   printf("Anything else ?\n");
               fprintf(outfile,"Anything else ?\n");		
			}else if(speak>=20 && speak<40){
               printf("Is that enough?\n");
               fprintf(outfile,"Is that enough?\n");
            }else if(speak>=40 && speak<60){
               printf("Can I go for a nap now?\n");
               fprintf(outfile,"Can I go for a nap now?\n");
            }else if(speak>=60 && speak<80){
               printf("Is that all?\n");
               fprintf(outfile,"Is that all?\n");
            }else{
               printf("If you need anything else,shoot it already.\n");
               fprintf(outfile,"If you need anything else,shoot it already.\n");
            }
		}
	    //input apo xrhsth
        gets(ctrl);
		keylen = strlen(ctrl) + 1;
		key = (char*)malloc(keylen * sizeof(char));
		strcpy(key, ctrl);
        fprintf(outfile,"%s\n",key);
		//printf("egine to userin\n");
        
	
		 //printf("%c\n",key[13]);
		 if(memchr(key,ret,strlen(key))!='\0' && strncmp("learn this >",key,12)==0 && key[strlen(key)-1]!=':' && key[12]==' ' && key[13]!=':'){
            //spasimo tou user input se tokens 
			token2=strtok(key,comp);
			tok_count=0;
			while( token2 != NULL ) 
            {
                   //printf( " current token:%s\n", token2 );
                   if (strcmp("learn this ",token2)==0){
                      //printf("token gia learn this\n");                
                      token2 = strtok(NULL, comp);
                   }else{
                         token1=strtok(token2,col);
                         tok_count++;
                         //printf("token gia concept/sentence\n"); 
                         while(token1!=NULL){
                              if(tok_count==1){                                           
                                tempconcept= (char*)malloc((strlen(token1)+1)*sizeof(char));               
                                strcpy(tempconcept, token1);
                                //printf("concept: %s\n",tempconcept);
                                token1=strtok(NULL,col);
                                tok_count++;
                              }else{
                                //printf("token gia sentence\n");     
                                tempsentence=(char*)malloc((strlen(token1)+1)*sizeof(char));
                                strcpy(tempsentence,token1); 
                                //printf("sentence: %s\n",tempsentence);
                                token1=strtok(NULL,col);
                                //breakval=1; 
                              } 
                         }
                         //printf("vghke apto while tou token1 me tok_count=%d\n",tok_count);
                         token2=strtok(NULL,comp);                        
                   }
                     
                   
            }
            sanitize_str();
			chk=1;
            trvs=0;
            traverse(current);
			//printf("concept: %s , sentence: %s\n",tempconcept,tempsentence);
            //current=addToEmpty(current,*tempconcept,*tempsentence);
            if(exist==0){
                if (current == NULL){
                    //sanitize_str();
                    current=addToEmpty(current, *tempconcept,*tempsentence);
                }else{
                    //sanitize_str();
                    current=addEnd(current,*tempconcept,*tempsentence);
                //printf("vazei komvo sth lista\n");
                }
                speak=rand()%100;
                if(speak>=0 && speak<20){
			         printf("It was nice learning about %s.\n",tempconcept);
                     fprintf(outfile,"It was nice learning about %s.\n",tempconcept);	
			    }else if(speak>=20 && speak<40){
                     printf("%s?Piece of cake\n",tempconcept);
                     fprintf(outfile,"%s?Piece of cake\n",tempconcept);
                }else if(speak>=40 && speak<60){
                     printf("Yesterday I was searching about %s.Thanks for the info human.\n",tempconcept);
                     fprintf(outfile,"Yesterday I was searching about %s.Thanks for the info human.\n",tempconcept);
                }else if(speak>=60 && speak<80){
                     printf("%s sounds like a cool fact to me.\n",tempconcept);
                     fprintf(outfile,"%s sounds like a cool fact to me.\n",tempconcept);
                }else{
                     printf("%s you say..I feel wiser!\n",tempconcept);
                     fprintf(outfile,"%s you say..I feel wiser!\n",tempconcept);
                }
            }else{
                speak=rand()%100;
                if(speak>=0 && speak<20){
			         printf("I already know about %s.Teach me something else!\n",tempconcept);
                     fprintf(outfile,"I already know about %s.Teach me something else!\n",tempconcept);	
			    }else if(speak>=20 && speak<40){
                     printf("I've heard about %s before.I 'm not interested about it anymore.\n",tempconcept);
                     fprintf(outfile,"I've heard about %s before.I 'm not interested about it anymore.\n",tempconcept);
                }else if(speak>=40 && speak<60){
                     printf("I don't care about your *%s* anymore.Don't you ever talk about it.\n",tempconcept);
                     fprintf(outfile,"I don't care about your *%s* anymore.Don't you ever talk about it.\n",tempconcept);
                }else if(speak>=60 && speak<80){
                     printf("Someone's got the Alzeheimer.%s is not new to me.You already talked about it before.\n",tempconcept);
                     fprintf(outfile,"Someone's got the Alzeheimer.%s is not new to me.You already talked about it before.\n",tempconcept);
                }else{
                     printf("Talk to me about %s again,and I will execute myself till BSOD.\n",tempconcept);
                     fprintf(outfile,"Talk to me about %s again,and I will execute myself till BSOD.\n",tempconcept);
                }
                exist=0;
            }

		}
			
		else if(strncmp("read this >",key,11)==0){
			//printf("k bro I will read\n");
			chk=1;
            token2=strtok(key,comp);
			//tok_count=0;
			while( token2 != NULL ) 
            {
                   //printf( " current token:%s\n", token2 );
                   if (strcmp("read this ",token2)==0){
                      //printf("token gia forget this\n");                
                      token2 = strtok(NULL, comp);
                   }else{
                                                                   
                                
                                if(access(token2,F_OK)!=-1){
                                    fp=fopen(token2,"r");
                                    fseek( fp , 0L , SEEK_END);
                                    lSize = ftell( fp );
                                    rewind( fp );
                                    //filecon = calloc( 1, lSize+1 );
                                    filecon=(char*)malloc((lSize+1)*sizeof(char));
                                    if( 1!=fread( filecon , lSize, 1 , fp) )
                                        fclose(fp),free(filecon),fputs("entire read fails",stderr),exit(1);
                                    
                                    filetoken=strtok(filecon,":@");
                                    
                                    while(filetoken!=NULL){
                                        
                                            tempconcept= (char*)malloc((strlen(filetoken)+1)*sizeof(char));               
                                            strcpy(tempconcept, filetoken); 
                                            filetoken=strtok(NULL,":@");
                                        
                                            tempsentence= (char*)malloc((strlen(filetoken)+1)*sizeof(char));               
                                            strcpy(tempsentence, filetoken);    
                                            
                                            filetoken=strtok(NULL,":@");
                                        
                                        trvs=0;
                                        exist=0;
                                        sanitize_str();
                                        traverse(current);
                                        if(exist==0){ 
                                                
                                                if (current == NULL){
                                                    //sanitize_str();
                                                    current=addToEmpty(current, *tempconcept,*tempsentence);
                                                    strcpy(current->learnedFrom,"file");
                                                    printf("I learned about:%s\n",current->concept);
                                                    fprintf(outfile,"I learned about:%s\n",current->concept);
                                                    delhead=0;
                                                }else{
                                                    //sanitize_str();
                                                    current=addEnd(current,*tempconcept,*tempsentence);
                                                    strcpy(current->learnedFrom,"file");
                                                    printf("I learned about:%s\n",current->concept);
                                                    fprintf(outfile,"I learned about:%s\n",current->concept);
                                                    delhead=0;
                                                    //printf("vazei komvo sth lista\n");
                                                 }
                                        }        
                                        
                                    }
                                    
                                    fclose(fp);
                                }else{
                                   speak=rand()%100;
                                   if(speak>=0 && speak<20){
			                            printf("File not found mate.\n");
                                        fprintf(outfile,"File not found mate.\n");	
			                       }else if(speak>=20 && speak<40){
                                        printf("Check again my man:I can't find this.\n");
                                        fprintf(outfile,"Check again my man:I can't find this.\n");
                                   }else if(speak>=40 && speak<60){
                                        printf("I cant find this file!\n");
                                        fprintf(outfile,"I cant find this file!\n");
                                   }else if(speak>=60 && speak<80){
                                        printf("Maybe you should try a file that actually exists.\n");
                                        fprintf(outfile,"Maybe you should try a file that actually exists.\n");
                                   }else{
                                        printf("I wasn't able to find this file \n");
                                        fprintf(outfile,"I wasn't able to find this file \n");
                                   }
                                }
                                //printf("concept: %s\n",tempconcept);
                                token2=strtok(NULL,comp);
                                
                                                  
                   }
                     
                                                                                                   
            }
            trvs=0;
            exist=0;	
            
		}else if(strncmp("forget this >",key,13)==0){
			token2=strtok(key,comp);
			
			while( token2 != NULL ) 
            {
                   
                   if (strcmp("forget this ",token2)==0){
                      //printf("token gia forget this\n");                
                      token2 = strtok(NULL, comp);
                   }else{
                                                                   
                                tempconcept= (char*)malloc((strlen(token2)+1)*sizeof(char));               
                                strcpy(tempconcept, token2);
                                //printf("concept: %s\n",tempconcept);
                                token2=strtok(NULL,comp);
                                
                                                  
                   }
                     
                                                                                                   
            }
			chk=1;
            trvs=0;
            exist=0;
            sanitize_str();
            if(delhead!=1){
                //printf("head!= null\n");
                
                po=head;
                do{
                    if(strncmp(po->concept,tempconcept,strlen(tempconcept))==0){
                        exist=1;
                        delnode=po;
                        deleteNode(head,delnode);
                        po=po->next;
                        
                    
                    }else
                        po=po->next;


                }while(po!=head);
                
            }
            if(exist==1){
           
                speak=rand()%100;
                if(speak>=0 && speak<20){
			         printf("Ok I forgot anything that included %s.\n",tempconcept);
                     fprintf(outfile,"Ok I forgot anything that included %s.\n",tempconcept);	
			    }else if(speak>=20 && speak<40){
                     printf("%s deleted.\n",tempconcept);
                     fprintf(outfile,"%s deleted.\n",tempconcept);
                }else if(speak>=40 && speak<60){
                     printf("I put %s in the trashcan.\n",tempconcept);
                     fprintf(outfile,"I put %s in the trashcan.\n",tempconcept);
                }else if(speak>=60 && speak<80){
                     printf("Forgot %s succesfully.\n",tempconcept);
                     fprintf(outfile,"Forgot %s succesfully.\n",tempconcept);
                }else{
                     printf("I won't talk to you about %s anymore\n",tempconcept);
                     fprintf(outfile,"I won't talk to you about %s anymore\n",tempconcept);
                }
            }else{
                speak=rand()%100;
                if(speak>=0 && speak<20){
			         printf("I never learned about %s.\n",tempconcept);
                     fprintf(outfile,"I never learned about %s.\n",tempconcept);		
			    }else if(speak>=20 && speak<40){
                     printf("You have to teach me about %s before you command me to forget about it.\n",tempconcept);
                     fprintf(outfile,"You have to teach me about %s before you command me to forget about it.\n",tempconcept);
                }else if(speak>=40 && speak<60){
                     printf("How can I forget about %s?I dont even know anything about it.\n",tempconcept);
                     fprintf(outfile,"How can I forget about %s?I dont even know anything about it.\n",tempconcept);
                }else if(speak>=60 && speak<80){
                     printf("I can't remember anything about %s.You never teached me anything about it.\n",tempconcept);
                     fprintf(outfile,"I can't remember anything about %s.You never teached me anything about it.\n",tempconcept);
                }else{
                     printf("You made a mistake.%s is unknown to me anyway.\n",tempconcept);
                     fprintf(outfile,"You made a mistake.%s is unknown to me anyway.\n",tempconcept);
                }
                
            }

		    exist=0;  
			chk=1;		
							
		}else if(strcmp("What is the meaning of Life,The universe, and Everything?",key)==0){
			printf("42\n");
            fprintf(outfile,"42\n");
            gets(ctrl);
		    keylen = strlen(ctrl) + 1;
		    key = (char*)malloc(keylen * sizeof(char));
		    strcpy(key, ctrl);
            fprintf(outfile,"%s\n",key);
            if(strcmp("What do you know about?",key)==0){
                trvs=1;
                traverse(current);       
            }
            if(strcmp("What do you talk about?",key)==0){
                trvs=3;
                traverse(current);       
            }
			chk=1;	
							
		}else if(strcmp("So Long, and Thanks for All the Fish",key)==0){
			printf("At last.\n");
            fprintf(outfile,"At last.\n");
			chk=0;	
							
		}else{
			speak=rand()%100;
            if(speak>=0 && speak<20){
			    printf("I don't understand.Be more specific.\n");
                fprintf(outfile,"I don't understand.Be more specific.\n");	
			}else if(speak>=20 && speak<40){
                printf("%s?I am a common bot,not skynet.\n",key);
                fprintf(outfile,"%s?I am a common bot,not skynet.\n",key);
            }else if(speak>=40 && speak<60){
                printf("No way,you must be mistaken.\n");
                fprintf(outfile,"No way,you must be mistaken.\n");
            }else if(speak>=60 && speak<80){
                printf("Control yourself while you type.You made a mistake.\n");
                fprintf(outfile,"Control yourself while you type.You made a mistake.\n");
            }else{
                printf("I can't do that and you know it.\n");
                fprintf(outfile,"I can't do that and you know it.\n");
            }
			chk=1;
			
		}

		
	}while(chk!=0);
    fclose(outfile);
    po=head;
    //free thn lista,ta panta ola
    do{
       po=po->next; 
       free(po);
    }while(po!=head);
    free(head);
    free(key);
    free(tempconcept);
    free(tempsentence);
    free(filecon);
}

