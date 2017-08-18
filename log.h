#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include <string.h>
#define LOGE(fmt, ...) printf("[E][%s.%d]: " fmt "\n", strrchr(__FILE__, '/') + 1, __LINE__, ## __VA_ARGS__)
#define LOGW(fmt, ...) printf("[D][%s.%d]: " fmt "\n", strrchr(__FILE__, '/') + 1, __LINE__, ## __VA_ARGS__)
#define LOGD(fmt, ...) printf("[W][%s.%d]: " fmt "\n", strrchr(__FILE__, '/') + 1, __LINE__, ## __VA_ARGS__)

#endif // LOG_H
