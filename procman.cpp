#include <Windows.h>
#include <iostream> // printf
#include <Psapi.h> // process api
#include <tchar.h>

void getProcName(DWORD pid, TCHAR *ret){
    HANDLE  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, pid);
    if (hProcess){
        HMODULE hMOd;
        DWORD cbNeeded;
        if (EnumProcessModules(hProcess, &hMOd, sizeof(hMOd), &cbNeeded)){
            GetModuleBaseName(hProcess, hMOd, ret, MAX_PATH/ sizeof(TCHAR));
        
        }
    }
}

int main()
{
  
    DWORD procARR[1024], nextd;
    BOOL procs = EnumProcesses(procARR, sizeof(procARR), &nextd);
    // get number of process found
    unsigned int nnextd = nextd / sizeof(DWORD);

    if (procs){
        printf("found processors\n");
        printf("\t numbers of processors found: %d\n", nnextd);
        printf("\t first PID : %d \n", procARR[0]);
    }

    for (int i = 0; i < nnextd; i++){
        TCHAR * procName = new TCHAR(MAX_PATH);
        getProcName(procARR[i], procName);
        printf("\t [+] PID #%d: %d\t \t", i, procARR[i]);
        _tprintf(TEXT("%s\n"), procName);
    }



    return 0;
}