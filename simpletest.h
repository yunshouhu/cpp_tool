#ifndef UNITTEST_H
#define UNITTEST_H
#include <stdio.h>



 #define TEST_OK 0
 #define TEST_RESULT char*
 #define TEST_ASSERT(message, test) do { if (!(test))return message; } while (0);
 #define RUN_TEST(test) do { \
 char *message = test(); \
 nr_tests_run++;\
 if (message){printf("Test nr %d: " #test "( %s ) FAILED !!! \n",nr_tests_run,message);return message;}\
 else{printf("Test nr %d: " #test " OK...\n",nr_tests_run);} \
 } while (0);
 
 #define DECLARE_FIXTURE(name) char* run_tests_##name(){\
 puts("\n\n Testing fixture: " #name);\
 puts("______________________________\n");\
 int nr_tests_run=0;
 
 #define END_FIXTURE return 0;} 
 #define RUN_FIXTURE(name) do{ if(run_tests_##name()==0) {printf("ALL TESTS PASSED\n"); } }while(0);
		 
#endif
