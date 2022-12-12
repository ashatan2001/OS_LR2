#include <iostream>
#include <Windows.h>
#include <string>
#include <map>
using std::cout;
using std::cin;
using std::endl;

using namespace std;


void menu();
void helpMBI();
void getSystemInfo();
void getMemStatus();
void getStateMemArea();
void memReserve();
void memAlloc();
void writeData();
void setProtect();
void memFree();

int main() {
    int item = 0;

    do {
        menu();
        while (!(cin >> item) || (cin.peek() != '\n'))
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "  Input error. Repeat...\n";
        }
        system("cls");

        switch (item) {
        case 1:
            getSystemInfo();
            break;
        case 2:
            getMemStatus();
            break;
        case 3:
            helpMBI();
            getStateMemArea();
            break;
        case 4:
            memReserve();
            break;
        case 5:
            memAlloc();
            break;
        case 6:
            writeData();
            break;
        case 7:
            setProtect();
            break;
        case 8:
            memFree();
            break;
        case 0:
            break;
        default:
            cout << "  Non-existent menu item" << endl;
            break;
        }

        cout << endl;
        system("pause");
        system("cls");
    } while (item);

    return 0;
}

// Подправить названия (5, 8)
void menu() {
    cout << "  1. Get system info" << endl;
    cout << "  2. Get virtual memory status" << endl;
    cout << "  3. Identify state of memory area" << endl;
    cout << "  4. Region reservation" << endl;
    cout << "  5. Region reservation and physical" << endl;
    cout << "     memory transfer" << endl;
    cout << "  6. Write data to memory cells" << endl;
    cout << "  7. Set access protection for the" << endl;
    cout << "     region memory with check" << endl;
    cout << "  8. Return physical memory and free" << endl;
    cout << "     of the address region space" << endl;
    cout << "  0. Exit" << endl << endl;

    cout << "  Choose item: ";
}

void helpMBI() {
    int item;

    do {
        cout << "  Output with help?" << endl;
        cout << "    1. Yes" << endl;
        cout << "    0. No" << endl;
        cout << "  Choose an action: ";

        cin >> item;

        if (item != 0 && item != 1) {
            cout << "\n  Input error. Repeat..." << endl;
            system("pause");
        }
        system("cls");
    } while (item != 0 && item != 1);

    if (item) {
        cout << "  Memory basic information help:" << endl;
        cout << "    Base Address - a pointer to the base address of the region of pages" << endl << endl;

        cout << "    Allocation base - a pointer to the base address of a range of pages allocated by the VirtualAlloc function" << endl << endl;

        cout << "    Region size - the size of the region beginning at the base address in which all pages have identical\n"
            "    attributes, in bytes" << endl << endl;

        cout << "    Allocation protect - the memory protection option when the region was initially allocated" << endl << endl;

        cout << "    State - indicates committed pages for which physical storage has been allocated, either in\n"
            "    memory or in the paging file on disk" << endl;
        cout << "    - MEM_COMMIT - indicates committed pages for which physical storage has been allocated, either in memory or in\n"
            "      the paging file on disk" << endl;
        cout << "    - MEM_FREE - indicates free pages not accessible to the calling process and available to be allocated" << endl;
        cout << "    - MEM_RESERVE - indicates free pages not accessible to the calling process and available to be allocated" << endl << endl;

        cout << "    Protect - the access protection of the pages in the region" << endl << endl;

        cout << "    Type - the type of pages in the region. The following types are defined" << endl;
        cout << "    - MEM_IMAGE - indicates that the memory pages within the region are mapped into the view of an image section" << endl;
        cout << "    - MEM_MAPPED - indicates that the memory pages within the region are mapped into the view of a section" << endl;
        cout << "    - MEM_RESERVE - indicates that the memory pages within the region are private (that is, not shared by other processes)" << endl << endl;
    }
    else system("cls");
}

void getSystemInfo() {
    map <unsigned long, string> oemId = {
       {PROCESSOR_ARCHITECTURE_AMD64,"PROCESSOR_ARCHITECTURE_AMD64"},
       {PROCESSOR_ARCHITECTURE_ARM,"PROCESSOR_ARCHITECTURE_ARM"},
       {PROCESSOR_ARCHITECTURE_ARM64, "PROCESSOR_ARCHITECTURE_ARM64"},
       {PROCESSOR_ARCHITECTURE_IA64,"PROCESSOR_ARCHITECTURE_IA64"},
       {PROCESSOR_ARCHITECTURE_INTEL,"PROCESSOR_ARCHITECTURE_INTEL"},
       {PROCESSOR_ARCHITECTURE_UNKNOWN,"PROCESSOR_ARCHITECTURE_UNKNOWN"}
    };
    SYSTEM_INFO sysInfo;

    GetSystemInfo(&sysInfo);

    printf("  Hardware information: \n");
    cout << "    OEM ID: " << oemId[sysInfo.dwOemId] << endl;
    printf("    Page size: %u\n", sysInfo.dwPageSize);
    printf("    Minimum application address: %p\n",
        sysInfo.lpMinimumApplicationAddress);
    printf("    Maximum application address: %p\n",
        sysInfo.lpMaximumApplicationAddress);
    printf("    Active processor mask: %u\n",
        sysInfo.dwActiveProcessorMask);
    printf("    Number of processors: %u\n", sysInfo.dwNumberOfProcessors);
    printf("    Processor type: %u\n", sysInfo.dwProcessorType);
    printf("    Allocation granularity: %u\n", sysInfo.dwAllocationGranularity);
    printf("    Processor level: %u\n", sysInfo.wProcessorLevel);
    printf("    Processor revision: %u\n", sysInfo.wProcessorRevision);
}

void getMemStatus() {
    MEMORYSTATUS ms;

    GlobalMemoryStatus(&ms);

    cout << "  Memory Status:" << endl;
    cout << "    Size MEMORYSTATUS data structure: " << ms.dwLength << endl;
    cout << "    Used physical memory: " << ms.dwMemoryLoad << " %" << endl;
    cout << "    Total physical memory: " << ms.dwTotalPhys << endl;
    cout << "    Available physical memory: " << ms.dwAvailPhys << endl;
    cout << "    Total page file memory: " << ms.dwTotalPageFile << endl;
    cout << "    Available page file: " << ms.dwAvailPageFile << endl;
    cout << "    Total virtual memory: " << ms.dwTotalVirtual << endl;
    cout << "    Available virtual memory: " << ms.dwAvailVirtual << endl;
}

void getStateMemArea() {
    MEMORY_BASIC_INFORMATION memInfo;
    MEMORYSTATUS buffer;
    LPVOID address = NULL;

    cout << "  Enter address: 0x";
    cin >> std::hex >> address;

    GlobalMemoryStatus(&buffer);
    if (!VirtualQuery(address, &memInfo, sizeof(buffer))) {
        cout << "\n  Error " << GetLastError() << endl;
        return;
    }

    cout << "\n  Memory basic information:" << endl;
    cout << "    Base address: " << memInfo.BaseAddress << endl;
    cout << "    Allocation base: " << memInfo.AllocationBase << endl;
    cout << "    Allocation protect: " << memInfo.AllocationProtect << endl;
    cout << "    Region size: " << memInfo.RegionSize << endl;

    cout << "    State: ";
    switch (memInfo.State) {
    case MEM_FREE:
        cout << "MEM_FREE" << endl;
        break;
    case MEM_RESERVE:
        cout << "MEM_RESERVE" << endl;
        break;
    case MEM_COMMIT:
        cout << "MEM_COMMIT" << endl;
        break;
    default:
        cout << memInfo.State << endl;
        break;
    }

    cout << "    Protect: " << memInfo.Protect << endl;

    cout << "    Type: ";
    switch (memInfo.Type) {
    case MEM_PRIVATE:
        cout << "MEM_PRIVATE" << endl;
        break;
    case MEM_IMAGE:
        cout << "MEM_IMAGE" << endl;
        break;
    case MEM_MAPPED:
        cout << "MEM_MAPPED" << endl;
        break;
    default:
        cout << memInfo.Type << endl;
        break;
    }
}

void memReserve() {
    LPVOID address = NULL;
    SIZE_T size;
    int item = 0;

    // Выбор режима
    do {
        cout << "  Choose mode:" << endl;
        cout << "    1. Automatic" << endl;
        cout << "    2. Enter address" << endl;
        cout << "  Item: ";

        cin >> item;

        if (item != 1 && item != 2) {
            cout << "\n  Input error. Repeat..." << endl;
            system("pause");
        }
        system("cls");
    } while (item != 1 && item != 2);

    if (item == 2) {
        cout << "  Enter address: 0x";
        cin >> std::hex >> address;
    }

    cout << "  Enter size (in bytes): ";
    cin >> size;

    if (address = VirtualAlloc(address, size, MEM_RESERVE, PAGE_READWRITE)) {
        cout << "\n  Memory reserved at address 0x" << address << endl;
    }
    else
        cout << "\n  Error " << GetLastError() << ".  No memory reserved" << endl;
}

void memAlloc() {
    LPVOID address = NULL;
    SIZE_T size;
    int item = 0;

    // Выбор режима
    do {
        cout << "  Choose mode:" << endl;
        cout << "    1. Automatic" << endl;
        cout << "    2. Enter address" << endl;
        cout << "  Item: ";

        cin >> item;

        if (item != 1 && item != 2) {
            cout << "\n  Input error. Repeat..." << endl;
            system("pause");
        }
        system("cls");
    } while (item != 1 && item != 2);

    if (item == 2) {
        cout << "  Enter address: 0x";
        cin >> std::hex >> address;
    }

    cout << "  Enter size (in bytes): ";
    cin >> size;

    if (address = VirtualAlloc(address, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE)) {
        cout << "\n  Memory reserved and commited at address 0x" << address << endl;
    }
    else
        cout << "\n  Error " << GetLastError() << ". No memory reserved abd commited" << endl;
}

void writeData() {
    MEMORY_BASIC_INFORMATION memInfo;
    LPVOID address = nullptr;
    int* data;
    int num;

    cout << "  Enter address: 0x";
    cin >> std::hex >> address;

    if (!address) {
        cout << "\n  Address is null" << endl;
        return;
    }

    // Получение информации о доступе
    if (!VirtualQuery(address, &memInfo, sizeof(memInfo))) {
        cout << "  Error " << GetLastError() << endl;
        return;
    }

    if (memInfo.State != MEM_COMMIT) {
        cout << "  Error. No memory commited\n";
        return;
    }

    // Запись данных
    data = (int*)address;
    cout << "  Enter integer to write memory: ";
    cin >> std::dec >> num >> std::hex;
    *data = num;
    cout << "  Data " << dec << *(int*)address << " write at address " << address << endl;
}

void setProtect() {
    map <unsigned long, string> protectConsts = {
        {PAGE_EXECUTE,"PAGE_EXECUTE"},
        {PAGE_EXECUTE_READ,"PAGE_EXECUTE_READ"},
        {PAGE_EXECUTE_READWRITE,"PAGE_EXECUTE_READWRITE"},
        {PAGE_EXECUTE_WRITECOPY,"PAGE_EXECUTE_WRITECOPY"},
        {PAGE_NOACCESS, "PAGE_NOACCESS"},
        {PAGE_READONLY,"PAGE_READONLY"},
        {PAGE_READWRITE,"PAGE_READWRITE"},
        {PAGE_WRITECOPY, "PAGE_WRITECOPY"},
        {PAGE_TARGETS_INVALID,"PAGE_TARGETS_INVALID"},
        {PAGE_TARGETS_NO_UPDATE,"PAGE_TARGETS_NO_UPDATE"}
    };
    MEMORY_BASIC_INFORMATION memInfo;
    DWORD oldProtect, newProtect;
    LPVOID address = nullptr;
    int item;
    int i = 0;

    cout << "  Enter address: 0x";
    cin >> std::hex >> address;

    if (!address) {
        cout << "\n  Address is null" << endl;
        return;
    }

    // Получение информации о текущей защите
    if (!VirtualQuery(address, &memInfo, sizeof(memInfo))) {
        cout << "  Error " << GetLastError() << endl;
        return;
    }

    if (memInfo.State != MEM_COMMIT) {
        cout << "  Error. No memory commited\n";
        return;
    }

    cout << "\n  Current type of protection at address " << memInfo.BaseAddress
        << " size " << memInfo.RegionSize << ": "
        << (memInfo.Protect == 0 ? "No access" : protectConsts.find(memInfo.Protect)->second) << endl << endl;

    // Выбор новой защиты
    cout << "  Choose type of protection:" << endl;
    for (auto const& x : protectConsts) 
        cout << "    " << i++ << ". " << x.second << endl;

    cout << "  Item: ";
    cin >> item;

    // Установка новой защиты
    newProtect = std::next(protectConsts.begin(), item)->first;

    if (VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, newProtect, &oldProtect))
    {
        cout << "\n  Current type of protection at address 0x" << address
            << " size " << memInfo.RegionSize << ": "
            << protectConsts.find(newProtect)->second << endl;
        cout << "  Previous type of protection: "
            << protectConsts.find(oldProtect)->second << endl;
    }
    else 
        cout << "\n  Error " << GetLastError() << ". No set type of protection" << endl;
}

void memFree() {
    MEMORY_BASIC_INFORMATION memInfo;
    LPVOID address = NULL;
    SIZE_T size;
    int item = 0;

    do {
        cout << "  Choose free type:" << endl;
        cout << "    1. Free region" << endl;
        cout << "    2. Return memory" << endl;
        cout << "  Item: ";

        cin >> item;

        if (item != 1 && item != 2) {
            cout << "\n  Input error. Repeat..." << endl;
        }
        system("cls");
    } while (item != 1 && item != 2);

    cout << "  Enter address: 0x";
    cin >> std::hex >> address;

    if (!VirtualQuery(address, &memInfo, sizeof(memInfo))) {
        cout << "  Error " << GetLastError() << endl;
        return;
    }

    switch (item) {
    case 1:

        if (memInfo.State != MEM_RESERVE) {
            cout << "  Error. No memory reserved\n";
            return;
        }

        if (VirtualFree(address, 0, MEM_RELEASE))
            cout << "  Memory released at address 0x" << address << endl;
        else
            cout << "  Error! No memory released" << endl;
        break;
    case 2:
        if (memInfo.State != MEM_COMMIT) {
            cout << "  Error. No memory commited\n";
            return;
        }

        cout << "  Enter size (in bytes):";
        cin >> size;

        if (VirtualFree(address, size, MEM_DECOMMIT))
            cout << "  Memory decommited at address 0x" << address << endl;
        else
            cout << "  Error! No memory decommited" << endl;
        break;
    }
}