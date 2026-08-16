  #include <stdio.h>
  int main(int argc, char *argv[])
  {
    
    if(argc < 3 || argc > 3)
    {
      printf("Usage: ./assignment9 Firstname Lastname");
    }
    else
    {
      printf("Hello, %s %s", argv[1], argv[2]);
    }
    return 0;
  }


### 正确运行：./assignment9 Alice Lee

输出：Hello, Alice Lee
