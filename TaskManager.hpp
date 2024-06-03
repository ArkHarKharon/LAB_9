#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdexcept>


class Functions
{
public:
	Functions(){}

    void error()
    {
        std::cout << "������! �������� �����. ���������� ��� ���." << std::endl;
    }

    void exit()
    {
        std::string message = "���������� ������...";
        std::cout << message << std::endl;
    }

    template <typename T>
    T input(const std::string& str)
    {
        T value;
        std::cout << str;
        std::cin >> value;
        return value;
    }

    template <typename T>
    void input(const std::string& str, T& variable) 
    {
        std::cout << str;
        std::string input_str;
        std::getline(std::cin, input_str);

        try 
        {
            std::stringstream ss(input_str);
            ss >> variable;

            // �������� �� ������ ���������� �� ������
            if (ss.rdbuf()->in_avail() != 0) 
                throw std::invalid_argument("������������ ����.");
        }
        catch (const std::exception& err)
        {
            // ���� �� �������� ������
            std::cout << err.what() << " ������� �����." << std::endl;
            variable = T(); // ��������� �������� �� ��������� ��� ���� T
        }
    }

    template <typename T>
    T input(const std::string& request, T min, T max) 
    {
        T value{};
        while (true)
        {
            try
            {
                std::cout << request;
                std::cin >> value;
                if (value >= min && value < max)
                    return value;
                else
                    throw std::out_of_range("�������� ��� ���������");
            }
            catch (const std::exception& err) 
            {
                std::cerr << "������: " << err.what() << ". ���������� ��� ���." << std::endl;
                std::cin.clear();
                std::cin.ignore();
            }
        }
    }

    std::vector<int> input(const std::string& request, std::vector<int>& arr) 
    {
        std::string numbStr = "";
        std::cin.clear();
        std::cin.ignore();

        for (size_t i = 0; i < arr.size(); i++)
        {
            std::cout << request;
            std::getline(std::cin, numbStr);

            try
            {
                double numb = std::stod(numbStr);
                int result = static_cast<int>(numb);

                if (result != numb)
                    std::cout << "����� " << numb << " ���� ������������� � " << result << "\n\n";

                arr.at(i) = result;
            }
            catch (const std::invalid_argument& err) 
            {
                std::cerr << "������������ ��������: ������ �� ����� ���� ������������� � �����\n";
                i--; // ������������ � �������� �������
            }
            catch (const std::out_of_range& err) 
            {
                std::cerr << "����� ������� �� ������� ����������� ���������\n";
                i--; // ������������ � �������� �������
            }
        }

        return arr;
    }

    double divide(double a, double b)
    {
        if (b == 0) 
            throw std::invalid_argument("������� �� ����");
        return a / b;
    }

    double divideWithException(double a, double b)
    {
        double result;
        try 
        {
            result = divide(a, b);
        }
        catch (const std::exception& err)
        {
            // std::cerr << "������1: " << e.what() << std::endl;
            throw; // ����������� ���������� ������ ��� ������ ���������
        }
        return result;
    }

    double sqrt(double x) 
    {
        if (x < 0)
            throw std::domain_error("������������� ������");
        return std::sqrt(x);
    }

    double sqrtWithException(double x)
    {
        try 
        {
            return sqrt(x);
        }
        catch (const std::exception& err)
        {
            std::cerr << "������: " << err.what() << std::endl;
            return 0;
        }
    }

    int stringToInt(const std::string& str)
    {
        int value{ 0 };
        int sign{ 1 };
        size_t i{ 0 };

        if (str.empty())
            throw std::invalid_argument("������ ������ �� ����� ���� ������������� � �����");

        if (str[0] == '-')
        {
            sign = -1;
            i = 1;
        }
        else if (str[0] == '+')
            i = 1;

        for (; i < str.length(); ++i)
        {
            if (str[i] < '0' or str[i] > '9')
                throw std::invalid_argument("�������� ������ ������: ������ �������� ������������ �������");

            value = value * 10 + (str[i] - '0');
        }

        return value * sign;
    }

    int stringToIntWithException(const std::string& str) 
    {
        try 
        {
            return stringToInt(str);
        }
        catch (const std::invalid_argument& err)
        {
            std::cerr << "\n������: " << err.what() << std::endl;
            return 0;  // ���������� �������� �� ��������� � ������ ������
        }
    }

};




class TaskManager
{
private:

	Functions m_functions;

	enum class Tasks
	{
		TASK_1 = 1,
		TASK_2,
		TASK_3,
		TASK_4,
		TASK_5,
		TASK_6,
        EXIT
	};

    void task1() 
    {
        int a = m_functions.input<int>("������� a: ");
        std::cout << "��������� �������� a: " << a << std::endl;

        double b = m_functions.input<double>("������� b: ");
        std::cout << "��������� �������� b: " << b << std::endl;

        std::string c = m_functions.input<std::string>("������� c: ");
        std::cout << "��������� �������� c: " << c << std::endl;

        std::string d = m_functions.input<std::string>("������� d: ");
        std::cout << "��������� �������� d: " << d << std::endl;
    }

    void task2()
    {
        int c = m_functions.input<int>("������� �������� c � ��������� [0;9]: ", 0, 10);
        std::cout << "��������� �������� c = " << c << std::endl;
    }

    void task3()
    {
        std::vector<int> arr(5);
        arr = m_functions.input("������� ������� ������� (������������� �����) --> ", arr);

        std::cout << "\t��� ������ �� ����� �����: { ";
        for (size_t i = 0; i < arr.size() - 1; i++)
            std::cout << arr.at(i) << ", ";
        std::cout << arr.at(arr.size() - 1) << " }\n\n";
    }

    void task4() 
    {
        double x = m_functions.input<double>("������� x: ");
        double y = m_functions.input<double>("������� y: ");
        try 
        {
            double result = m_functions.divideWithException(x, y);
            std::cout << "��������� ������� " << x << " �� " << y << ": " << result << std::endl;
        }
        catch (const std::exception& e)
        {
            // ��������� ���������� �����
            std::cerr << "������: " << e.what() << std::endl;
        }
    }

    void task5()
    {
        double z = m_functions.input<double>("������� z: ");
        double sqrtResult = m_functions.sqrtWithException(z);
        if (z >= 0)
            std::cout << "���������� ������ �� " << z << ": " << sqrtResult << std::endl;
        else
            std::cout << "���������� ������ �� ����� ���� �������� ��� �������������� �����: " << z << std::endl;
    }

    void task6() 
    {
        std::string strValue = m_functions.input<std::string>("������� ������ ��� �������������� � �����: ");
        int intValue = m_functions.stringToIntWithException(strValue);
        if (intValue != 0 or (intValue == 0 && strValue == "0"))
            std::cout << "��������� �������������� ������ '" << strValue << "' � �����: " << intValue << std::endl;
        else 
            std::cout << "�������� ��������� ������: ������ '" << strValue << "' �� ����� ���� ������������� � �����" << std::endl;
    }

public:
	TaskManager() {}

	void task_control()
	{
        int answer{};
        do
        {
            std::cout
                << "����� ������� ���������?\n"
                << "1) ������� 1\n"
                << "2) ������� 2\n"
                << "3) ������� 3\n"
                << "4) ������� 4\n"
                << "5) ������� 5\n"
                << "6) ������� 6\n"
                << "7) � ���� �����!\n\n"
                << "�����: ";

            std::cin >> answer;

            switch ((Tasks)answer)
            {
            case(Tasks::TASK_1):
                task1();
                break;

            case(Tasks::TASK_2):
                task2();
                break;

            case(Tasks::TASK_3):
                task3();
                break;

            case(Tasks::TASK_4):
                task4();
                break;

            case(Tasks::TASK_5):
                task5();
                break;

            case(Tasks::TASK_6):
                task6();
                break;

            case(Tasks::EXIT):
                std::cout << "����� �������!";
                break;

            default:
                std::cout << "�������� ������!";
                break;
            }

        } while ((Tasks)answer != Tasks::EXIT);
	}

};