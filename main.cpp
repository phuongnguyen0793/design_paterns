//
//  main.cpp
//  design_paterns
//
//  Created by Minh Phuong on 22/09/2021.
//

#include <iostream>

using namespace std;

//step 1: create House
class House{
public:
    std::string _door;
    bool _hasGarage;
    bool _hasPool;
    
    void PrintHouseInfo(){
        std::cout << "Door: " << _door
                  << "; has garage: " << _hasGarage
                  << "; has pool:" << _hasPool <<std::endl;
    }
};

//step2: create interface Builder - list out all of the actions need to build the house
class Builder{
public:
    virtual ~Builder(){};
    virtual void BuildDoor(std::string) const = 0;
    virtual void BuildGarage() const = 0;
    virtual void BuildPool() const = 0;
};

//step3: create ConcreteBuilder: inplement all of the steps for building the house
// the last thing need to remember is return the house
class ConcreteBuilder1 : public Builder{
private:
    House* house;
public:
    ConcreteBuilder1(){
        this->Reset();
    }
    ~ConcreteBuilder1(){
        delete house;
    }
    void Reset(){
        this->house = new House();
    }
    
    void BuildDoor(std::string door) const override{
        this->house->_door = door;
    }
    void BuildGarage() const override{
        this->house->_hasGarage = true;
    }
    void BuildPool() const override{
        this->house->_hasPool = true;
    }
    
    House * getHouse(){
        House* result = this->house;
        this->Reset();
        return result;
    }
};

//step 4: create Director: executing building steps and specify the particular step for building
// a house
class Director{
private:
    Builder * _builder;
public:
    void set_builder(Builder* builder){
        this->_builder = builder;
    }
    // The Director can construct several product variations
    void BuildMinimalHouseWithWoodyDoor(){
        _builder->BuildDoor("woody door");
    }
    void BuildFulllHouseByWood(){
        _builder->BuildDoor("woody door");
        _builder->BuildPool();
        _builder->BuildGarage();
    }
    void BuildMinimalHouseWithSteelDoor(){
        _builder->BuildDoor("steel door");
    }
    void BuildFulllHouseBySteek(){
        _builder->BuildDoor("steel door");
        _builder->BuildPool();
        _builder->BuildGarage();
    }
};

//step 5: create client code function
void ClientCode(Director& director){
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Build minimal house with woody door" << std::endl;
    
    director.BuildMinimalHouseWithWoodyDoor();
    House* h = builder->getHouse();
    h->PrintHouseInfo();
    delete h;
    
    std::cout << "Build full house by wood" << std::endl;
    director.BuildFulllHouseByWood();
    h = builder->getHouse();
    h->PrintHouseInfo();
    delete h;
    
    delete builder;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    Director * director = new Director;
    ClientCode(*director);
    
    return 0;
}

/*
 Open points:
 1. After reseting, the value of result is changed or not (reference)
     House* result = this->house;
     this->Reset();
 2. "const" in the declaretion of function
 3. Naming convention when declaring variables in c++: private and public
 4. The differences between new House and new House()
 */
