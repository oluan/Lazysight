#pragma once

class CEntityManager
{
public:
    char pad_0000[8]; //0x0000
    class CEntityList* m_list; //0x0008
    uint32_t m_count; //0x000C
    char pad_0010[48]; //0x0010
}; //Size: 0x0040