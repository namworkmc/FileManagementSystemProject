#include "ReadSector.h"
#include "NTFSPartitionBootSector.h"

using namespace std;

void subB(BYTE sector[], int x, int y) {
    for (int i = x; i <= y; ++i)
        cout << sector[i];
    cout << endl; 
}

void subB_dec(BYTE sector[], int x, int y) {
    int result = 0;
    for (int i = y; i >= x; --i)
        result = (result << 8) | sector[i];
    cout << result << endl;
}

void subB_hex(BYTE sector[], int x, int y) {
    cout << hex << setfill('0');
    for (int i = x; i <= y; ++i) {
        cout << setw(2) << int(sector[i]) << ' ';
    }
    cout << dec << endl;
}

// sau lenh ReadSector(...) goi asNTFS(sector);
void asNTFS(BYTE s[512]) {

    cout << "JMP instruction: ";
    subB_hex(s, 0x00, 0x02);

    cout << "OEM ID: ";
    subB(s, 0x03, 0x0a);

    cout << "Bytes per sector: ";
    subB_dec(s, 0x0b, 0x0c);

    cout << "Sectors per cluster: ";
    subB_dec(s, 0x0d, 0x0d);

    cout << "Reserved sectors: ";
    subB_dec(s, 0x0e, 0x0f);

    cout << "(always zero): ";
    subB_dec(s, 0x10, 0x12);

    cout << "Media descriptor: ";
    subB_dec(s, 0x15, 0x15);

    cout << "Sectors per track: ";
    subB_dec(s, 0x18, 0x19);

    cout << "Number of heads: ";
    subB_dec(s, 0x1A, 0x1B);

    cout << "Hidden sectors: ";
    subB_dec(s, 0x1C, 0x1F);

    cout << "Signature: ";
    subB_hex(s, 0x24, 0x27);

    cout << "Total sectors: ";
    subB_dec(s, 0x28, 0x2f);

    cout << "$MFT logical cluster number: ";
    subB_dec(s, 0x30, 0x37);

    cout << "$MFTMirr logical cluster number: ";
    subB_dec(s, 0x38, 0x3f);

    cout << "Clusters per File Record Segment: ";
    subB_dec(s, 0x40, 0x43);

    cout << "Clusters per Index Buffer: ";
    subB_dec(s, 0x44, 0x47);

    cout << "Volume serial number: ";
    subB_hex(s, 0x48, 0x4f);

    cout << "Checksum: ";
    subB_dec(s, 0x50, 0x53);

    //cout << "Boostrap code: ";
    //subB_hex(s, 0x54, 0x1FD);

    cout << "Signature (55 AA): ";
    subB_hex(s, 0x1FE, 0x1FF);
}

int main(int argc, char** argv)
{
    BYTE sector[512];
    ReadSector(L"\\\\.\\J:", 0, sector);

     /* TEST CASE
        BYTE sector[512] = { 
        235,82,144,78,84,70,83,32,  32,32,32,0,2,8,0,0,
        0,0,0,0,0,248,0,0,          63,0,255,0,63,0,0,0,
        0,0,0,0,128,0,0,0,          192,111,120,0,0,0,0,0,
        0,0,4,0,0,0,0,0,            2,0,0,0,0,0,0,0,
        246,0,0,0,1,0,0,0,          94,160,230,212,228,230,212,252,
        0,0,0,0,250,51,192,142,     208,188,0,124,251,104,192,7,
        31,30,104,102,0,203,136,22, 14,0,102,129,62,3,0,78,
        84,70,83,117,21,180,65,187,170,85,205,19,114,12,129,251,85,170,117,6,247,193,1,0,117,3,233,221,0,30,131,236,24,104,26,0,180,72,138,22,14,0,139,244,22,31,205,19,159,131,196,24,158,88,31,114,225,59,6,11,0,117,219,163,15,0,193,46,15,0,4,30,90,51,219,185,0,32,43,200,102,255,6,17,0,3,22,15,0,142,194,255,6,22,0,232,75,0,43,200,119,239,184,0,187,205,26,102,35,192,117,45,102,129,251,84,67,80,65,117,36,129,249,2,1,114,30,22,104,7,187,22,104,82,17,22,104,9,0,102,83,102,83,102,85,22,22,22,104,184,1,102,97,14,7,205,26,51,192,191,10,19,185,246,12,252,243,170,233,254,1,144,144,102,96,30,6,102,161,17,0,102,3,6,28,0,30,102,104,0,0,0,0,102,80,6,83,104,1,0,104,16,0,180,66,138,22,14,0,22,31,139,244,205,19,102,89,91,90,102,89,102,89,31,15,130,22,0,102,255,6,17,0,3,22,15,0,142,194,255,14,22,0,117,188,7,31,102,97,195,161,246,1,232,9,0,161,250,1,232,3,0,244,235,253,139,240,172,60,0,116,9,180,14,187,7,0,205,16,235,242,195,13,10,65,32,100,105,115,107,32,114,101,97,100,32,101,114,114,111,114,32,111,99,99,117,114,114,101,100,0,13,10,66,79,79,84,77,71,82,32,105,115,32,99,111,109,112,114,101,115,115,101,100,0,13,10,80,114,101,115,115,32,67,116,114,108,43,65,108,116,43,68,101,108,32,116,111,32,114,101,115,116,97,114,116,13,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,138,1,167,1,191,1,0,0,85,170 };/**/

    asNTFS(sector);
    return 0;
}