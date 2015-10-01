//
//  main.c
//  Proj_1_Unix_File_Operation
//
//  Created by Sushant Patil on 20/09/15.
//  Copyright © 2015 Sushant Patil. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void print_line(FILE *fp, int no_of_lines)
{
    char a, line=0;
    if (!fp)
    {
        printf("FILE NOT FOUND");
    }
    while ((a = getc(fp))!=EOF)
    {
        printf("%c", a);
        if (a =='\n')
        {
            line++;
        }
        if (line == no_of_lines)
        {
            break;
        }
    }
}

void print_i_th_line(FILE *fp, int line_num)
{
    char a, line=0;
    if (!fp)
    {
        printf("FILE NOT FOUND");
    }
    while ((a = getc(fp))!=EOF)
    {
        if (a =='\n')
        {
            line++;
        }
        if (line == line_num-1)
        {
            if (a !='\n')
            {
                printf("%c", a);
            }
        }
    }
    printf("\n");
    rewind(fp);
}

void copy_line(FILE *f1, FILE *f2, int no_of_lines)
{
    char a,line=0;
    
    while ((a = getc(f1))!=EOF)
    {
        printf("%c", a);
        putc(a, f2);
        
        if (a =='\n')
        {
            //putc(a, f2);
            line++;
        }
        if (line == no_of_lines)
        {
            //fseek(f1, -1, SEEK_CUR);
            
            break;
        }
    }
}

int copy_file(FILE *f1, FILE *f2)
{
    
    char a;
    if (!f1)
    {
        printf("FILE NOT FOUND\n");
        return 1;
    }
    
    while ((a = getc(f1))!=EOF)
    {
        putc(a, f2);
    }
    printf("FILE copied\n");
    rewind(f1);
    rewind(f2);
    return 0;
    
}


int more_command(FILE *f1)
{
    char a, User_Input;
    if (!f1)
    {
        printf("FILE NOT FOUND");
        return 1;
    }
    
    while(((a=getc(f1))!=EOF))
    {
        printf("Press n\\p\\q : ");
        fseek(f1, -1, SEEK_CUR);
        
        scanf("%c", &User_Input);
        
        if (User_Input == 'n')
        {
            print_line(f1, 1);
            printf("One lines printed\n");
            continue;
        }
        
        if (User_Input == 'p')
        {
            print_line(f1, 10);
            printf("\nTen lines printed\n");
            continue;
        }
        
        if (User_Input == 'q')
        {
            printf("\nTerminated\n");
            break;
        }
        
    }
    printf("\nNo More lines to print\n");
    rewind(f1);
    return 0;

}

void interleave(FILE *f1, FILE *f2, FILE *f3)
{
    char a,b='\0';
    
    do
    {
         a=getc(f1);
         b=getc(f2);

        if (a != EOF)
        {
            fseek(f1, -1, SEEK_CUR);
            copy_line(f1, f3, 1);
        }
        
        if (b !=EOF)
        {
            fseek(f2, -1, SEEK_CUR);
            copy_line(f2, f3, 1);
        }
        
    }while ((a!= EOF) || (b!= EOF));
    
    printf("\n");
    rewind(f1);
    rewind(f2);
    rewind(f3);

}


void grep(FILE *f1)
{
    char temp[512], str[10];
    int match_cnt =0;
    
    printf("\nInput the string you want to search (10 char max.) :\t");
    scanf("%s", str);
    
    while(fgets(temp, 512, f1)!=NULL)
    {
        if (strstr(temp, str)!= NULL)
        {
            printf("Match Found : \n%s", temp);
            match_cnt++;
        }
    
    }
    if (match_cnt == 0)
    {
        printf("NO MATCH FOUND\n");
    }
    printf("Search Complete\n");
    rewind(f1);

}

int count_char_in_line(FILE *fp, int line_num)
{
    char c;
    int char_cnt=0,line_cnt=0;
    
    while ((c= getc(fp))!=EOF)
    {
        char_cnt++;
        if (c=='\n')
        {
            line_cnt++;
            if (line_cnt == line_num)
            {
                rewind(fp);
                return char_cnt;
            }
            char_cnt = 0;
        }
    }
    rewind(fp);
    return char_cnt;
}

int count_words_in_line(FILE *fp, int line_num)
{
    char c;
    int line_cnt=0,word_cnt=1,sp_char_cnt=0;
    
    while ((c= getc(fp))!=EOF)
    {
        if (!((c==',')||(c=='\n')||((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c<='z')) || ((c >= '0') && (c<='9'))))
        {
            sp_char_cnt++;
            if (sp_char_cnt == 1)
            {
                sp_char_cnt =0;
                word_cnt++;
               // printf("\n%d", word_cnt);
            }
        }
        
        if (c=='\n')
        {
            line_cnt++;
            if (line_cnt == line_num)
            {
              //  printf("%d",line_cnt);
                rewind(fp);
                return word_cnt;
            }
            word_cnt = 0;
        }
    }
    rewind(fp);
    return word_cnt;
}

int smallest_line_by_char_cnt(FILE *fp, int lines)
{
    int i, min=100,min_char_line = 0;
    for(i=1;i<=lines+1;i++)
    {
        //printf("\ni%d", count_char_in_line(fp,i));
        if(count_char_in_line(fp, i)< min)
        {
            min = count_char_in_line(fp, i);
            min_char_line = i;
            //printf("\nt%d", min);
        }
    }
    rewind(fp);
    printf("(%d characters) ",min);
    print_i_th_line(fp,min_char_line);
    return min;
}

int smallest_line_by_word_cnt(FILE *fp, int lines)
{
    int i, min=100,min_word_line = 0;
    for(i=1;i<=lines+1;i++)
    {
        //printf("\ni%d", count_char_in_line(fp,i));
        if(count_char_in_line(fp, i)< min)
        {
            min = count_words_in_line(fp, i);
            min_word_line = i;
            //printf("\nt%d", min);
        }
    }
    rewind(fp);
    printf("(%d words) ",min);
    print_i_th_line(fp,min_word_line);
    return min;
}


void longest_3_words(FILE *fp)
{
    char c;
    int word_cnt=0,cnt=0, i = 0;
    char l1[20], l2[20], l3[20],tmp[20];
    l1[0] = '\0';l2[0] = '\0';l3[0] = '\0';
    
    while ((c= getc(fp))!=EOF)
    {
        if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c<='z')) || ((c >= '0') && (c<='9')))
        {
            tmp[cnt] = c;
            cnt++;
        }
        else
        {
            word_cnt++;
            tmp[cnt+1]='\0';
            //printf("%s ", tmp);
            //printf("%d",strlen(tmp));
            
            //biggest 3 logic
            if(strlen(tmp)>strlen(l1))
            {
                strcpy(l1, tmp);
                //printf("%s ", tmp);
            }
            else if(strlen(tmp)>strlen(l2))
            {
                strcpy(l2, tmp);
                //printf("%s ", tmp);
            }
            else if(strlen(tmp)>strlen(l3))
            {
                strcpy(l3, tmp);
                //printf("%s ", tmp);
            }
            
            for (i=0; i<20; i++)
            {
                tmp[i] = '\0';
            }
            cnt = 0;
            
        }
        
    }
    printf("The top 3 longest words are : %s, %s, %s\n",l1,l2,l3);

    rewind(fp);
}



void file_details(FILE *fp)
{
    char c;
    int sp_char_cnt=0,a;
    int char_cnt=1, word_cnt=1, line_cnt=1;
    
    while ((c= getc(fp))!=EOF)
    {
        char_cnt++;
        if (c=='\n')
        {
            line_cnt++;
        }
        
        if (!((c=='\n')||((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c<='z')) || ((c >= '0') && (c<='9'))))
        {
            sp_char_cnt++;
            if (sp_char_cnt == 1)
            {
                sp_char_cnt =0;
                word_cnt++;
            }
        }
    }
    rewind(fp);
    
    printf("\nChar Count is : %d", char_cnt+1);
    printf("\nWord Count is : %d", word_cnt+1);
    printf("\nLine Count is : %d\n", line_cnt);
    printf("The shortest line by char :  ");
    a = smallest_line_by_char_cnt(fp, line_cnt);
    printf("The shortest line by word :  ");
    a = smallest_line_by_word_cnt(fp,line_cnt);
    longest_3_words(fp);

}


int main(int argc, const char * argv[])
{
    //static variables
    FILE *f1, *f2, *f3;
    
    const char *op = argv[1];
    
    printf("Hello, Welcome to Linux File Command Executor\n");
    
    //switch case
    switch (*op)
    {
        case '0':
            f1 = fopen(argv[2], "r");
            f2 = fopen(argv[3], "w");
            copy_file(f1, f2);
            break;
         
        case '1':
            f1 = fopen(argv[2], "r");
            f2 = fopen(argv[3], "r");
            f3 = fopen(argv[4], "w");
            interleave(f1, f2, f3);
            break;
            
        case '2':
            f1 = fopen(argv[2], "r");
            more_command(f1);
            break;
            
        case '3':
            f1 = fopen(argv[2], "r");
            grep(f1);
            break;
            
        case '4':
            f1 = fopen(argv[2], "r");
            file_details(f1);
            break;
            
        default:
            break;
    }
    
    //close the files
    fclose(f1);
    fclose(f2);
    
    // insert code here...
    return 0;
}
