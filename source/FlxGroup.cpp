#include "flixel++/FlxGroup.hpp"

//G.. TODO: REMAKE THIS INTO A FLXTYPEDGROUP CUS IS MORE INTUITIVE AND PRECISE

Flx::Group::Group()
    : members()
{}

Flx::Group::~Group(){}

Flx::Basic* Flx::Group::add(Flx::Basic& obj){
    members.push_back(&obj);
    return &obj;
}
Flx::Basic* Flx::Group::add(Flx::Basic* obj){
    members.push_back(obj);
    return obj;
}
Flx::Basic* Flx::Group::operator+=(Flx::Basic& obj){
    return this->add(obj);
}
Flx::Basic* Flx::Group::operator+=(Flx::Basic* obj){
    return this->add(obj);
}

void Flx::Group::update(){
    for(Flx::Basic* obj : members)
        obj->update();
}

void Flx::Group::draw(){
    for(Flx::Basic* obj : members)
        obj->draw();
}