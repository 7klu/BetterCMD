#include "htop.h"
#include <csignal>
#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <thread>
#include <chrono>
#include <atomic>

// Variable atomique pour indiquer si Ctrl+C a été pressé
std::atomic<bool> interrompreBoucle(false);

// Gestionnaire de signal pour capturer Ctrl+C
void handleSignal(int signal) {
    if (signal == SIGINT) {
        interrompreBoucle = true; // Déclenche l'interruption
    }
}

void htopCmd() {
    // Attache le gestionnaire de signal
    signal(SIGINT, handleSignal);

    system("cls");

    while (true) {
        // Vérifie si Ctrl+C a été pressé
        if (interrompreBoucle) {
            std::cout << "\nCtrl+C capturé ! Retour au menu principal...\n";
            interrompreBoucle = false; // Réinitialise l'état
            return; // Quitte la boucle et retourne au menu
        }

        // Obtenir le handle du processus actuel
        HANDLE hProcess = GetCurrentProcess();

        // Obtenir les informations sur l'utilisation de la mémoire
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
            std::cout << "Memory Usage: " << pmc.WorkingSetSize / 1024 << " KB" << std::endl;
        }

        // Obtenir les informations sur l'utilisation du CPU
        FILETIME ftSysIdle, ftSysKernel, ftSysUser;
        FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser;

        if (GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser) &&
            GetProcessTimes(hProcess, &ftProcCreation, &ftProcExit, &ftProcKernel, &ftProcUser)) {
            ULARGE_INTEGER sysKernel, sysUser;
            sysKernel.LowPart = ftSysKernel.dwLowDateTime;
            sysKernel.HighPart = ftSysKernel.dwHighDateTime;
            sysUser.LowPart = ftSysUser.dwLowDateTime;
            sysUser.HighPart = ftSysUser.dwHighDateTime;

            ULARGE_INTEGER procKernel, procUser;
            procKernel.LowPart = ftProcKernel.dwLowDateTime;
            procKernel.HighPart = ftProcKernel.dwHighDateTime;
            procUser.LowPart = ftProcUser.dwLowDateTime;
            procUser.HighPart = ftProcUser.dwHighDateTime;

            std::cout << "CPU Usage: " << (procKernel.QuadPart + procUser.QuadPart) * 100 /
                                         (sysKernel.QuadPart + sysUser.QuadPart)
                      << "%" << std::endl;
        }

        // Fermer le handle
        CloseHandle(hProcess);

        // Pause de 1 seconde avant la mise à jour
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Effacer l'écran
        system("cls");
    }
}