#pragma once

class CEntityManager
{
public:
    char pad_0000[8]; //0x0000
    class CEntityList* m_list; //0x0008
    uint32_t m_count; //0x000C
    uint32_t m_max_count; //0x0010 
}; //Size: 0x0040