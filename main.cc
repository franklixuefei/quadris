#include <iostream>
#include <string>
#include "quadris.h"

using namespace std;

int main (int argc, char* argv[]) {
   uint32_t seed = DEFAULT_SEED;
   bool text = false;
   for (int i = 1; i < argc; ++i) {
      string arg = (string)argv[i];
      if (arg == "-seed") {
         ++i;
         string temp = (string)argv[i];
         istringstream iss(temp);
         iss >> seed;
      }
      else if (arg == "-text") {
         text = true;
      }
   }
   if (text) {
      Quadris q;
      q.setSeed(seed);
      q.runQuadris();
   } else {
      Xwindow xw1(20*MAX_COL,70 + 20*MAX_ROW);
      Xwindow xw2(180, 10+60);
      Quadris q(&xw1, &xw2);
      q.setSeed(seed);
      q.runQuadris();
   }

   return 0;
}
