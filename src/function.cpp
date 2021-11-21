#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm> 
using namespace std;
short numberofmines_near(short x,short y,vector<vector<int>> &board,int width, int height)
{
   short count=0;
   for(int i=y-1;i<=y+1;i++)
   {
         for(int j=x-1;j<=x+1;j++)
         {
             if(i<0 || i>=height || j<0 || j>= width)
                continue;
            else
            {
                   if(board[j][i]==-1)
                {
                   count++;
                }
            }
         }
   }
   return count;
}
void gen_board(vector<vector<int>> &board, int width, int height, int mines, int seed = 0)
{
    // fill the board vector with 0
    // if seed is 0, generate a random seed
    // generate a vector<pair<int,int>> containing every cells
    // use shuffle() to pick random cells that has mines
    // for cells that don't has mines, count the number of mines around them
    if(seed==0)
      srand(time(0));
    vector<pair<int,int>> cell;
    for(int i=0;i < height;i++)
    {
        for(int j=0;j < width;j++ )
        {
            cell.push_back({j,i});
        }
    }
    random_shuffle(cell.begin(),cell.end());
    for(int i=0; i < mines; i++)
    {
          board[cell[i].first][cell[i].second]=-1;
    }
    for(int i=0;i < height;i++ )
    {
        for(int j=0;j < width;j++ )
        {
            if(i<0 || i>=height || j<0 || j>= width)
                continue;
            else
            {
                if(board[j][i]!=-1)
               {
                   board[j][i]= numberofmines_near(j,i,board,width,height);
               }
            }
        }
        
    }
}
bool open_cell(int x, int y, vector<vector<int>> &board, vector<vector<int>> &mask)
{
    // return true if board[x][y] has a mine
    // else if board[x][y] is 0, call mass_open() and return false
    // else set mask[x][y] to 1 and return false
    if(board[x][y]==-1)
       return true;
    else if(board[x][y]==0)
       {
           mass_open(x,y,board,mask);
           return false;
       }
    else 
       {
           mask[x][y]==1;
           return false;
       }
}
void flag_cell(int x, int y, vector<vector<int>> &mask)
{
    // set mask[x][y] to 0 to if the cell is already flagged
    // else set mask[x][y] to -1
    if(mask[x][y]==-1)
    {
        mask[x][y]==0;
    }
    else{
        mask[x][y]==-1;
    }
}