#pragma once

class StorageManager
{
public:
    void begin();

private:
    void initializeFileSystem();
};