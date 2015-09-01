// started from concat_proplist . Support complex numbers
// added main/utils subdirectory with some useful main programs...
//
//

#include <iostream>
#include <cstdio>

#include "covfit/statistics.h"
#include "covfit/proplist.h"




using namespace std;
using namespace CovFit ;

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    cerr << "Usage: " << argv[0] << " <concat proplist>  <proplist> ..." ; 
    cerr << endl;
    exit(1);
  }

  int Nx, Nt ;
  int Nfiles = argc-2 ;
  cout << "Number of files: "<<Nfiles<<endl ;
  cPropList pp ;
  Array<cPropList> all(Nfiles);
  cPropList av ;

  int totalCnfs(0) ;
  
  for(int i(2);i<argc;i++){
    int ttNx= ReadProplist(all[i-2],argv[i]);
    int ttNt = all[i-2][0].size() ;
    if(i==2){
      Nx=ttNx ;
      Nt=ttNt ;
    }
    if(Nx!=ttNx){
      cerr<<"Nx: "<<Nx<<" ttNx: "<<ttNx<<endl ;
      cerr<<"OOPS! wrong proplist header\n" ;
      exit(2);
    }
    if(Nt!=ttNt){ 
      cerr<<"Nt: "<<Nt<<" ttNt: "<<ttNt<<endl ;
      cerr<<"OOPS! wrong propagator length\n" ;
      exit(1);
    }
    
    totalCnfs += all[i-2].size() ;
  }
  av.resize(totalCnfs) ;
  for(int i(0);i<totalCnfs;i++)
    av[i].resize(Nt) ;

  int c(0) ;
  for(int i(0);i<Nfiles;i++){
    for(int k(0);k<all[i].size();k++){
      av[c] = all[i][k] ;
      c++;
    }
  }
  
  WriteProplist(av,Nx,argv[1]);
  
}
