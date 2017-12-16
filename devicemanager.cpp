#include "devicemanager.h"

DeviceManager::DeviceManager()
{
    list = new Device[40];
    for(int i = 0; i < 40; i++){
        list[i].hw_path = new char[256];
        list[i].file_path = new char[256];
        list[i].svendor = new char[256];
        list[i].vendor = new char[256];
        list[i].slot = new char[256];
        list[i].full_info = new char[1024];
        list[i].driver_name = new char[256];

        list[i].hw_path[0] = '\0';
        list[i].file_path[0] = '\0';
        list[i].svendor[0] = '\0';
        list[i].vendor[0] = '\0';
        list[i].slot[0] = '\0';
        list[i].full_info[0] = '\0';
        list[i].driver_name[0] = '\0';

    }
}

DeviceManager::~DeviceManager()
{
    for(int i = 0; i < 40; i++){
        delete(list[i].hw_path);
        delete(list[i].file_path);
        delete(list[i].svendor);
        delete(list[i].vendor);
        delete(list[i].slot);
        delete(list[i].full_info);
        delete(list[i].driver_name);
    }
    delete(list);
}

void DeviceManager::getDeviceList()
{
    char* result = new char[8192];
    char* tmp = new char[128];
    int i = 0;
    getCommandLine("lspci -vmm", result);
    for(; strstr(result, "Slot"); i++)
    {
        getField(result, tmp, "Slot", 0, '\n');
        strcpy(list[i].hw_path, tmp);
        strcat(list[i].full_info, tmp);

        getField(result, tmp, "Class", 0, '\n');
        if(strlen(tmp) < 30){
            strcat(tmp, "\t");
            if(strlen(tmp) < 21)
                strcat(tmp, "\t");
        }

        strcpy(list[i].slot, tmp);
        strcat(list[i].full_info, tmp);

        getField(result, tmp, "Vendor", 0, '\n');
        if(strlen(tmp) < 30){
            strcat(tmp, "\t");
        }
        strcpy(list[i].vendor, tmp);
        strcat(list[i].full_info, tmp);

        if(strstr(result, "SVendor") &&
           (strstr(result, "Slot") > strstr(result, "SVendor") ||
           !strstr(result, "Slot"))){
            getField(result, tmp, "SVendor", 0, '\n');

        }
        else{
            tmp[0] = '\0';
            strcat(tmp, "\t\t\t\t");
        }
        strcpy(list[i].svendor, tmp);
        strcat(list[i].full_info, tmp);

        strcpy(result, result + 1);
    }

    size = i;
    getDriverName();
    delete(tmp);
    delete(result);
}

void DeviceManager::getDriverName()
{
    char* result = new char[128];
    char* command = new char[128];

    for(int i = 0; i < size; i++){
        strcpy(command, "lspci -v -s ");
        strcat(command, list[i].hw_path);
        command[strlen(command) - 1] = '\0';
        strcpy(command + 12, command + 18);
        strcat(command, " | grep \'Kernel driver in use\'");
        getCommandLine(command, result);
        if(!strstr(result, "driver")){
            result[0] = '\0';
        }else{
            result[strlen(result)-1] = '\0';
            strcpy(list[i].driver_name, result + 22);
            //list[i].driver_name[strlen(list[i].driver_name)] = '\0';
            cout <<"!@# " <<
                   list[i].driver_name <<
                   " !@# " <<
                   strlen(list[i].driver_name) <<
                   endl;
            strcat(list[i].full_info, result + 1);
        }
    }

    delete(command);
    delete(result);
}

Device *DeviceManager::getList() const
{
    return list;
}

int DeviceManager::getSize() const
{
    return size;
}

int DeviceManager::getCommandLine(const char *command, char* result)
{
    result[0] = '\0';
    char* tmp = new char[256];
    FILE *file = popen(command, "r");
    if(!file)
    {
        cout << "Open error" << endl;
        return 0;
    }
    int i = 0;
    for(i = 0; fgets(tmp, 256, file); i++)
        strcat(result, tmp);
    pclose(file);
    delete(tmp);
    return i;
}

void DeviceManager::getField(char *source, char *destination, const char *field_name, int offset, const char last_sign)
{
    int i = 0;
    strcpy(source, strstr(source, field_name) + offset);
    for(i = 0; source[i] != last_sign; i++)
        destination[i] = source[i];
    destination[i++] = '\t';
    if(i < 12) destination[i++] = '\t';
    destination[i] = '\0';
}

void DeviceManager::createCommand(char **lego, int num)
{
    for(int i = 1; i < num; i++)
        strcat(lego[0], lego[i]);
}
