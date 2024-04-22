#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

bool flag = false;

void *setFlag(void *arg)
{
    sleep(2); // 模拟一些处理过程
    flag = true;
    printf("Flag set to true\n");
    return NULL;
}

int main()
{
    pthread_t flag_thread;

    printf("Program started\n");
    pthread_create(&flag_thread, NULL, setFlag, NULL); // 创建一个线程来设置flag

    // 主线程中的轮询
    while (!flag)
    {
        // 在这个循环中，如果没有使用volatile，编译器可能会优化这个循环
        // 并认为flag值永远不会改变，导致这个循环变成无限循环
        // 为了避免编译器优化，我们可以添加一个伪操作，如下面的printf
        printf("Waiting for flag to become true\n");
    }

    pthread_join(flag_thread, NULL); // 等待线程结束
    printf("Flag detected as true\n");
    return 0;
}
