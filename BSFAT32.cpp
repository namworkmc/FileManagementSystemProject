#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,       // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }
}

//Convert to hex 
string HexConvert(BYTE sector[])
{
    stringstream hexSs;
    for (int i = 0; i < 512; i++)
        hexSs << hex << setw(2) << setfill('0') << (int)sector[i];
    return hexSs.str();
}

//Convert hex to dec
int DecConvert(string hex)
{
    unsigned long result = 0;

    for (int i = 0; i < hex.length(); i++) {
        if (hex[i] >= 48 && hex[i] <= 57)
        {
            result += (hex[i] - 48) * pow(16, hex.length() - i - 1);
        }
        else if (hex[i] >= 65 && hex[i] <= 70) {
            result += (hex[i] - 55) * pow(16, hex.length() - i - 1);
        }
        else if (hex[i] >= 97 && hex[i] <= 102) {
            result += (hex[i] - 87) * pow(16, hex.length() - i - 1);
        }
    }
    return result;
}

void type(string hex)
{
    string str = hex.substr(0x52 * 2, 16);
    for (int i = 0; i < 16; i += 2)
    {
        string sub = str.substr(i, 2);
        cout << char(DecConvert(sub));
    }
    cout << endl;
}

void changeData(string hex, int start, int numbit)
{
    string a = hex.substr(start , numbit);

    string b = "";

    for (int i = a.size() - 2; i >= 0; i -= 2)
    {
        b += a.substr(i, 2);
        
    }
    cout << DecConvert(b) << endl;
}

void BootSectorFAT32(BYTE sector[])
{
    string hex = HexConvert(sector);
    cout << "** Information is described in the Boot Sector: **" << endl;
    cout << "Type of FAT: ";
    type(hex);
    cout << "Number of bytes per sector: ";
    changeData(hex, 0x0B * 2, 4);
    cout << "Number of sector per cluster: ";
    changeData(hex, 0x0D * 2, 2);
    cout << "Number of sectors in the bootsector: ";
    changeData(hex, 0x0E * 2, 4);
    cout << "Number of FAT table: ";
    changeData(hex, 0x10 * 2, 2);
    cout << "Size of volume : ";
    changeData(hex, 0x20 * 2, 8);
    cout << "Size of per FAT table: ";
    changeData(hex, 0x24 * 2, 8);
    cout << "Begin cluster of RDET: ";
    changeData(hex, 0x2C * 2, 8);
    cout << "Sector contains extra information ( about empty cluster ): ";
    changeData(hex, 0x30 * 2, 4);
    cout << "Sector contains the save version of Boot Sector: ";
    changeData(hex, 0x32 * 2, 4);
}


int main(int argc, char** argv)
{
    BYTE sector[512];
    ReadSector(L"\\\\.\\D:", 0, sector);
    BootSectorFAT32(sector);

}