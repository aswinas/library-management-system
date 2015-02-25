//Library Management System by Aswin.A.S.  clean ver1.0
#include <termios.h>
#include <stdio_ext.h>
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
typedef struct
{
char sid[10],bname[20],scl[10],sname[20],bid[10];
}student;

int sgets(char a[],int l)
{
do
fgets(a,l,stdin);
while(*a=='\n');
}

int getch(void)
    {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
    }
void gotoxy(int x,int y)
{
    fflush(stdout);
   printf("%c[%d;%df",0x1B,x,y);
}

void box()
{
int i=3,j;
char buffer[50];
time_t curtime;
struct tm *loctime;

system("clear");
gotoxy(i,5);
for(i=0;i<75;i++)
{
printf("%c",'*');
j=0x3ffff;
while(j--)
fflush(stdout);
}
for(i=4;i<50;i++)
{
gotoxy(i,5);
printf("*");
gotoxy(i,79);
printf("*");
j=0x3ffff;
while(j--)
fflush(stdout);
}
gotoxy(i,5);
for(i=0;i<75;i++)
{
printf("%c",'*');
j=0x3ffff;
while(j--)
fflush(stdout);
}
gotoxy(6,27);
printf("Library Management System");
gotoxy(7,27);
printf("_______ __________ ______");
curtime = time (NULL);
loctime = localtime (&curtime);
strftime (buffer,50, "%d %B %Y", loctime);
gotoxy(4,62);
fputs (buffer, stdout);
fflush(stdout);
strftime (buffer,50, "Time: %I:%M %p", loctime);
gotoxy(5,63);
fputs (buffer, stdout);
fflush(stdout);
}

int pass()
{
box();
char a[]="aswin",b[20];
int check,i=0;
static int count;
gotoxy(12,38);
printf("LOGIN");
fflush(stdout);
gotoxy(13,38);
printf("_____");
fflush(stdout);
gotoxy(16,23);
printf("Enter the password:");
fflush(stdout);
    while((b[i++]=getch())!=EOF)
    {
        if(b[i-1]=='\n')
        {
            b[--i]='\0';
            break;
        }
	putchar('*');
    }
check=strcmp(a,b);
if(!check)
{
gotoxy(19,32);
printf("Access Granted");
fflush(stdout);
sleep(1);
return;
}
else
{
count++;
gotoxy(19,32);
printf("Access Denied");
fflush(stdout);
sleep(1);
if(count==3)
{
gotoxy(22,27);
printf("No More Attempts are Allowed");
fflush(stdout);
while(1);
}
}
pass();

}
typedef struct
{
char aname[20],bname[20],id[10];
int q,iss;
float price;
}book;

int add()
{
FILE *p,*q;
char y,id1[10];
int qu,check=0;
book *b;
b=malloc(sizeof(book));
p=fopen("stock","a+");
q=fopen("temp","w");
box();
gotoxy(10,37);
fflush(stdout);
printf("ADD BOOK");
gotoxy(11,37);
fflush(stdout);
printf("___ ____");
gotoxy(13,30);
fflush(stdout);
printf("Enter book id:");
sgets(id1,10);
while(1)
{
fread(b,sizeof(book),1,p);
if(feof(p))
break;
	if(!strcmp(id1,b->id))
	{
	check=1;
	gotoxy(16,30);
	printf("Enter quantity:");
	scanf("%d",&qu);
	(b->q)=(b->q)+qu;
	(b->iss)=(b->iss)+qu;
	gotoxy(20,25);
	fflush(stdout);
	printf("Entry Updated successfully...");
	}
	fwrite(b,sizeof(book),1,q);
}
if(!check)
{
strcpy(b->id,id1);
gotoxy(15,30);
printf("Enter book Name:");
sgets(b->bname,20);
gotoxy(17,30);
printf("Enter author's Name:");
sgets(b->aname,20);
gotoxy(19,30);
printf("Enter quantity:");
scanf("%d",&(b->q));
(b->iss)=(b->q);
gotoxy(21,30);
printf("Enter price:");
scanf("%f",&(b->price));
fwrite(b,sizeof(book),1,q);
gotoxy(23,25);
fflush(stdout);
printf("New Entry added successfully...");
sleep(1);
}
fclose(p);
fclose(q);
sleep(1);
rename("temp","stock");
gotoxy(26,20);
fflush(stdout);
printf("Do you want to add books again <y,n> ? ");
while(y=getch())
{
if(y=='Y'||y=='y')
{
add();
break;
}
else if(y=='n')
return;
}
}


int list()
{
FILE *p;
char y;
int i=16;
book *b;
b=malloc(sizeof(book));
p=fopen("stock","a+");
box();
gotoxy(10,34);
fflush(stdout);
printf("LIST OF BOOKS");
gotoxy(11,34);
fflush(stdout);
printf("____ __ _____");
gotoxy(13,10);
printf("ID\tBook Name  \t  Author  \tQuantity\tPrice");
gotoxy(14,10);
printf("__\t_________  \t  ______  \t________\t_____");
gotoxy(39,50);
printf("Press N for Return to Menu");
while(1)
{
fread(b,sizeof(book),1,p);
if(feof(p))
break;
gotoxy(i,10);
printf("%2.5s",b->id);
gotoxy(i,17);
printf("%12.15s",b->bname);
gotoxy(i,33);
printf("%10.15s",b->aname);
gotoxy(i,49);
printf("%5d",b->q);
gotoxy(i,65);
printf("%.2f",b->price);
fflush(stdout);
i++;

if(i==36)
{
gotoxy(39,15);
printf("Press Z for Scroll Down");

while(y=getch())
{
if(y=='n'||y=='N')
return;
if(y=='z'||y=='Z')
break;
}
while(i>=17)
{
gotoxy(i--,6);
printf("                                                                     ");
fflush(stdout);
}
}
}
while(y=getch())
{
if(y=='n'||y=='N')
return;
}
}

int issue()
{
FILE *p,*q,*r;
book *b;
student *s,*t;
int check=0,count=0;
char id1[10],y;
b=malloc(sizeof(book));
p=fopen("stock","a+");
q=fopen("temp","w");
r=fopen("issue","a+");
box();
gotoxy(10,36);
fflush(stdout);
printf("ISSUE BOOK");
gotoxy(11,36);
fflush(stdout);
printf("_____ ____");
gotoxy(13,30);
printf("Enter book id:");
sgets(id1,10);
while(1)
{
fread(b,sizeof(book),1,p);
if(feof(p))
break;
if(!strcmp(id1,b->id))
{
check=1;
if((b->iss)>=1)
{
s=malloc(sizeof(student));
t=malloc(sizeof(student));
gotoxy(15,30);
printf("Enter Student Name:");
sgets(s->sname,20);
gotoxy(17,30);
printf("Enter Student ID:");
sgets(s->sid,10);
gotoxy(19,30);
printf("Enter Class:");
sgets(s->scl,10);
	while(1)
        {
        fread(t,sizeof(student),1,r);
        if(feof(r))
        break;
        if(!strcmp(t->sid,s->sid))
        count++;
        }
if(count<2)
{
(b->iss)=(b->iss)-1;
strcpy((s->bname),(b->bname));
strcpy((s->bid),(b->id));
fwrite(s,sizeof(student),1,r);
gotoxy(23,28);
printf("Book Successfully Issued");
sleep(1);
}
else
{
gotoxy(23,20);
printf("Sorry.You can hold only 2 books at a time");
sleep(1);
}
}
else
{
gotoxy(18,32);
printf("No Books Left");
}
fwrite(b,sizeof(book),1,q);
}
else
fwrite(b,sizeof(book),1,q);
}
fclose(p);
fclose(r);
fclose(q);
rename("temp","stock");
if(!check)
{
gotoxy(18,30);
printf("Can not Find Book Id");
}
gotoxy(26,20);
fflush(stdout);
printf("Do you want to issue book again <y,n> ? ");
while(y=getch())
{
if(y=='Y'||y=='y')
{
issue();
break;
}
else if(y=='n'||y=='N')
return;
}
}


int edit()
{
FILE *p,*q;
book *b;
int check=0;
char id1[10],y;
b=malloc(sizeof(book));
p=fopen("stock","a+");
q=fopen("temp","w");
box();
gotoxy(10,37);
fflush(stdout);
printf("EDIT BOOK");
gotoxy(11,37);
fflush(stdout);
printf("____ ____");
gotoxy(13,30);
printf("Enter book id:");
sgets(id1,10);
while(1)
{
fread(b,sizeof(book),1,p);
if(feof(p))
break;
if(!strcmp(id1,b->id))
{
check=1;
strcpy(b->id,id1);
gotoxy(15,30);
printf("Enter book Name:");
sgets(b->bname,20);
gotoxy(17,30);
printf("Enter author's Name:");
sgets(b->aname,20);
gotoxy(19,30);
printf("Enter quantity:");
scanf("%d",&(b->q));
(b->iss)=(b->q);
gotoxy(21,30);
printf("Enter price:");
scanf("%f",&(b->price));
fwrite(b,sizeof(book),1,q);
sleep(1);
gotoxy(24,28);
printf("Book Successfully Edited");
sleep(1);
}
else
fwrite(b,sizeof(book),1,q);
}
fclose(p);
fclose(q);
rename("temp","stock");
if(!check)
{
gotoxy(18,30);
printf("Can not Find Book Id");
fflush(stdout);
}
gotoxy(39,54);
printf("Press N for Menu");
fflush(stdout);
gotoxy(26,20);
fflush(stdout);
printf("Do you want to Edit book again <y,n> ? ");
while(y=getch())
{
if(y=='Y'||y=='y')
{
edit();
break;
}
else if(y=='n'||y=='N')
return;
}
}

int delet()
{

FILE *p,*q;
book *b;
int check=0;
char id1[10],y;
b=malloc(sizeof(book));
p=fopen("stock","a+");
q=fopen("temp","w");
box();
gotoxy(10,35);
fflush(stdout);
printf("DELETE BOOK");
gotoxy(11,35);
fflush(stdout);
printf("______ ____");
gotoxy(13,30);
printf("Enter book id:");
sgets(id1,10);
while(1)
{
fread(b,sizeof(book),1,p);
if(feof(p))
break;
if(!strcmp(id1,b->id))
{
check=1;
gotoxy(16,30);
printf("Book Successfully Deleted");
sleep(1);
}
else
fwrite(b,sizeof(book),1,q);
}
fclose(p);
fclose(q);
rename("temp","stock");
if(!check)
{
gotoxy(16,30);
printf("Can not Find Book Id");
}
gotoxy(19,20);
fflush(stdout);
printf("Do you want to Delete book again <y,n> ? ");
while(y=getch())
{
if(y=='Y'||y=='y')
delet();
if(y=='n'||y=='N')
return;
}
return;
}

int ret()
{
FILE *p,*q,*r,*t;
book *b;
student *s;
int check1=0,check2=0;
char id1[10],y,sid1[10];
b=malloc(sizeof(book));
p=fopen("stock","a+");
q=fopen("temp","w");
t=fopen("istemp","w");
r=fopen("issue","a+");
box();
gotoxy(10,35);
fflush(stdout);
printf("RETURN BOOK");
gotoxy(11,35);
fflush(stdout);
printf("______ ____");
gotoxy(13,30);
printf("Enter book id:");
sgets(id1,10);
while(1)
{
fread(b,sizeof(book),1,p);
if(feof(p))
break;
if(!strcmp(id1,b->id))
{
check1=1;
gotoxy(15,30);
printf("Enter Student ID:");
sgets(sid1,10);
s=malloc(sizeof(student));
	while(1)
	{
	fread(s,sizeof(student),1,r);
	if(feof(r))
	break;
	if(!strcmp(sid1,s->sid))
	{
	check2=1;
	gotoxy(18,28);
	printf("Book Successfully Returned.");
	sleep(1);
	}
	else
	fwrite(s,sizeof(student),1,t);	
	}

(b->iss)=(b->iss)+1;
fwrite(b,sizeof(book),1,q);
}
else
fwrite(b,sizeof(book),1,q);
}
fclose(p);
fclose(q);
fclose(r);
fclose(t);
rename("temp","stock");
rename("istemp","issue");
gotoxy(18,30);
if(check1)
{
if(!check2)
printf("Can not Find Student Id");
}
else
printf("Can not Find Book Id");
gotoxy(20,20);
fflush(stdout);
printf("Do you want to return book again <y,n> ? ");
while(y=getch())
{
if(y=='Y'||y=='y')
{
ret();
break;
}
else if(y=='n'||y=='N')
return;
}
}

int listiss()
{
FILE *p;
char y;
int i=16;
student *s;
s=malloc(sizeof(student));
p=fopen("issue","a+");
box();
gotoxy(10,36);
fflush(stdout);
printf("ISSUE LIST");
gotoxy(11,36);
fflush(stdout);
printf("_____ ____");
gotoxy(13,10);
printf("Book ID     Book Name     Student ID     Student Name     Class");
gotoxy(14,10);
printf("____ __     _________      _______ __     ______ _____    _____");
gotoxy(39,50);
printf("Press N for Return to Menu");
while(1)
{
fread(s,sizeof(student),1,p);
if(feof(p))
break;
gotoxy(i,10);
printf("%5.5s",s->bid);
gotoxy(i,17);
printf("%17.15s",s->bname);
gotoxy(i,33);
printf("%10.5s",s->sid);
gotoxy(i,49);
printf("%13.15s",s->sname);
gotoxy(i,65);
printf("%8.5s",s->scl);
fflush(stdout);
i++;
if(i==36)
{
gotoxy(39,15);
printf("Press Z for Scroll Down");

while(y=getch())
{
if(y=='n'||y=='N')
return;
if(y=='z'||y=='Z')
break;
}
while(i>=17)
{
gotoxy(i--,6);
printf("                                                                     ");
fflush(stdout);
}
}
}
while(y=getch())
{
if(y=='n'||y=='N')
return;
}
}


int main()
{
char c;
pass();
do
{
box();
gotoxy(10,28);
printf("*......Main Menu......*");
gotoxy(11,28);
printf("       ____ ____ ");
gotoxy(14,30);
printf("1. ADD a Book");
gotoxy(16,30);
printf("2. LIST Books");
gotoxy(18,30);
printf("3. Issue Book");
gotoxy(20,30);
printf("4. Edit Book");
gotoxy(22,30);
printf("5. Delete Book");
gotoxy(24,30);
printf("6. Return Book");
gotoxy(26,30);
printf("7. List Issues");
gotoxy(28,30);
printf("9. EXIT");
c=getch();
switch(c)
{
case '1':
add();
break;
case '2':
list();
break;
case '3':
issue();
break;
case '4':
edit();
break;
case '5':
delet();
break;
case '6':
ret();
break;
case '7':
listiss();
break;
}
}while(c!='9');
}
