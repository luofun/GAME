#include<stdio.h>
#include<windows.h>
#include<time.h>
 
void gameinit(int basic[15][15],int basicback[15][15])
{
         srand(time(NULL));
         memset(basic, 0, sizeof(basic)*15*15);
         memset(basicback, 0, sizeof(basicback)*15*15);
         basicback[7][7] = -1;
}
 
int randnum(int input)
{
         return rand() % input + 1;
}
 
int keyinput(int x, int y, int basicback[15][15])
{
         if (x >= 15 || y >= 15 || x < 0 || x < 0)
                   return 1;//unzero to false
         if (basicback[x][y] != -1)
                   return 1;
         return 0;
}
 
void beginprintf()
{
         printf("\n\ntest1.0\n\n");
         Sleep(1000);
         system("cls");
}
 
int chooseone(int basicback[15][15], int randin, int *pos)
{
         int choosenum;
         int k = 0;
 
         choosenum = randnum(randin);
        
         pos[0] = -1;
         pos[1] = -1;
 
         if (randin < 1)
                   return 1;
         for (int i = 0; i < 15; i++)
         {
                   for (int j = 0; j < 15; j++)
                   {
                            if (basicback[i][j] == -1)
                            {
                                     k++;
                            }
                            if (k == choosenum)
                            {
                                     pos[0] = i;
                                     pos[1] = j;
                                     return 0;
                            }
                   }
         }
         return 1;
}
 
void show(int basic[15][15])
{
         for (int i = 0; i < 15; i++)
         {
                   printf("\t\t");
                   for (int j = 0; j < 15; j++)
                   {
                            printf(" %d ", basic[i][j]);
                   }
                   printf("\n");
         }
}
 
int updatepos(int basicback[15][15], int *pos, int color)
{
         int count = 0;
        
         if (basicback[pos[0]][pos[1]] != -1)
                   return count;
         basicback[pos[0]][pos[1]] = color;
 
         if (pos[0] > 0 && pos[1] > 0 && basicback[pos[0] - 1][pos[1] - 1] == 0)
         {
                   basicback[pos[0] - 1][pos[1] - 1] = -1;
                   count++;
         }
         if (pos[0] >= 0 && pos[1] > 0 && basicback[pos[0]][pos[1] - 1] == 0)
         {
                   basicback[pos[0]][pos[1] - 1] = -1;
                   count++;
         }
         if (pos[0] < 14 && pos[1] > 0 && basicback[pos[0] + 1][pos[1] - 1] == 0)
         {
                   basicback[pos[0] + 1][pos[1] - 1] = -1;
                   count++;
         }
         if (pos[0] < 14 && pos[1] >= 0 && basicback[pos[0] + 1][pos[1]] == 0)
         {
                   basicback[pos[0] + 1][pos[1]] = -1;
                   count++;
         }
         if (pos[0] < 14 && pos[1] < 14 && basicback[pos[0] + 1][pos[1] + 1] == 0)
         {
                   basicback[pos[0] + 1][pos[1] + 1] = -1;
                   count++;
         }
         if (pos[0] >= 0 && pos[1] < 14 && basicback[pos[0]][pos[1] + 1] == 0)
         {
                   basicback[pos[0]][pos[1] + 1] = -1;
                   count++;
         }
         if (pos[0] > 0 && pos[1] < 14 && basicback[pos[0] - 1][pos[1] + 1] == 0)
         {
                   basicback[pos[0] - 1][pos[1] + 1] = -1;
                   count++;
         }
         if (pos[0] > 0 && pos[1] >= 0 && basicback[pos[0] - 1][pos[1]] == 0)
         {
                   basicback[pos[0] - 1][pos[1]] = -1;
                   count++;
         }
 
         return count;
}//old = old + new - 1
 
void colorchoose(int *color)
{
         printf("put your color: ");
         scanf("%d", color);
         while (!(*color == 1 || *color == 2))
         {
                   printf("put your color: ");
                   scanf("%d", color);
 
                   #ifdef _DEBUG
                            printf("your color: %d\ttest: %d\n\n", *color, *color == 1 || *color == 2);
                   #endif // _DEBUG
                  
         }
}
 
void copy(int basic[15][15], int basicback[15][15])
{
         for(int i=0;i<15;i++)
                   for(int j=0;j<15;j++)
                            if (basicback[i][j]!=-1)
                            {
                                     basic[i][j] = basicback[i][j];
                            }
}
 
void scaninput(int* pos)
{
         printf("put your pos like %%d %%d:");
         scanf("%d %d", &(pos[0]), &(pos[1]));
}
 
int main(int argc, char* argv[])
{
         #ifdef _DEBUG
                   //printf("%d", getchar());
                   printf("\n\nnow in the debug mode\n\n");
         #endif // _DEBUG
 
         int basic[15][15];
         int basicback[15][15];
         int canchoose = 1;
         int pos[2];
         int color = -1;
 
         pos[0] = -1;
         pos[1] = -1;
 
         beginprintf();
 
         while (1)
         {
                   gameinit(basic, basicback);
                   colorchoose(&color);
 
                   #ifdef _DEBUG
                            show(basic);
                            Sleep(3000);
                            system("cls");
                   #endif
 
                   if (color==1)
                   {
                            while (keyinput(pos[0], pos[1], basicback) == 1)
                                     scaninput(pos);
 
                   }
                   else if (color == 2)
                   {
 
                   }
 
                   #ifdef _DEBUG
                            printf("%d\t%d\t%d\t%d\t\n", basic[0][0], basic[14][14], basicback[0][0], basicback[14][14]);
                            //scanf("%d %d", &(pos[0]), &(pos[1]));
                            //printf("pos:\t%d\t%d\n", pos[0], pos[1]);
                            printf("\n\nin the debug mode really to exit\n\n");
                            Sleep(3000);
                            system("cls");
                            return 0;
                   #endif // _DEBUG
 
         }
 
         return 0;
}