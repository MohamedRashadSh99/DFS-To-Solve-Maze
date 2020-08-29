#include <stdio.h>
#include <stdlib.h>
int start_rows;
int start_cols;
int end_rows;
int end_cols;
char** maze;
int rows,hj;
int cols;
int**visited;
enum terrain
{
    empty,
    wall,
    goal,
    crumb
};

void alloc_visited()
{
    visited=malloc(rows*sizeof(char*));
    int i;
    for(i=0; i<rows; i++)
        visited[i]=malloc(cols*sizeof(char*));
}

void alloc_maze()
{
    maze=malloc(rows*sizeof(char*));
    int i;
    for(i=0; i<rows; i++)
        maze[i]=malloc(cols*sizeof(char*));
}
void get_maze(char*file_name)
{
    char c;
    char rows_s[3]= {'\0'};
    char clos_s[3]= {'\0'};
    int rows_i=0;
    int cols_i=0;
    int swap=0;
    FILE* file=fopen(file_name,"r");
    if(file)
    {
        while((c =getc(file))!=EOF)
        {
            if(c=='\n')
            {
                break;
            }
            else if(c==',')
            {
                swap=1;

            }
            else if(!swap)
            {
                rows_s[rows_i]=c;
                rows_i++;
            }
            else
            {
                clos_s[cols_i]=c;
                cols_i++;
            }
        }

    }
    rows=atoi(rows_s);
    cols=atoi(clos_s);
    alloc_maze();

    int i,j;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            c=getc(file);
            if(c=='\n')
                c=getc(file);
            if(c=='s')
            {
                start_rows=i;
                start_cols=j;
            }
            if(c=='g')
            {
                end_rows=i;
                end_cols=j;
            }
            maze[i][j]=c;
        }
    }

    fclose(file);
}

void get_visited()
{
    alloc_visited();
    int i,j;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            if(maze[i][j]=='*')
                visited[i][j]=wall;
            else if(maze[i][j]=='g')
                visited[i][j]=goal;
            else
                visited[i][j]=empty;
        }

    }
}



void add_crumbs()
{
  int i,j;

for(i=0;i<rows;i++)
  {for(j=0;j<cols;j++)
    {if(maze[i][j]!='s')
        {
            if(visited[i][j]==crumb)
            {
                maze[i][j]='W';
            }
        }
    }
  }
}
int dfs(int row,int col)
{
    int*current=&visited[row][col];
   // printf("row= %d col =%d\n",row,col);
    if(*current==goal)
        return 1;
    if(*current==empty)
    {
        //  printf("%d\n",dfs(row+1,cols));
          *current=wall;
        if(dfs(row-1,col))
        {//printf("left\n");
           *current=crumb;
            return 1;
        }
        if(dfs(row,col+1))
        {//printf("right\n");
            *current=crumb;
            return 1;
        }



        if(dfs(row+1,col))
        {//printf("down\n");
            *current=crumb;
            return 1;
        }

        if(dfs(row,col-1))
        {//printf("Up\n");
            *current=crumb;
            return 1;
        }
    }
    return 0;
}

void printVisited()
{
    int i,j;
   // printf("%d %d\n",start_rows,start_cols);
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            printf("%d ",visited[i][j]);

        }
        printf("\n");
    }
}
void printMaze()
{
    int i,j;
   // printf("%d %d\n",end_rows,end_cols);
    for(i=0; i<rows; i++)
    {printf("\t");
        for(j=0; j<cols; j++)
        {
            printf("  %c  ",maze[i][j]);

        }
        printf("\n");
    }
}

int main()
{

    get_maze("maze.txt");
    get_visited();
    printf("\nMaze before solving\n");
    printMaze();
    dfs(start_rows,start_cols);
    add_crumbs();
    printf("\nMaze after solving\n");
    printMaze();

    return 0;
}
