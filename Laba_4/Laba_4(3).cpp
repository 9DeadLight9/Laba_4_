#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>

void asyncFileIO(const char* filePath, const char* outputPath) {
    HANDLE hFile = CreateFileA(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED, NULL);
    HANDLE hOut = CreateFileA(outputPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_FLAG_OVERLAPPED, NULL);

    if (hFile == INVALID_HANDLE_VALUE || hOut == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening files.\n";
        return;
    }

    OVERLAPPED overlapped = { 0 };
    char buffer[4096];
    DWORD bytesRead, bytesWritten;

    while (true) {
        if (!ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, &overlapped) || bytesRead == 0) {
            break;
        }

        WriteFile(hOut, buffer, bytesRead, &bytesWritten, &overlapped);
        GetOverlappedResult(hOut, &overlapped, &bytesWritten, TRUE);
    }

    CloseHandle(hFile);
    CloseHandle(hOut);
}
/*
int main() {
    const char* file1 = "d:\\Laba_4.txt ";
    const char* out1 = "d:\\Laba_1.txt";
    const char* file2 = "d:\\Laba_3.txt";
    const char* out2 = "d:\\Laba_2.txt";

    std::thread t1(asyncFileIO, file1, out1);
    std::thread t2(asyncFileIO, file2, out2);

    t1.join();
    t2.join();

    return 0;
}
*/