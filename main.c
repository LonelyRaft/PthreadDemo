#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE_TEXT_BUFF 128

pthread_mutex_t mt_file = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mt_buff = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    char *path;
    int handle;
} File;

void *monitor_task(void *param)
{
    struct stat fst_text;
    time_t mtime;
    off_t size;
    File *file;
    char buff[SIZE_TEXT_BUFF];
    file = (File *)param;
    mtime = 0;
    pthread_detach(pthread_self());
    while (1)
    {
        pthread_mutex_lock(&mt_file);
        stat(file->path, &fst_text);
        if (mtime != fst_text.st_mtime)
        {
            mtime = fst_text.st_mtime;
            pthread_mutex_unlock(&mt_file);
            printf("%lld changed!\n", mtime);
        }
        else
        {
            pthread_mutex_unlock(&mt_file);
            printf("no change!\n");
        }
        sleep(1);
    }
    return 0;
}

void *producer_task(void *param)
{
    char data[] = {"abcdefgijklmnopqrstuvwxyz0123456789\n"}; // 数据源
    char *buff = (char *)param;                              // 目的地址
    int idx, size;                                           // 缓冲区索引，缓冲区大小
    // size = SIZE_TEXT_BUFF - 1;
    size = sizeof(data);
    pthread_detach(pthread_self());
    while (1)
    {
        idx = 0;
        pthread_mutex_lock(&mt_buff);
        for (idx = 0; idx < size; idx++)
            buff[idx] = data[idx];
        pthread_mutex_unlock(&mt_buff);
        sleep(5);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    char *buff;
    File file;
    file.path = "text.txt";
    file.handle = open(file.path, O_CREAT | O_RDWR);
    buff = (char *)malloc(SIZE_TEXT_BUFF);
    if (0 < file.handle && 0 != buff)
    {
        pthread_t thd_monitor, thd_producer;
        if (pthread_create(&thd_monitor, 0, monitor_task, &file) ||
            pthread_create(&thd_producer, 0, producer_task, buff))
        {
            close(file.handle);
            free(buff);
            return 0;
        }
        while (1)
        {
            pthread_mutex_lock(&mt_file);
            pthread_mutex_lock(&mt_buff);
            write(file.handle, buff, strlen(buff));
            pthread_mutex_unlock(&mt_buff);
            pthread_mutex_unlock(&mt_file);
            sleep(5);
        }
    }
    if (0 < file.handle)
        close(file.handle);
    if (0 != buff)
        free(buff);
    return 0;
}
