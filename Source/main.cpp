#include <QApplication>

#include <iostream>
using namespace std;
#include "JoypadListener.hpp"

int main(int argc, char* argv[])
{
  QApplication a( argc, argv );
  cout << "Hello world" << endl;
    
  JoypadListener listener;
  a.exec();
  
  //while(true);
}

