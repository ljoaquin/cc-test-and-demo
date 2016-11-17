#include <iostream>
#include <functional>
#include <thread>

using namespace std;

void test1();

int main(int argc, char const *argv[])
{
    cout << "hello\n";

    test1();

    return 0;
}

void sleep_ms(int millisecs)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecs));
}

class Car
{
public:
    Car(string number): m_car_num(number){};
    string GetCarNumber(){ return m_car_num; };
    void SetDriver(string name)
    {
        cout << "car driver:" << name.c_str() << endl;
        m_driver_name = name;
    };

    void Ignite(function<void()> cb)
    {
        if(cb == nullptr)
        {
            cout << "ignite cb null\n";
            return;
        }
        cout << "trying to ignite\n";
        sleep_ms(2000);
        cb();
    };

private:
    string m_car_num;
    string m_driver_name;
};

class Person
{
public:
    Person(string name): m_name(name){};
    void Drive(Car* car)
    {
        if(car == NULL) return;
        cout << m_name.c_str() << " drive " << car->GetCarNumber().c_str() << ", ignitint\n";
        car->SetDriver(m_name);
        car->Ignite(bind(&Person::OnIgnite, this));
    };

    void OnIgnite()
    {
        cout << "person ignite done, name:" << m_name.c_str() << endl;
    };

private:
    string m_name;
};

void on_ignite()
{
    cout << "ignite done\n";
}

// lambda
void test1()
{
    int local = 17;
    function<void(int)> func = [](int i){ cout << "func, i:" << i << endl; };
    func(local);

    Car car1("C1A322");
    function<string()> car1_number = bind(&Car::GetCarNumber, car1);
    string car_number = car1_number();
    cout << "car number:" << car_number.c_str() << endl;

    function<void(string)> car1_set_driver = bind(&Car::SetDriver, car1, placeholders::_1);
    car1_set_driver("Ding");

    car1.Ignite(on_ignite);
    car1.Ignite(nullptr);
    car1.Ignite([&](){ cout << "ignite cb, local:" << local << endl; });

    //
    Person person1("Joel");
    person1.Drive(&car1);
}
