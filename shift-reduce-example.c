#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	char data[5];
	struct node * next;
};

char* action[12][6];
char* goTo[8][3];
char grammar[7][4];
int grammarAmount[7];

void fillActionTable()
{
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<6;j++){
			action[i][j] = "e";
			//action[i][j] = NULL;
		}
	}
	action[0][0] = "s5";	action[0][3] = "s4";	
	
	action[1][1] = "s6";	action[1][5] = "acc";
	
	action[2][1] = "r2";	action[2][2] = "s7";	action[2][4] = "r2";	action[2][5] = "r2";
	
	action[3][1] = "r4";	action[3][2] = "r4";	action[3][4] = "r4";	action[3][5] = "r4";
	
	action[4][0] = "s5";	action[4][3] = "s4";	action[5][1] = "r6";	action[5][2] = "r6";
	
	action[5][4] = "r6";	action[5][5] = "r6";	
	
	action[6][0] = "s5";	action[6][3] = "s4";
	
	action[7][0] = "s5";	action[7][3] = "s4";	
		
	action[8][1] = "s6";	action[8][4] = "s11";
	
	action[9][1] = "r1";	action[9][2] = "s7";	action[9][4] = "r1";	action[9][5] = "r1";
	
	action[10][1] = "r3";	action[10][2] = "r3";	action[10][4] = "r3";	action[10][5] = "r3";

	action[11][1] = "r5";	action[11][2] = "r5";	action[11][4] = "r5";	action[11][5] = "r5";	
}

void fillGrammarTable()
{
	strcpy(grammar[1],"EE+T");
	strcpy(grammar[2],"ET");
	strcpy(grammar[3],"TT*F");
	strcpy(grammar[4],"TF");
	strcpy(grammar[5],"F(E)");
	strcpy(grammar[6],"Fid");
}

char* getGrammarHead(int number) // Getting left hand-side of grammar sentence
{
	if(grammar[number][0] == 'E')
		return "E";
	else if(grammar[number][0] == 'T')
		return "T";
	else if(grammar[number][0] == 'F')
		return "F";
}

char* getGrammarFactor(int number)	// Getting grammar sentence
{
	return grammar[number];
}

void fillGrammarAmountTable()
{
	grammarAmount[1] = 3;
	grammarAmount[2] = 1;
	grammarAmount[3] = 3;
	grammarAmount[4] = 1;
	grammarAmount[5] = 3;
	grammarAmount[6] = 1;
}

int getGrammarAmount(int number) // Getting number of element of right-hand side of grammar sentence for reducing amount
{
	return grammarAmount[number];
}

void fillGotoTable()
{
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<3;j++){
			goTo[i][j] = "-1";
		}
	}	
	goTo[0][0] = "1";
	goTo[0][1] = "2";
	goTo[0][2] = "3";
	goTo[1][0] = "1";
	goTo[4][0] = "8";
	goTo[4][1] = "2";
	goTo[4][2] = "3";
	goTo[6][1] = "9";
	goTo[6][2] = "3";
	goTo[7][2] = "10";
}

char* getGotoTableNumber(int factorNum,int orderNum) // Getting wanted number of goto table for reduce function
{
	return goTo[orderNum][factorNum];
}

int getActionTableIndex(char str[3]) // Getting index of the action table titles
{
	if(strcmp(str,"id") == 0){
		return 0;
	}
	else if(strcmp(str,"+") == 0)
		return 1;
	else if(strcmp(str,"*") == 0)
		return 2;
	else if(strcmp(str,"(") == 0)
		return 3;
	else if(strcmp(str,")") == 0)
		return 4;
	else if(strcmp(str,"$") == 0)
		return 5;	
}

int getGotoTableIndex(char str[3]) // Getting index of goto table titles 
{
	if(str[0] == 'E')
		return 0;
	else if(str[0] == 'T')
		return 1;
	else if(str[0] == 'F')
		return 2;
}

int getNumberFromString(char string[3])	// Converting number from string for the indexes of tables  
{
	if(strlen(string) == 1)
		return 0;
	else if(strlen(string) == 2){
		if(string[1] == '1')
			return 1;
		else if(string[1] == '2')
			return 2;	
		else if(string[1] == '3')
			return 3;
		else if(string[1] == '4')
			return 4;
		else if(string[1] == '5')
			return 5;
		else if(string[1] == '6')
			return 6;
		else if(string[1] == '7')
			return 7;
		else if(string[1] == '8')
			return 8;
		else if(string[1] == '9')
			return 9;
	}
	else if(strlen(string) == 3){
		if(string[0] == 'i')
			return 5;
		else if(string[2] == '0')
			return 10;
		else if(string[2] == '1')
			return 11;
	}
}

char* convertChartoStr(char element[5])	// Converting char to string because I have to use strings in order to add that characters to another string.
{	
	if(element[1] == '0')
		return "0";
	else if(element[2] == '0')
		return "10";
	else if(element[2] == '1')
		return "11";
	else if(element[1] == '1')
		return "1";
	else if(element[1] == '2')
		return "2";
	else if(element[1] == '3')
		return "3";
	else if(element[1] == '4')
		return "4";
	else if(element[1] == '5')
		return "5";
	else if(element[1] == '6')
		return "6";
	else if(element[1] == '7')
		return "7";
	else if(element[1] == '8')
		return "8";
	else if(element[1] == '9')
		return "9";
	
}

void print(struct node* root,char token) // Printing stack or input linkedlist by taking token such as 's' or 'i' 
{
	if(token == 's')
		printf("stack:");
	else if(token == 'i')
		printf("input:");
	
	if(root == NULL)
	{
		printf("\n");
		return;
	}
		
	while(root != NULL){
		printf("%s ",root->data);
		root = root->next;
	}	
	printf("\n");
}

char* convert(char element){
	if(element == '*')
		return "*";
	else if(element == '+')
		return "+";
	else if(element == '(')
		return "(";
	else if(element == ')')
		return ")";
}

struct node* push(struct node* root,char data[5]) // Adding an element to the stack
{
	struct node* iter;
	iter = root;
	while(iter->next != NULL){
		iter = iter->next;
	}	
	iter->next = (struct node*)malloc(sizeof(struct node));
	strcpy(iter->next->data,data);
	iter->next->next = NULL;
	return root;
}

struct node* pop(struct node* root)	// Deleting the first element of the stack
{
	struct node* delNode;
	struct node* iter;
	iter = root;
	if(root->next == NULL){
		delNode = root;
		root = NULL;
		free(delNode);
		return root;
	}
	while(iter->next->next != NULL)
	{
		iter = iter->next;
	}
	delNode = iter->next;
	iter->next = NULL;
	free(delNode);
	return root;
}

int getHeadNumber(struct node* root) // Getting data of the first element of the stack 
{
	int i = 0;
	int count = 0;
	
	while(root->next != NULL){
		root = root->next;
	}
	
	char temp[5];
	strcpy(temp,root->data);
	
	return getNumberFromString(temp);
}

char* getAction(int number, char factor[5]) // Getting wanted element from action table by passing index number and current element
{
	return action[number][getActionTableIndex(factor)];
}

struct node* reduce(struct node* root,int grammarNumber) // Reduce function for reducing operation of Shift-Reduce Algorithm
{
	int i;
	int reduceAmount = getGrammarAmount(grammarNumber);
	
	for(i=0;i<reduceAmount;i++){
		root = pop(root);
	}
	char gotoTableNumber[3];
	strcpy(gotoTableNumber,getGotoTableNumber(getGotoTableIndex(getGrammarFactor(grammarNumber)),getHeadNumber(root)));
	
	printf("Goto(%d,%s)\n",getHeadNumber(root),getGrammarHead(grammarNumber));
	
	char tempStr[3];
	strcpy(tempStr,getGrammarHead(grammarNumber)); 	
	strcat (tempStr,gotoTableNumber);	
	root = push(root,tempStr); 
	
	return root;
}

struct node* addInput(struct node* head,char str[3]) //	Adding an element to the input linkedlist
{
	struct node* iter;
	iter = head;
	
	if(head == NULL){
		head = (struct node*)malloc(sizeof(struct node));
		strcpy(head->data,str);
		head->next = NULL;
		return head;
	}
	while(iter->next != NULL){
		iter = iter->next;
	}
	iter->next = (struct node*)malloc(sizeof(struct node));
	strcpy(iter->next->data,str);;
	iter->next->next = NULL;
	return head;	
}

struct node* deleteInput(struct node* head) // Deleting one of the element from the input linkedlist
{
	struct node* delNode;
	if(head->next == NULL){
		delNode = head;
		head = NULL;
		free(delNode);
		return NULL;
	}
	delNode = head;
	head = head->next;
	free(delNode);
	return head;
}

struct node* makeAction(struct node* root,char currentElement[5],char currentAction[5])
{
	if(currentAction[0] == 's'){
		printf("**********\n");
		printf("action:%s\n",currentAction);
		push(root,strcat(currentElement,convertChartoStr(currentAction)));
		print(root,'s');
		return root;
	}
	else if(currentAction[0] == 'r'){
		printf("**********\n");
		printf("action:%s -> ",currentAction);
		
		root = reduce(root,atoi(convertChartoStr(currentAction)));
		if(strcmp(currentAction,"$") == 0)
			return NULL;
			
		print(root,'s');
		strcpy(currentAction,getAction(getHeadNumber(root),currentElement));
		while(currentAction[0] != 's'){
			printf("**********\n");
			printf("action:%s -> ",currentAction);
			
			if(strcmp(currentAction,"e") == 0){
				strcpy(root->data,"err");
				return root;
			}
			
			root = reduce(root,atoi(convertChartoStr(currentAction)));
			print(root,'s');
			strcpy(currentAction,getAction(getHeadNumber(root),currentElement));
			
			if(strcmp(currentAction,"acc") == 0){	
				return NULL;
			}
		}
		printf("**********\n");
		printf("action:%s\n",currentAction);
		push(root,strcat(currentElement,convertChartoStr(currentAction)));
		print(root,'s');
		return root;
	}
}

int main()
{
	char currentAction[5];
	char currentElement[5];

	struct node* root;
	root = (struct node*)malloc(sizeof(struct node)); //Creating root of the stack
	strcpy(root->data,"0");
	root->next = NULL;
	
	struct node* head;
	head = (struct node*)malloc(sizeof(struct node)); //Creating root of the input linkedlist
	head = NULL;
	
	fillActionTable(); //Filling required table
	fillGrammarTable();	//Filling required tables
	fillGrammarAmountTable(); //Filling required tables
	fillGotoTable(); //Filling required tables
	
	char input[50];
	scanf("%[^\n]%*c",input);
	
	//printf("%s",input);
	int a = 0;
	
	while(input[a] != '\0'){
		if(input[a] == ' '){
			a++;
			continue;
		}
		if(input[a] == 'i'){
			head = addInput(head,"id");
			a += 2;
			continue;
		}
		head = addInput(head,convert(input[a]));
		a++;
	}
	
	head = addInput(head,"$");
	
	//printTitles();
		
	while(head != NULL){ // That loop works until the input linledlist is empty
		printf("-----------------------------------------------\n");
		strcpy(currentElement,head->data); // Taking the first element of the input linkedlist as a current element
		printf("Current Situation\n");
		print(root,'s');
 	    print(head,'i');
 	    printf("Current Element:%s\n",currentElement);
 	    //printf("\n");
 		strcpy(currentAction,getAction(getHeadNumber(root),currentElement)); // Assinging corresponding action as a current action by using current element and data of the last element of the stack
 		  
		if(currentAction[0] != 's' && currentAction[0] != 'r' && (strcmp(currentAction,"acc") != 0 )){ // If corresponding element of the action table is empty program gives an error 
			printf("Latest Situation\n");
			print(root,'s');
			print(head,'i');
			printf("Syntax Error\n");
			return 0;
		}
		
		char tempHead[5];
		strcpy(tempHead,root->data);
		 
		root = makeAction(root,currentElement,currentAction); // Making action by passing current element and current action arguments
		
		if(root == NULL){
			printf("**********\n");
			printf("action:acc\n");
			printf("**********\n");
			printf("stack:0\n");
			printf("input:$\n");
			printf("Accepted\n");
			return 1;
		}
		
		if(strcmp(root->data,"err") == 0){
			strcpy(root->data,tempHead);
			printf("Latest Situation\n");
			print(root,'s');
			print(head,'i');
			printf("Syntax Error\n");
			return 0;
		}
		
		head = deleteInput(head); // Deleting the first element of the input linkedlist
	}
		
	return 1;
}





