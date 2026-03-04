#pragma once

#ifdef __cplusplus
extern "C"{
#endif

typedef struct TestClass TestClass; // class to struct?

TestClass* TestClass_Create();
int TestClass_GetCoolInt(TestClass*);

#ifdef __cplusplus
}
#endif