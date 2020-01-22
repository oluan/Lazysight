#pragma once

class CEntityNode
{
public:
    class CEntityNode* m_next; //0x0000
    class CEntityNode* m_previous; //0x0004
    class CPlayer* m_instance; //0x0008
}; //Size: 0x000C