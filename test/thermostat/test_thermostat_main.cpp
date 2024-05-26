#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"


#if ON_TARGET

   #include "pico/stdlib.h"

   void setup() {
      stdio_init_all();
   }
#else 
   void setup() {
   }
#endif


int main(int ac, char** av)
{  
   setup();

   int num = 2;
   const char* args[2] = {"", "-c"};


   return CommandLineTestRunner::RunAllTests(num, args);
}