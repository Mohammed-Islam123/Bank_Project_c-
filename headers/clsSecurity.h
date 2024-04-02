#pragma once
#include <iostream>
using namespace std;
class clsSecurity
{
public:
    static string encryptString(string message, int key)
    {
        const short length = message.length();
        for (int i = 0; i < length; i++)
        {
            message[i] += key;
        }
        return message;
    }

    static string decryptString(string message, int key)
    {
        const short length = message.length();
        for (int i = 0; i < length; i++)
        {
            message[i] -= key;
        }
        return message;
    }
};