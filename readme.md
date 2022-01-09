
# 监视文件是否有变化

练习内容：
- 主线程负责改变文件内容，一个子线程负责生成数据，另一个子线程负责监视文件是否有变化。
- 线程之间使用互斥量或者条件变量进行同步。

练习目标：

1、创建一个线程

- pthread_attr_init
- pthread_attr_destroy
- pthread_attr_setxxxx
- pthread_attr_getxxxx
- pthread_create
- pthread_exit
- pthread_self
- pthread_equal
- pthread_join
- pthread_detach

2、互斥量同步

- pthread_mutexattr_init
- pthread_mutexattr_destroy
- pthread_mutexattr_setxxxx
- pthread_mutexattr_getxxxx
- pthread_mutex_init
- pthread_mutex_destroy
- pthread_mutex_lock
- pthread_mutex_trylock
- pthread_mutex_timedlock
- pthread_mutex_unlock

3、条件变量同步

- pthread_cond_init
- pthread_cond_destroy
- pthread_cond_signal
- pthread_cond_broadcast
- pthread_cond_wait
- pthread_cond_timedwait