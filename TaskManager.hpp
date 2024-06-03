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
        std::cout << "Ошибка! Неверный выбор. Попробуйте еще раз." << std::endl;
    }

    void exit()
    {
        std::string message = "Завершение работы...";
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

            // Проверка на полное извлечение из строки
            if (ss.rdbuf()->in_avail() != 0) 
                throw std::invalid_argument("Некорректный ввод.");
        }
        catch (const std::exception& err)
        {
            // Ввод не является числом
            std::cout << err.what() << " Введите число." << std::endl;
            variable = T(); // Присвоить значение по умолчанию для типа T
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
                    throw std::out_of_range("Значение вне диапазона");
            }
            catch (const std::exception& err) 
            {
                std::cerr << "Ошибка: " << err.what() << ". Попробуйте еще раз." << std::endl;
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
                    std::cout << "Число " << numb << " было преобразовано в " << result << "\n\n";

                arr.at(i) = result;
            }
            catch (const std::invalid_argument& err) 
            {
                std::cerr << "Некорректное значение: строка не может быть преобразована в число\n";
                i--; // Возвращаемся к текущему индексу
            }
            catch (const std::out_of_range& err) 
            {
                std::cerr << "Число выходит за пределы допустимого диапазона\n";
                i--; // Возвращаемся к текущему индексу
            }
        }

        return arr;
    }

    double divide(double a, double b)
    {
        if (b == 0) 
            throw std::invalid_argument("Деление на ноль");
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
            // std::cerr << "Ошибка1: " << e.what() << std::endl;
            throw; // Выбрасываем исключение дальше без вывода сообщения
        }
        return result;
    }

    double sqrt(double x) 
    {
        if (x < 0)
            throw std::domain_error("Отрицательный корень");
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
            std::cerr << "Ошибка: " << err.what() << std::endl;
            return 0;
        }
    }

    int stringToInt(const std::string& str)
    {
        int value{ 0 };
        int sign{ 1 };
        size_t i{ 0 };

        if (str.empty())
            throw std::invalid_argument("Пустая строка не может быть преобразована в число");

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
                throw std::invalid_argument("Неверный формат данных: строка содержит недопустимые символы");

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
            std::cerr << "\nОшибка: " << err.what() << std::endl;
            return 0;  // Возвращаем значение по умолчанию в случае ошибки
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
        int a = m_functions.input<int>("Введите a: ");
        std::cout << "Введенное значение a: " << a << std::endl;

        double b = m_functions.input<double>("Введите b: ");
        std::cout << "Введенное значение b: " << b << std::endl;

        std::string c = m_functions.input<std::string>("Введите c: ");
        std::cout << "Введенное значение c: " << c << std::endl;

        std::string d = m_functions.input<std::string>("Введите d: ");
        std::cout << "Введенное значение d: " << d << std::endl;
    }

    void task2()
    {
        int c = m_functions.input<int>("Введите значение c в диапазоне [0;9]: ", 0, 10);
        std::cout << "Введенное значение c = " << c << std::endl;
    }

    void task3()
    {
        std::vector<int> arr(5);
        arr = m_functions.input("Введите элемент массива (целочисленное число) --> ", arr);

        std::cout << "\tВаш массив из целых чисел: { ";
        for (size_t i = 0; i < arr.size() - 1; i++)
            std::cout << arr.at(i) << ", ";
        std::cout << arr.at(arr.size() - 1) << " }\n\n";
    }

    void task4() 
    {
        double x = m_functions.input<double>("Введите x: ");
        double y = m_functions.input<double>("Введите y: ");
        try 
        {
            double result = m_functions.divideWithException(x, y);
            std::cout << "Результат деления " << x << " на " << y << ": " << result << std::endl;
        }
        catch (const std::exception& e)
        {
            // Обработка исключения здесь
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }

    void task5()
    {
        double z = m_functions.input<double>("Введите z: ");
        double sqrtResult = m_functions.sqrtWithException(z);
        if (z >= 0)
            std::cout << "Квадратный корень из " << z << ": " << sqrtResult << std::endl;
        else
            std::cout << "Квадратный корень не может быть вычислен для отрицательного числа: " << z << std::endl;
    }

    void task6() 
    {
        std::string strValue = m_functions.input<std::string>("Введите строку для преобразования в число: ");
        int intValue = m_functions.stringToIntWithException(strValue);
        if (intValue != 0 or (intValue == 0 && strValue == "0"))
            std::cout << "Результат преобразования строки '" << strValue << "' в число: " << intValue << std::endl;
        else 
            std::cout << "Конечная обработка ошибки: строка '" << strValue << "' не может быть преобразована в число" << std::endl;
    }

public:
	TaskManager() {}

	void task_control()
	{
        int answer{};
        do
        {
            std::cout
                << "Какое задание запускаем?\n"
                << "1) Задание 1\n"
                << "2) Задание 2\n"
                << "3) Задание 3\n"
                << "4) Задание 4\n"
                << "5) Задание 5\n"
                << "6) Задание 6\n"
                << "7) Я хочу выйти!\n\n"
                << "Выбор: ";

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
                std::cout << "Всего доброго!";
                break;

            default:
                std::cout << "Неверный индекс!";
                break;
            }

        } while ((Tasks)answer != Tasks::EXIT);
	}

};