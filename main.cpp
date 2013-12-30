#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>

bool czyBylaWylosowana( int iLiczba, int tab[], int ile )
{
  if( ile <= 0 )
    return false;

  int i = 0;
    do
      {
        if( tab[ i ] == iLiczba )
	  return true;

        i++;
      } while( i < ile );

    return false;
}

int wylosuj(int ile)
{
  return( rand() % ile ) + 1;
}

void rysuj(int tab[], int z)
{
  for(int j=0; j<z; j++)
    {
      mvprintw(j, 0, "                        ");
      for(int i=0; i<tab[j]; i++)
        {
	  mvprintw(j, i, "#");
        }
      refresh();
      usleep(20000);
    }
}

void rysuj2(int tab[], int j)
{
  for(int jj=0; jj<LINES; jj++)
   {
      mvprintw(j, jj, " ");
   }
  for(int i=0; i<tab[j]; i++)
    {
      mvprintw(j, i, "#");
    }
  refresh();
}

void bubble_sort( int tab[], int size )
{
  int size2 = size;
  int s = 0;
  for( int i = 0; i < size; i++ )
    {
      for( int j = 0; j < size2 - 1; j++ )
        {
	  rysuj2(tab, j);
	  usleep(70000);
	  if( tab[ j ] > tab[ j + 1 ] )
            {
	      std::swap( tab[ j ], tab[ j + 1 ] );
	      rysuj2(tab, j);
	      rysuj2(tab, j+1);
	      s=0;
	      if(j+1 == size2-1) size2--;
            }
	  else s++;
	  if(j+1 == size2-1) size2-=s;
        }
    }
}

void comb_sort( int tab[], int size )
{
  int gap = size;
  bool replace = true;
    
  while( gap > 1 || replace )
    {
      gap = gap * 10 / 13;
      if( gap == 0 )
	gap = 1;
      mvprintw(gap, LINES+2, "*");
      replace = false;
      for( int i = 0; i + gap < size; i++ )
        {
	  //getch();
	  rysuj2(tab, i);
	  usleep(500000);
	  if( tab[ i + gap ] < tab[ i ] )
            {
	      std::swap( tab[ i ], tab[ i + gap ] );
	      replace = true;
	      //getch();
	      rysuj2(tab, i);
	      //getch();
	      rysuj2(tab, i+gap);
	      usleep(200000);
            }
        }
    }
}

void shake_sort( int tab[], int size)
{
  int bottom = 0, top = size - 1;
  bool replace = true;
    
  while( replace )
    {
      replace = false;
        
      for( int i = bottom; i < top; i++ )
        {
	  rysuj2(tab, i);
	  usleep(100000);
	  if( tab[ i ] > tab[ i + 1 ] )
            {
	      std::swap( tab[ i ], tab[ i + 1 ] );
              rysuj2(tab, i);
	      rysuj2(tab, i+1);
	      replace = true;
            }
        }
      top--;

      for( int i = top; i > bottom; i-- )
        {
	  rysuj2(tab, i);
	  usleep(100000);
	  if( tab[ i ] < tab[ i - 1 ] )
            {
	      std:: swap( tab[ i ], tab[ i - 1 ] );
              rysuj2(tab, i);
	      rysuj2(tab, i-1);
	      replace = true;
            }
        }
        
      bottom++;
    }
}

void insertion_sort( int tab[], int size )
{
  int temp, j;
    
  for( int i = 1; i < size; i++ )
    {
      temp = tab[ i ];
      rysuj2(tab, i);
      usleep(150000);
        
      for( j = i - 1; j >= 0 && tab[ j ] > temp; j-- )
	{
	  std::swap(tab[ j + 1 ], tab[ j ]);
	  rysuj2(tab, j+1);
	  rysuj2(tab, j);
	  usleep(100000); 
	}
      tab[ j + 1 ] = temp;
      rysuj2(tab, j+1);
      usleep(100000);
    }
}

void selection_sort( int tab[], int size )
{
  int k;
  for( int i = 0; i < size; i++ )
    {
      rysuj2(tab, i);
      usleep(100000);
      k = i;
      for( int j = i + 1; j < size; j++ )
	{
	  rysuj2(tab, j);
	  usleep(100000);
	  if( tab[ j ] < tab[ k ] )
	    {
	      k = j;
	      usleep(300000);
	    }
	}
      rysuj2(tab, k);
      usleep(400000);
      std::swap( tab[ k ], tab[ i ] );
      rysuj2(tab, k);
      rysuj2(tab, i);
      usleep(400000);
    }
}

void quick_sort( int tab[], int left, int right )
{
  int i = left;
  int j = right;
  int x = tab[( left + right ) / 2 ];
    do
      {
        while( tab[ i ] < x )i++;
        while( tab[ j ] > x )j--;
        if( i <= j )
	  {
	    std::swap( tab[ i ], tab[ j ] );
	    rysuj2(tab, i);
            usleep(150000);
	    rysuj2(tab, j);
            usleep(150000);
            i++;
            j--;
	  }
      } while( i <= j );
    if( left < j ) quick_sort( tab, left, j );
    if( right > i ) quick_sort( tab, i, right );
    
}

int Losuj(int wylosowane[], int L)
{
int wylosowanych = 0;
   do
     {
       int liczba = wylosuj(L);
       if( czyBylaWylosowana( liczba, wylosowane, wylosowanych ) == false )
	 {
	   wylosowane[ wylosowanych ] = liczba;
	   wylosowanych++;
	 } //if
     } while( wylosowanych < L );

   wylosowanych = 0;
    do
      {
        wylosowanych++;
      } while( wylosowanych < L );
}
int main()
{
  srand(time(NULL));
  //start
  initscr();
  int wylosowane[LINES];
  printw( "Przycisnij przycisk...\n" );
  printw("Ekran: %d x %d", LINES, COLS);
  noecho();
  //rozpoczynamy wyswietlanie menu!
  const char txt1[] = "Sortowanie babelkowe (ang. bubble sort)";
  const char txt2[] = "Sortowanie grzebieniowe (ang. comb sort)";
  const char txt3[] = "Sortowanie koktajlowe (ang. shake sort)";
  const char txt4[] = "Sortowanie przez wstawianie (ang. insertion sort)"; 
  const char txt5[] = "Sortowanie przez wybieranie (ang. selection sort)";
  const char txt6[] = "Sortowanie szybkie (ang. quick sort)";
  const char txt7[] = "Wyjscie";
  int ktory = 1;
  int znak, n = LINES;
  const short int min_wybor = 1;
  const short int max_wybor = 7;
    do
      {
        //pobieranie znaku
        znak = getch();
        clear();
        if( znak == 'a' && ktory != min_wybor )
	  {
            ktory--;
	  }
        else if( znak == 'z' && ktory != max_wybor )
	  {
            ktory++;
	  }
        //reakcja
        if( znak == 10 )
	  {
            switch( ktory )
	      {
	      case 1:
		clear();
		Losuj(wylosowane, n);
                rysuj(wylosowane, n);
		getch();
		bubble_sort(wylosowane, n);
		getch();
		clear();
                break;
	      case 2:
		clear();
                Losuj(wylosowane, n);
                rysuj(wylosowane, n);
		getch();
		comb_sort(wylosowane, n);
		getch();
		clear();
                break;
	      case 3:
		clear();
                Losuj(wylosowane, n);
                rysuj(wylosowane, n);
		getch();
		shake_sort(wylosowane, n);
		getch();
		clear();
                break;
	      case 4:
		clear();
                Losuj(wylosowane, n);
                rysuj(wylosowane, n);
		getch();
		insertion_sort(wylosowane, n);
		getch();
		clear();
                break;
	      case 5:
		clear();
                Losuj(wylosowane, n);
                rysuj(wylosowane, n);
		getch();
		selection_sort(wylosowane, n);
		getch();
		clear();
                break;
	      case 6:
		clear();
                Losuj(wylosowane, n);
                rysuj(wylosowane, n);
		getch();
		quick_sort(wylosowane, 0, n);
		getch();
		clear();
                break;
	      }
	  }
        //wyswietlanie
        switch( ktory )
	  {
	  case 1:
            mvprintw( 3, 5, txt2 );
            mvprintw( 4, 5, txt3 );
	    mvprintw( 5, 5, txt4 );
	    mvprintw( 6, 5, txt5 );
	    mvprintw( 7, 5, txt6 );
	    mvprintw( 8, 5, txt7 );
            attron( A_REVERSE );
            mvprintw( 2, 5, txt1 );
            break;

	  case 2:
            mvprintw( 2, 5, txt1 );
            mvprintw( 4, 5, txt3 );
	    mvprintw( 5, 5, txt4 );
	    mvprintw( 6, 5, txt5 );
	    mvprintw( 7, 5, txt6 );
	    mvprintw( 8, 5, txt7 );
            attron( A_REVERSE );
            mvprintw( 3, 5, txt2 );
            break;

	  case 3:
            mvprintw( 2, 5, txt1 );
            mvprintw( 3, 5, txt2 );
	    mvprintw( 5, 5, txt4 );
	    mvprintw( 6, 5, txt5 );
	    mvprintw( 7, 5, txt6 );
	    mvprintw( 8, 5, txt7 );
            attron( A_REVERSE );
            mvprintw( 4, 5, txt3 );
            break;

	  case 4:
            mvprintw( 2, 5, txt1 );
            mvprintw( 3, 5, txt2 );
	    mvprintw( 4, 5, txt3 );
	    mvprintw( 6, 5, txt5 );
	    mvprintw( 7, 5, txt6 );
	    mvprintw( 8, 5, txt7 );
            attron( A_REVERSE );
	    mvprintw( 5, 5, txt4 );
	    break;

	  case 5:
            mvprintw( 2, 5, txt1 );
            mvprintw( 3, 5, txt2 );
	    mvprintw( 5, 5, txt4 );
	    mvprintw( 4, 5, txt3 );
	    mvprintw( 7, 5, txt6 );
	    mvprintw( 8, 5, txt7 );
            attron( A_REVERSE );
            mvprintw( 6, 5, txt5 );
            break;

	  case 6:
            mvprintw( 2, 5, txt1 );
            mvprintw( 3, 5, txt2 );
	    mvprintw( 5, 5, txt4 );
	    mvprintw( 6, 5, txt5 );
	    mvprintw( 4, 5, txt3 );
	    mvprintw( 8, 5, txt7 );
            attron( A_REVERSE );
            mvprintw( 7, 5, txt6 );
            break;

	  case 7:
            mvprintw( 2, 5, txt1 );
            mvprintw( 3, 5, txt2 );
	    mvprintw( 5, 5, txt4 );
	    mvprintw( 6, 5, txt5 );
	    mvprintw( 7, 5, txt6 );
	    mvprintw( 4, 5, txt3 );
            attron( A_REVERSE );
            mvprintw( 8, 5, txt7 );
            break;
	  }
        attroff( A_REVERSE );
      } while( ktory != 7 || znak != 10 );

    move( 9, 0 );
    printw( "Koniec programu, przycisnij przycisk..." );
    getch();
    endwin();

}
