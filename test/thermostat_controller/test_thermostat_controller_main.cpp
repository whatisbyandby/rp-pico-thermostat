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

   return CommandLineTestRunner::RunAllTests(ac, av);
}