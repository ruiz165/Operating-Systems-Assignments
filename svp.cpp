#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <unordered_set>

using namespace std;

const int ROW = 9;
const int COL = 9;
int errI;
vector <int> dupCol, dupRow, col, row, temp, v, index, err, errIndex;
map <int, vector <int>> myMap;
map <int, vector <int>> rowMap;
map <int, vector <int>> colMap;
multimap <int,vector<int>> subSqMap;
multimap <int, vector<int> >::const_iterator it;
map <int, vector <int> > :: iterator MyIterMap;
int data[ROW][COL];
int subArr1[3][3], subArr2[3][3], subArr3[3][3], subArr4[3][3], subArr5[3][3], subArr6[3][3], subArr7[3][3], subArr8[3][3], subArr9[3][3];


int printVect(vector <int> vect)
{
  for(int i = 0; i < vect.size(); i++ )
  {
     //cout << vect[i] << " ";
     return vect[i];
  }

  cout << endl;

}

void countDupRows(vector <int> v, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (v[i] == v[j])
            {
              dupRow.push_back(i);
              dupRow.push_back(j);
            }
}


void countDupCols(vector <int> v, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (v[i] == v[j])
            {
              dupCol.push_back(i);
              dupCol.push_back(j);
            }
}

/****** Counting duplicates and pushing to duplicate row map ******/
void pushRowMap(vector <int> v)
{
  int r = 1;
  for (int i = 0; i < row.size(); i++)
  {
    if(row[i] < 0)
    {
      countDupRows(temp, temp.size());
      rowMap.insert( pair<int, vector<int>>(r, dupRow));
      r++;
      dupRow.clear();
      temp.clear();
    }
    else
    {
      temp.push_back(row[i]);
    }
  }
}


/****** Counting duplicates and pushing to duplicate column map ******/
void pushColMap(vector <int> v)
{
  int c = 1;
  for (int i = 0; i < col.size(); i++)
  {
    if(col[i] < 0)
    {
      countDupCols(temp, temp.size());
      colMap.insert( pair<int,vector<int>>(c, dupCol) );
      c++;
      dupCol.clear();
      temp.clear();
    }
    else
    {
      temp.push_back(col[i]);
    }
  }

}

/****** Function to print a map with its key and values ******/
void printMap(map <int, vector<int>> m)
{
  typedef map<int, vector<int>>::const_iterator MapIterator;
  for (MapIterator iter = m.begin(); iter != m.end(); iter++)
  {
    cout << "Key: " << iter->first << endl << "Values:" << endl;
    typedef vector<int>::const_iterator ListIterator;
    for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
        cout << " " << *list_iter << endl;
  }
}

/****** Push Rows of the grid into map as ==> Key: Row, Value: List of the values ******/
map <int, vector <int>> verifyRow(int arr[ROW][COL])
{
  int i = 0;
  while (i < 9)
  {
    for(int j = 0; j < 9; ++j)
    {
      row.push_back(arr[i][j]);
    }
    row.push_back(-1);
    ++i;
  }
  pushRowMap(row);
  return rowMap;
}

/****** Push Columns of the grid into a map as ==> Key: Col number, Value: List of the values ******/
map <int, vector <int>> verifyCol(int arr[ROW][COL])
{
  int j = 0;
  while(j < 9)
  {
    for(int i = 0; i < 9; ++i)
    {
      col.push_back(arr[i][j]);
    }
    col.push_back(-1);
    ++j;
  }
  pushColMap(col);
  return colMap;
}

/****** Function to divide the 9 by 9 board ******/
void getSection(int board[9][9],int result[3][3],int x, int y)
{
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            result[i][j] = board[3*x+i][3*y+j];
        }
    }
}

/****** Creating the sub grids from the original 9 by 9 board ******/
void createSubSuares(int arr[9][9])
{
  getSection(arr, subArr1, 0, 0);
  getSection(arr, subArr2, 0, 1);
  getSection(arr, subArr3, 0, 2);
  getSection(arr, subArr4, 1, 0);
  getSection(arr, subArr5, 1, 1);
  getSection(arr, subArr6, 1, 2);
  getSection(arr, subArr7, 2, 0);
  getSection(arr, subArr8, 2, 1);
  getSection(arr, subArr9, 2, 2);
}

/******  Verifying Sub grids******/
map <int, vector<int>> verifySubSquares(int arr[3][3])
{
  for(int i = 0; i < 3; ++i)
  {
      for(int j = 0; j < 3; ++j)
      {
          int val = arr[i][j];
          if (find(v.begin(), v.end(), val) != v.end())
          {
            val = -val;
            v.push_back(val);
            index.push_back(i);
            index.push_back(j);
            myMap.insert( pair<int,vector<int>>(val, index) );
          }
          else
          {
            v.push_back(val);
          }
          index.push_back(i);
          index.push_back(j);
          myMap.insert( pair<int, vector<int>>(val,index) );
          index.clear();
      }
  }
  v.clear();
  return myMap;
}

/****** Looks through Row and Column maps and outputs the indices of repeating values into the err vector ******/
void findSudokuError(map <int, vector <int>> m1, map <int, vector <int>> m2)
{
  err.clear();
  typedef map<int, vector<int>>::const_iterator MapIterator;
  for (MapIterator iter = m1.begin(); iter != m1.end(); iter++)
  {
    //cout << "Values: \n";
    typedef vector<int>::const_iterator ListIterator;
    for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
    {
    //cout << " " << *list_iter << endl;
    err.push_back(*list_iter );
    }
  }

  for (MapIterator iter = m2.begin(); iter != m2.end(); iter++)
  {
    //cout << "Values: \n";
    typedef vector<int>::const_iterator ListIterator;
    for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
    {
    //cout << " " << *list_iter << endl;
    err.push_back(*list_iter );
    }
  }
}

/****** Find repeating values in the err vector ******/
void getDupInd(vector<int> vec1)
{
  for (int i=0; i<vec1.size(); i++)
    for (int j=0; j<vec1.size(); j++)
      if(i != j && vec1[i] == vec1[j])
      {
        int m = 0;
        for (int k=0; k<errIndex.size(); k++)
          if(errIndex[k] == vec1[i])
            m++;
        if(m == 0)
          errIndex.push_back(vec1[i]);
      }
}

//MAIN METHOD
int main()
{
    /****** Reading the file and populating a 9 by 9 2-dimensional array ******/
    ifstream file("invalid.txt");
    for(int row = 0; row < 9; ++row)
    {
        string line;
        getline(file, line);
        if ( !file.good() )
            break;

        stringstream iss(line);

        for (int col = 0; col < 9; ++col)
        {
            string dupal;
            getline(iss, dupal, ',');

            if ( !iss.good() )
                break;

            stringstream condupertor(dupal);
            condupertor >> data[row][col];
        }
    }

    file.close();

    /****** creating the nine different 3 by 3 sub grids ******/
    getSection(data, subArr1, 0, 0);
    getSection(data, subArr2, 0, 1);
    getSection(data, subArr3, 0, 2);
    getSection(data, subArr4, 1, 0);
    getSection(data, subArr5, 1, 1);
    getSection(data, subArr6, 1, 2);
    getSection(data, subArr7, 2, 0);
    getSection(data, subArr8, 2, 1);
    getSection(data, subArr9, 2, 2);


    /******  ******/
    verifySubSquares(subArr1);
    verifySubSquares(subArr2);
    verifySubSquares(subArr3);
    verifySubSquares(subArr4);
    verifySubSquares(subArr5);
    verifySubSquares(subArr6);
    verifySubSquares(subArr7);
    verifySubSquares(subArr8);
    verifySubSquares(subArr9);

    /****** Find  the index where the error occurs ******/
    verifyRow(data);
    verifyCol(data);

    findSudokuError(rowMap, colMap);
    getDupInd(err);
    errI = printVect(errIndex);
    cout << "The error occurs in Row: " << errI + 1 << ", and Column: " << errI + 1 << "\n";


    return 0;
}
