#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include "stdafx.h"
#include "/home/vladiislav/Документы/iipu6_1/iipu6_1/wifi.h"

struct Device{
    char* vendor;   //manufacturer
    char* svendor;  //provider
    char* file_path;
    char* hw_path;
    char* slot;
    char* full_info;
    char* driver_name;
};

class DeviceManager
{
    Device* list;
    int size;
public:
    DeviceManager();
    ~DeviceManager();
    void getDeviceList();
    void getDriverName();  //vendor + sub_vendor

    Device *getList() const;
    int getSize() const;

    static int getCommandLine(const char* command, char* result);
    static void getField(char* source, char* destination, const char* field_name, int offset, const char last_sign);
    static void createCommand(char**, int);
};

#endif // DEVICEMANAGER_H
