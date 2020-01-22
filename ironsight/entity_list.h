#pragma once

class CEntityList
{
public:
    class CEntityNode* m_head; //0x0000
    class CEntityNode* m_tail; //0x0004
    char pad_0008[4]; //0x0008
}; //Size: 0x000C